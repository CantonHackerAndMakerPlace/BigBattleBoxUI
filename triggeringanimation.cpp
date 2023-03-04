#include "triggeringanimation.h"
#include <QDebug>

TriggeringAnimation::TriggeringAnimation(QObject *parent)
    : QAbstractAnimation{parent}
{ }

int TriggeringAnimation::duration() const {
    return m_duration;
}
void TriggeringAnimation::setDuration(int time) {
    m_duration = time;
}

bool TriggeringAnimation::event(QEvent *event) {
    return false;
}

void TriggeringAnimation::updateCurrentTime(int currentTime) {
    if(currentTime >= m_duration) {
        qDebug() << "Emitting finished";
    }
}
