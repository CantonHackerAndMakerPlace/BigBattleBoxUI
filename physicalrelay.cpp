#include "physicalrelay.h"

PhysicalRelay::PhysicalRelay(QObject *parent)
    : QObject{parent}
{

}

bool PhysicalRelay::state() const {
    return m_state;
}

void PhysicalRelay::setState(bool arg) {
    if(m_state != arg) {
        m_state = arg;
        emit stateChanged(m_state);
    }
}
