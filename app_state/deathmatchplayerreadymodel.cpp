#include "deathmatchplayerreadymodel.h"
#include <QDebug>

DeathMatchPlayerReadyModel::DeathMatchPlayerReadyModel(QObject *parent)
    : QObject{parent}
{
    connect(this, &DeathMatchPlayerReadyModel::doorClosedChanged,
            this, &DeathMatchPlayerReadyModel::updateDoorText);
    connect(this, &DeathMatchPlayerReadyModel::playerReadyChanged,
            this, &DeathMatchPlayerReadyModel::updateReadyText);
}

bool DeathMatchPlayerReadyModel::doorClosed() const {
    return m_doorClosed;
}

bool DeathMatchPlayerReadyModel::playerReady() const {
    return m_playerReady;
}

QString DeathMatchPlayerReadyModel::readyText() const {
    return m_readyText;
}

QString DeathMatchPlayerReadyModel::doorText() const {
    return m_doorText;
}

void DeathMatchPlayerReadyModel::setDoorClosed(bool arg) {
    if (m_doorClosed != arg) {
        m_doorClosed = arg;
        emit doorClosedChanged(m_doorClosed);
    }
    updateDoorText(m_doorClosed);
}

void DeathMatchPlayerReadyModel::resetDoorClosed() {
    setDoorClosed(false);
}

void DeathMatchPlayerReadyModel::setDoorClosedForRound(bool arg) {
    if (!arg) {
        if (!m_doorClosed) {
            // Do nothing.
            return;
        } else {
            setDoorClosed(arg);
            if (m_playerReady) {
                // Player must hit ready again because they opened the door.
                // Uncheck the player ready state because they aren't
                // actually ready yet.
                emit doorNotClosed("Door opened");
                setPlayerReady(false);
            } else {
                // Do nothing player wasn't ready anyway.
                return;
            }
        }
    } else {
        setDoorClosed(arg);
    }
}

void DeathMatchPlayerReadyModel::setPlayerReady(bool arg) {
    if (m_playerReady != arg) {
        m_playerReady = arg;
        emit playerReadyChanged(m_playerReady);
    }
}

void DeathMatchPlayerReadyModel::setPlayerReadyForRound(bool arg) {
    // Ignore when the player is ready but lets go of the button.
    if (m_playerReady && !arg) {
        return;
    }
    if(m_doorClosed) {
        if(m_playerReady != arg) {
            m_playerReady = arg;
            emit playerReadyChanged(m_playerReady);
        }
    } else if(arg) {
        emit doorNotClosed("door not closed");
    } else {
        m_playerReady = arg;
        emit playerReadyChanged(m_playerReady);
    }
}

void DeathMatchPlayerReadyModel::resetPlayerReady() {
    setPlayerReady(false);
}

void DeathMatchPlayerReadyModel::setReadyText(QString arg) {
    if (m_readyText != arg) {
        m_readyText = arg;
        emit readyTextChanged(m_readyText);
    }
}

void DeathMatchPlayerReadyModel::resetReadyText() {
    setDoorText("Not Ready");
}

void DeathMatchPlayerReadyModel::setDoorText(QString arg) {
    if (m_doorText != arg) {
        m_doorText = arg;
        emit doorTextChanged(m_doorText);
    }
}

void DeathMatchPlayerReadyModel::resetDoorText() {
    setDoorText("Open");
}

void DeathMatchPlayerReadyModel::reset() {
//    resetDoorClosed();
    resetPlayerReady();
    resetReadyText();
//    resetDoorText();
}

void DeathMatchPlayerReadyModel::updateReadyText(bool arg) {
    setReadyText(arg ? "Ready" : "Not Ready");
}

void DeathMatchPlayerReadyModel::updateDoorText(bool arg) {
    setDoorText(arg ? "Closed" : "Open");
}
