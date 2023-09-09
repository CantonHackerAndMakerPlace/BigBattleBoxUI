#include "arduinomessanger.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

static const QHash<QString, MsgKind> MsgNameToKind = {
    {"Test", MsgKind::Test},
    {"Status", MsgKind::Status},
    {"SpotLightsOn", MsgKind::SpotLightsOn},
    {"SpotLightsOff", MsgKind::SpotLightsOff},
    {"SetSpotLights", MsgKind::SetSpotLights},
    {"LEDReconfig", MsgKind::LEDReconfig},
    {"LEDAllShow", MsgKind::LEDAllShow},
    {"LEDAllFill", MsgKind::LEDAllFill},
    {"LEDAllSetPixelColor", MsgKind::LEDAllSetPixelColor},
    {"LEDAllSetBrightness", MsgKind::LEDAllSetBrightness},
    {"LEDAllWhite", MsgKind::LEDAllWhite},
    {"LEDShow", MsgKind::LEDShow},
    {"LEDFill", MsgKind::LEDFill},
    {"LEDSetPixelColor", MsgKind::LEDSetPixelColor},
    {"LEDSetBrightness", MsgKind::LEDSetBrightness},
    {"LEDWhite", MsgKind::LEDWhite   },
};

MsgKind fromString(QString &msgName) {
    auto iter = MsgNameToKind.find(msgName);
    if (iter == MsgNameToKind.end()) {
        return MsgKind::Unknown;
    }
    return iter.value();
}

ArduinoMessanger::ArduinoMessanger(ArduinoConnectionManager *connectionManager, QObject *parent)
    : QObject{parent}
    , m_conn(connectionManager)
    , m_messagingTimeoutHandler(new QTimer(this))
    , m_messageSender(new QTimer(this))
    , m_messagesToSend()
    , m_awaitingResponseFor(ArduinoMessage{MsgKind::Unknown, ""})
    , m_messagingState(MsgState::Disconnected)
{
    connect(m_messagingTimeoutHandler, &QTimer::timeout, this, &ArduinoMessanger::onTimeout);
    m_messagingTimeoutHandler->setSingleShot(true);
    // Need to configure this part of things.
    connect(m_messageSender, &QTimer::timeout, this, &ArduinoMessanger::messageHandler);
    m_messageSender->start(m_messagePollingInterval);

    // Setting up connections to the arduino
    connect(m_conn, &ArduinoConnectionManager::connected,
            this, &ArduinoMessanger::onConnected);
    connect(m_conn, &ArduinoConnectionManager::disconnected,
            this, &ArduinoMessanger::onDisconnected);
    connect(m_conn, &ArduinoConnectionManager::receivedData,
            this, &ArduinoMessanger::parseData);
    connect(m_conn, &ArduinoConnectionManager::error,
            this, &ArduinoMessanger::onError);


}

void ArduinoMessanger::sendMessage(MsgKind kind, QString content) {
    if (m_messagingState != MsgState::Disconnected) {
        // If we have too many messages just pop the frist message and bail
        // on the rest.
        if (m_messagesToSend.size() >= m_maxMessages) {
            auto msg = m_messagesToSend.dequeue();
            emit abandonedMessage(msg.kind, msg.content);
        }
        m_messagesToSend.enqueue(ArduinoMessage{ kind, content });
    } else {
        // If we are disconnected simply ignore the message.
        emit abandonedMessage(kind, content);
    }
}

void ArduinoMessanger::parseData(QString data) {
    // Whenever we receive a response we should stop and cancel the timeout handler.
    m_messagingTimeoutHandler->stop();

    // Handling case of receiving the first response message indicating that that
    // the arduino is ready to receive additional data.
    if (m_messagingState == MsgState::WaitingForFirstUpdate) {
        emit receivedFirstResponse();
    }

    // No matter what we received a response so we should send the next message
    // no matter what.
    m_messagingState = MsgState::WaitingForNewMessage;

    QJsonParseError err;
    auto document = QJsonDocument::fromJson(data.toUtf8(), &err);
    if (err.error) {
        qDebug() << "Error parsing json: " << err.errorString();
        return;
    }

    auto obj = document.object();
    auto statusIter = obj.find("status");
    if (obj.end() == statusIter) {
        qWarning() << "Invalid document:" << data << "unable to process response";
        return;
    }

    if (!statusIter->isString()) {
        qWarning() << "Invalid status:" << *statusIter << "unable to process response";
        return;
    }

    auto status = statusIter->toString();
    if (status == "UPDATE") {
        // Currently updates are handled somewhere else.
        return;
    } else if (status == "OK") {
        // We need to dispatch further.
        handleResponseToDispatch(&obj, data);
    } else if (status == "Error") {
        qWarning() << "Received an error respons from arduino" << data;
        return;
    } else {
        qWarning() << "Unknown status returned by arduino:" << data;
        return;
    }

}

