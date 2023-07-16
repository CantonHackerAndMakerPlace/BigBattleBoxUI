#include "physicalbutton.h"
#include <QDebug>

PhysicalButton::PhysicalButton(QString player, QString usedFor, QObject *parent)
    : QObject{parent}
    , m_name(player)
    , m_usedFor(usedFor)
    , m_state(false)
{ }

bool PhysicalButton::state() const {
    return m_state;
}

PhysicalButton::SwitchConfig PhysicalButton::switchKind() const {
    return m_switchKind;
}

void PhysicalButton::setState(bool arg) {
    switch(m_switchKind) {
    case SwitchConfig::NormallyOpen:
        // Normally open means when the switch is not pressed
        // the value is false
        if(m_state != arg) {
            qDebug() << m_name<< "'s " << m_usedFor << " Button Changed state to "  << m_state;
            m_state = arg;
            emit stateChanged(m_state);
        }
        break;
    case SwitchConfig::NormallyClosed:
        // Normally closed means that if the switch is not pressed
        // the value is true.
        // This means we need to ! the input for this case.
        if(m_state != !arg) {
            m_state = !arg;
            qDebug() << m_name<< "'s " << m_usedFor << " Button Changed state to "  << m_state;
            emit stateChanged(m_state);
        }
        break;
    }

}

void PhysicalButton::setSwitchKind(PhysicalButton::SwitchConfig cfg) {
    if (m_switchKind != cfg) {
        m_switchKind = cfg;
        // Update state changed because we re-configured.
        m_state = !m_state;
        emit switchKindChanged(m_switchKind);
        emit stateChanged(m_state);
    }

}
