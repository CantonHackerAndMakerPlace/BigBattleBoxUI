#ifndef BATTLEBOXSTATE_H
#define BATTLEBOXSTATE_H

#include <QObject>
#include <QStringList>
#include "physical_state/physicalplayerstate.h"
#include "physical_state/arduinoconnectionmanager.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "physical_state/arduinomessanger.h"

class QFileSystemWatcher;

class BattleBoxPhysicalState: public QObject
{
    Q_OBJECT

public:
    explicit BattleBoxPhysicalState(QObject *parent = nullptr);

    enum class Player {
        PlayerOne,
        PlayerTwo,
    };
    Q_ENUM(Player);

    ArduinoConnectionManager *connectionManager() const;
    ArduinoMessanger *messanger() const;
    PhysicalPlayerState *playerOne() const;
    PhysicalPlayerState *playerTwo() const;


private slots:
    /// This is used to receive data and indicate changes throughout the system.
    void parseData(QString data);

private:
    void handleUpdate(const QJsonDocument& doc);
signals:
    void error(QString msg);
    void receivedMessage();

    void arduinoReadyForSendReceive();
    void disconnectedFromArduino(QString portName);
private:
    ArduinoConnectionManager *m_connectionManager;
    ArduinoMessanger *m_messanger;
    PhysicalPlayerState *m_playerOne;
    PhysicalPlayerState *m_playerTwo;


};

#endif // BATTLEBOXSTATE_H
