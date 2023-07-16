#ifndef PHYSICALPLAYERSTATE_H
#define PHYSICALPLAYERSTATE_H

#include <QObject>
#include "physicalbutton.h"
#include "physicalrelay.h"

class PhysicalPlayerState : public QObject
{
    Q_OBJECT
public:
    explicit PhysicalPlayerState(QString name, QObject *parent = nullptr);

    PhysicalButton *readyButton() const;
    PhysicalButton *readyButton();
    PhysicalButton *doorButton() const;
    PhysicalButton *doorButton();
    PhysicalButton *trapDoorButton() const;
    PhysicalButton *trapDoorButton();
    PhysicalButton *quitButton() const;
    PhysicalButton *conceedButton();

    // Spot light for a player
    PhysicalRelay *spotLight() const;
    PhysicalRelay *spotLight();
private:
    QString m_name;
    PhysicalButton *m_ready;
    PhysicalButton *m_door;
    PhysicalButton *m_trapDoor;
    PhysicalButton *m_quit;
    PhysicalRelay *m_spotLight;
};

#endif // PHYSICALPLAYERSTATE_H
