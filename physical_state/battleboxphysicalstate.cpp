#include "physical_state/battleboxphysicalstate.h"
#include "physical_state/arduinoconnectionmanager.h"
#include <QColor>
#include <QFileSystemWatcher>
#include <QDir>

constexpr const char *SERIAL_PORT_FILES = "/dev/";

BattleBoxPhysicalState::BattleBoxPhysicalState(QObject *parent)
    : QObject{parent}
    , m_connectionManager(new ArduinoConnectionManager(this))
    , m_messanger(new ArduinoMessanger(m_connectionManager, this))
    , m_playerOne(new PhysicalPlayerState("player One", this))
    , m_playerTwo(new PhysicalPlayerState("player Two", this))
{

    // Pusing events out of this class so there is no confusion.
    connect(m_connectionManager, &ArduinoConnectionManager::disconnected,
        this, &BattleBoxPhysicalState::disconnectedFromArduino);
    connect(m_messanger, &ArduinoMessanger::receivedFirstResponse,
        this, &BattleBoxPhysicalState::arduinoReadyForSendReceive);

    connect(m_messanger, &ArduinoMessanger::receivedFirstResponse,
            [&] {
                qDebug() << "Received first arduino response";
            });

    // Other connections
    connect(m_connectionManager, &ArduinoConnectionManager::error,
            this, &BattleBoxPhysicalState::error);
    connect(m_connectionManager, &ArduinoConnectionManager::receivedData,
            this, &BattleBoxPhysicalState::parseData);
}

ArduinoConnectionManager *BattleBoxPhysicalState::connectionManager() const {
    return m_connectionManager;
}

ArduinoMessanger *BattleBoxPhysicalState::messanger() const {
    return m_messanger;
}

PhysicalPlayerState *BattleBoxPhysicalState::playerOne() const {
    return m_playerOne;
}

PhysicalPlayerState *BattleBoxPhysicalState::playerTwo() const {
    return m_playerTwo;
}



namespace {
    // Returns true in the event of a failure.
    bool readBool(QStringList &readableData,
                  QStringList::Iterator &iter,
                  bool *result)
    {
        bool ok = true;
        int p1ready = iter->toInt(&ok);
        if (!ok) {
            qDebug() << "Failed to read data at index: "
                     << iter - readableData.begin()
                     << ". Expected integer."
                     << readableData;
            return true;
        }
        ++iter;
        *result = p1ready != 0;
        return false;
    }

    // Returns true in the event of a failure.
    bool testString(QStringList &readableData,
                    QStringList::Iterator &iter,
                    const char* expected)
    {
        if (*iter != expected){
            qDebug() << "Failed to read data at index: "
                     << iter - readableData.begin()
                     << ". Expected string '"
                     << expected << "'."
                     << readableData;
            return true;
        }
        ++iter;
        return false;
    }
}

void BattleBoxPhysicalState::parseData(QString data) {
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
        handleUpdate(document);
    } else if (status == "OK") {
        // We need to dispatch further.
    } else if (status == "Error") {
        qWarning() << "Received an error respons from arduino" << data;
        return;
    } else {
        qWarning() << "Unknown status returned by arduino:" << data;
        return;
    }
}

bool readObjectReq(QJsonObject &obj, const char* name, QJsonObject *out) {
    auto iter = obj.find(name);
    if (iter == obj.end()) {
        qWarning() << "object is missing field" << name;
        return true;
    }

    if (!iter->isObject()){
        qWarning() << "field" << name << "is not an object";
        return true;
    }

    *out = iter->toObject();

    return false;
}

bool readIntToBoolReq(QJsonObject &obj, const char* name, bool *out) {
    auto iter = obj.find(name);
    if (iter == obj.end()) {
        qWarning() << "object is missing field" << name;
        return true;
    }

    if (!iter->isDouble()){
        qWarning() << "field" << name << "is not a number";
        return true;
    }

    *out = iter->toInt() == 1;

    return false;
}

void BattleBoxPhysicalState::handleUpdate(const QJsonDocument& document) {
    auto root = document.object();

    // Reading player one buttons
    QJsonObject p1;
    if (readObjectReq(root, "p1", &p1)) { return; }
    bool p1Door;
    if (readIntToBoolReq(p1, "door", &p1Door)) { return; }
    bool p1Ready;
    if (readIntToBoolReq(p1, "ready", &p1Ready)) { return; }
    bool p1Conceed;
    if (readIntToBoolReq(p1, "quit", &p1Conceed)) { return; }
    bool p1TrapDoor;
    if (readIntToBoolReq(p1, "trap_door", &p1TrapDoor)) { return; }

    // Reading player 2 buttons
    QJsonObject p2;
    if (readObjectReq(root, "p2", &p2)) { return; }
    bool p2Door;
    if (readIntToBoolReq(p2, "door", &p2Door)) { return; }
    bool p2Ready;
    if (readIntToBoolReq(p2, "ready", &p2Ready)) { return; }
    bool p2Conceed;
    if (readIntToBoolReq(p2, "quit", &p2Conceed)) { return; }
    bool p2TrapDoor;
    if (readIntToBoolReq(p2, "trap_door", &p2TrapDoor)) { return; }

    // Setting player one states.
    m_playerOne->doorButton()->setState(p1Door);
    m_playerOne->readyButton()->setState(p1Ready);
    m_playerOne->conceedButton()->setState(p1Conceed);
    m_playerOne->trapDoorButton()->setState(p1TrapDoor);

    // Setting player two states
    m_playerTwo->doorButton()->setState(p2Door);
    m_playerTwo->readyButton()->setState(p2Ready);
    m_playerTwo->conceedButton()->setState(p2Conceed);
    m_playerTwo->trapDoorButton()->setState(p2TrapDoor);
}
