#ifndef BATTLEBOXSTATE_H
#define BATTLEBOXSTATE_H

#include <QObject>
#include <QStringList>
#include "physicalplayerstate.h"
#include "arduinoconnectionmanager.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

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

private slots:
    void parseData(QString data);

private:
    void handleUpdate(const QJsonDocument& doc);
signals:
    void error(QString msg);
private:
    ArduinoConnectionManager *m_connectionManager;
    PhysicalPlayerState *m_playerOne;
    PhysicalPlayerState *m_playerTwo;

};

#endif // BATTLEBOXSTATE_H
