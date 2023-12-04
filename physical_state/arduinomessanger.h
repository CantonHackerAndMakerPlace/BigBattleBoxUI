#ifndef ARDUINOMESSANGER_H
#define ARDUINOMESSANGER_H

#include <QObject>
#include <physical_state/arduinoconnectionmanager.h>
#include <QQueue>
#include <QColor>
#include <QTimer>
#include <QJsonDocument>
#include <iostream>

enum class MsgKind {
    Unknown,
    Test,
    Status,
    SpotLightsOn,
    SpotLightsOff,
    SetP1SpotLight,
    SetP2SpotLight,
    SetSpotLights,
    LEDReconfig,
    LEDAllShow,
    LEDAllFill,
    LEDAllSetPixelColor,
    LEDAllSetBrightness,
    LEDAllWhite,
    LEDShow,
    LEDFill,
    LEDSetPixelColor,
    LEDSetBrightness,
    LEDWhite,
};

std::ostream& operator<<(std::ostream& out, MsgKind kind);

struct ArduinoMessage {
    MsgKind kind;
    QString content;
};

MsgKind fromString(QString &msgName);

// TODO: Finish connecting this to other parts of the application we will need to either expose
// an instance of this through the physicalstate object or push the events through the phyiscal
// state object itself.
class ArduinoMessanger : public QObject
{
    Q_OBJECT
public:
    explicit ArduinoMessanger(ArduinoConnectionManager *connectionManager, QObject *parent = nullptr);
    ArduinoConnectionManager *connectionManager() const;
public slots:
    /// Arduino communication helper funcitons.
    void sendTest();
    void sendStatus();
    void sendSpotLightsOn();
    void sendSpotLightsOff();
    void sendSetP1SpotLight(bool v);
    void sendSetP2SpotLight(bool v);
    void sendSetSpotLights(bool p1, bool p2);
    void sendLEDReconfig(int position, int pin, int ledCount);
    void sendLEDAllShow();
    void sendLEDAllFill(int r, int g, int b, int index, int count);
    void sendLEDAllFill(QColor color, int index, int count);
    void sendLEDAllSetPixelColor(int index, int r, int g, int b);
    void sendLEDAllSetPixelColor(int index, QColor color);
    void sendLEDAllSetBrightness(int brightness);
    void sendLEDAllWhite();
    void sendLEDShow(int position);
    void sendLEDFill(int position, int r, int g, int b, int index, int count);
    void sendLEDFill(int position, QColor color, int index, int count);
    void sendLEDSetPixelColor(int position, int index, int r, int g, int b);
    void sendLEDSetPixelColor(int position, int index, QColor color);
    void sendLEDSetBrightness(int position, int brightness);
    void sendLEDWhite(int position);


    void sendMessage(MsgKind msg, QString contnents);
    void parseData(QString data);
private:
    void handleResponseToDispatch(QJsonObject *obj, QString const& data);
private slots:
    void onTimeout();
    void messageHandler();

    // Slots for updating the the queue in response to changes or messages from
    // the connected arduino.
    void onDisconnected(QString portName);
    void onConnected(QString portName);
    void onError(QString msg);
signals:
    void receivedFirstResponse();

    /// Emitted when we are given a message to send to the arduino.
    void receivedMessageToSend(MsgKind, QString);

    /// Emitted when we have received and processed a message from the arduino.
    void receivedMessageResponse(MsgKind, QString);

    /// Signals to use for debugging when messages are processed and sent
    /// to/received from the arduino
    void sentMessage(MsgKind, QString);

    /// This happens when we receive a new message, and we already have too many
    /// message.
    void abandonedMessage(MsgKind, QString);
private:
    enum class MsgState {
        Disconnected,
        WaitingForFirstUpdate,
        WaitingForNewMessage,
        WaitingForResponse,
    };
    /// Flag used to indicate that we shouldn't start sending messages until we
    /// receive the first status from the connected arduino.
    bool m_receivedFirstMessageAftrerConnection = false;
    ArduinoConnectionManager *m_conn;
    std::size_t m_maxMessages = 10000;
    std::size_t m_timeOutMs = 100;
    std::size_t m_messagePollingInterval = 5;
    std::size_t m_firstMsgTimeOut = 10000;
    QTimer *m_messagingTimeoutHandler;
    QTimer *m_messageSender;
    MsgState m_messagingState;
    QQueue<ArduinoMessage> m_messagesToSend;
    ArduinoMessage m_awaitingResponseFor;
    int m_resendAttempts = 0;
};

#endif // ARDUINOMESSANGER_H