void ArduinoMessanger::handleResponseToDispatch(QJsonObject *obj, QString const& data) {
    auto responseToIter = obj->find("response_to");
    if (obj->end() == responseToIter) {
        qWarning() << "Invalid document missing \"response_to\" field unable to process response";
        return;
    }

    if (!responseToIter->isString()) {
        qWarning() << "Invalid status:" << *responseToIter << "unable to process response";
        return;
    }

    auto messageKind = responseToIter->toString();
    auto kind = fromString(messageKind);

    // If we have an unknown message we haven't received a response to anything yet.
    if (m_awaitingResponseFor.kind != MsgKind::Unknown) {
        //

        if (m_awaitingResponseFor.kind != kind) {
            qWarning() << "Missmatch between sent message and recieved response. Sent Message: " << m_awaitingResponseFor.content << "Received response:" << data;
            emit abandonedMessage(m_awaitingResponseFor.kind, m_awaitingResponseFor.content);

            // We are obviously out of touch with the current stream of events so we should bail?
            m_awaitingResponseFor = ArduinoMessage { MsgKind::Unknown, data };

        } else {
            // We have received the correct response and we should send the next message.
            emit receivedMessageResponse(kind, data);
            m_messagingState = MsgState::WaitingForNewMessage;
        }
    } else {
        qDebug() << "Received a response to a command that we didn't send!" << data;
    }
}

void ArduinoMessanger::onTimeout() {
    // This means we haven't received our message yet so we must abandon it and just send
    // the next one in line instead.

    switch(m_messagingState) {
    // Do nothing states.
    case MsgState::Disconnected:
    case MsgState::WaitingForNewMessage:
        break;

    case MsgState::WaitingForFirstUpdate:
        qWarning() << "Warning: a timeout has been for the first arduino update status message.";
        sendStatus();
        break;

    case MsgState::WaitingForResponse:
        // This indicates a timeout and we should emit an
        // abandonded message set the state waiting for new
        // message and let it get sent.
        qWarning() << "Warning: a timeout has been for the message" << m_awaitingResponseFor.content << ". Sending next message";
        m_messagingState = MsgState::WaitingForNewMessage;
        break;
    }

}

void ArduinoMessanger::messageHandler() {
    // How we should handle messaging during each of the connected states.
    switch(m_messagingState) {
    case MsgState::Disconnected:
        // Consider just consuming messages becasue nothing here should be consider
        // truely vital.
        break;

    case MsgState::WaitingForFirstUpdate:
        // This will consume the entire queue with the exception of a status message.
        // The goal is to allow the processing of a status message.
        while(!m_messagesToSend.empty() && m_messagesToSend.head().kind != MsgKind::Status) {
            auto toAbandon = m_messagesToSend.dequeue();
            emit abandonedMessage(toAbandon.kind, toAbandon.content);
        }

        if (!m_messagesToSend.empty()) {
            auto msg = m_messagesToSend.dequeue();
            emit receivedMessageToSend(msg.kind,msg.content);
            m_conn->sendData(msg.content);
        }
        break;

    case MsgState::WaitingForNewMessage:
        if (!m_messagesToSend.empty()) {
            // Handling case for actually sending a message.
            auto nextMsg = m_messagesToSend.dequeue();
            m_awaitingResponseFor = nextMsg;
            emit receivedMessageToSend(nextMsg.kind, nextMsg.content);
            m_conn->sendData(nextMsg.content);
            m_messagingTimeoutHandler->start(m_timeOutMs);
            m_messagingState = MsgState::WaitingForResponse;
        }
        break;
    case MsgState::WaitingForResponse:
        // This is a kind of contiue to wait state and don't send anything else, we are
        // waiting for a response from the arduino before we send the next message.
        // If we timeout the next phase of things will be handled by the timeout function.
        break;
    }
}

void ArduinoMessanger::onDisconnected(QString portName){
    m_messagingState = MsgState::Disconnected;
}

void ArduinoMessanger::onConnected(QString portName) {
    m_messagingTimeoutHandler->start(m_firstMsgTimeOut);
    m_messagingState = MsgState::WaitingForFirstUpdate;
}

void ArduinoMessanger::onError(QString msg) {
    qDebug() << "Received an error from the arduino connection manager" << msg << "\n";
}

void ArduinoMessanger::sendTest() {

}

void ArduinoMessanger::sendStatus() {

}

void ArduinoMessanger::sendSpotLightsOn() {

}

void ArduinoMessanger::sendSpotLightsOff() {

}

void ArduinoMessanger::sendSetSpotLights(bool p1, bool p2) {

}

void ArduinoMessanger::sendLEDReconfig(int position, int pin, int ledCount) {
//    connectionManager()->sendData(QString("LEDReconfig %1 %2 %3\n").arg(QString::number(position), QString::number(pin), QString::number(ledCount)));
}

void ArduinoMessanger::sendLEDAllShow() {

}

void ArduinoMessanger::sendLEDAllFill(int r, int g, int b, int index, int count) {

}

void ArduinoMessanger::sendLEDAllFill(QColor color, int index, int count) {

}

void ArduinoMessanger::sendLEDAllSetPixelColor(int index, int r, int g, int b) {

}

void ArduinoMessanger::sendLEDAllSetPixelColor(int index, QColor color) {

}

void ArduinoMessanger::sendLEDAllSetBrightness(int brightness) {

}

void ArduinoMessanger::sendLEDAllWhite() {

}

void ArduinoMessanger::sendLEDShow(int position) {

}

void ArduinoMessanger::sendLEDFill(int position, int r, int g, int b, int index, int count) {

}

void ArduinoMessanger::sendLEDFill(int position, QColor color, int index, int count) {

}

void ArduinoMessanger::sendLEDSetPixelColor(int position, int index, int r, int g, int b) {

}

void ArduinoMessanger::sendLEDSetPixelColor(int position, int index, QColor color) {

}

void ArduinoMessanger::sendLEDSetBrightness(int position, int brightness) {

}

void ArduinoMessanger::sendLEDWhite(int position) {

}
