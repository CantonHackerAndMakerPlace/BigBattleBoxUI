#include "physicalplayerstate.h"

PhysicalPlayerState::PhysicalPlayerState(QString name, QObject *parent)
    : QObject{parent}
    , m_name(name)
    , m_ready(new PhysicalButton(name, "ready", this))
    , m_door(new PhysicalButton(name, "door", this))
    , m_trapDoor(new PhysicalButton(name, "trap door", this))
    , m_quit(new PhysicalButton(name, "quit", this))
    , m_spotLight(new PhysicalRelay(this))
{ }

PhysicalButton *PhysicalPlayerState::readyButton() const {
    return m_ready;
}
PhysicalButton *PhysicalPlayerState::readyButton() {
    return m_ready;
}

PhysicalButton *PhysicalPlayerState::doorButton() const {
    return m_door;
}
PhysicalButton *PhysicalPlayerState::doorButton() {
    return m_door;
}

PhysicalButton *PhysicalPlayerState::trapDoorButton() const {
    return m_trapDoor;
}

PhysicalButton *PhysicalPlayerState::trapDoorButton() {
    return m_trapDoor;
}

PhysicalButton *PhysicalPlayerState::quitButton() const {
    return m_quit;
}

PhysicalButton *PhysicalPlayerState::conceedButton() {
    return m_quit;
}

PhysicalRelay *PhysicalPlayerState::spotLight() const {
    return m_spotLight;
}

PhysicalRelay *PhysicalPlayerState::spotLight() {
    return m_spotLight;
}
