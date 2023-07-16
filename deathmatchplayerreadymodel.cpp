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
        qDebug() << "Player SOmething Door closed status: "<< arg;
        emit doorClosedChanged(m_doorClosed);
    }
}

void DeathMatchPlayerReadyModel::resetDoorClosed() {
    setDoorClosed(false);
}

void DeathMatchPlayerReadyModel::setPlayerReady(bool arg) {
    qDebug() << "Received callback for player ready";
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
    resetDoorClosed();
    resetPlayerReady();
    resetReadyText();
    resetDoorText();
}

void DeathMatchPlayerReadyModel::updateReadyText(bool arg) {
    setReadyText(arg ? "Ready" : "Not Ready");
}

void DeathMatchPlayerReadyModel::updateDoorText(bool arg) {
    setDoorText(arg ? "Closed" : "Open");
}
