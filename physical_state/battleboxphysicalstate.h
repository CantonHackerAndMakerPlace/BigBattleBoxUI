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
    PhysicalPlayerState *playerOne() const;
    PhysicalPlayerState *playerTwo() const;




    // TODO: Create a message queue that get triggered after we get the first
    // status messages after we are connected. Allow for a time out of 200ms
    // when waiting for a response. Also make sure we correctly respond to
    // the OK messages instead of responding to status update messages.
public slots:
    /// Arduino communication helper funcitons.
    void sendTest();
    void sendStatus();
    void sendSpotLightsOn();
    void sendSpotLightsOff();
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

private slots:
    /// This is used to receive data and indicate changes throughout the system.
    void parseData(QString data);

private:
    void handleUpdate(const QJsonDocument& doc);
signals:
    void error(QString msg);
    void receivedMessage();
private:
    ArduinoConnectionManager *m_connectionManager;
    ArduinoMessanger *m_messanger;
    PhysicalPlayerState *m_playerOne;
    PhysicalPlayerState *m_playerTwo;

};

#endif // BATTLEBOXSTATE_H
