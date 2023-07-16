#include "app_state/deathmatchruntime.h"
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

DeathMatchRuntime::DeathMatchRuntime(QObject *parent)
    : QObject{parent}
    , m_dmcfg(nullptr)
    , m_duration(0)
    , m_ddDuration(0)
    , m_matchAnimation(new QParallelAnimationGroup(this))
{
    connect(m_matchAnimation, &QParallelAnimationGroup::stateChanged,
            this, &DeathMatchRuntime::animationStateChanged);
}

// Called after construction but before start is called.
void DeathMatchRuntime::initialize(DeathMatchConfig *config) {
    assert(!m_dmcfg && "Double initialization");
    m_dmcfg = config;
}

int DeathMatchRuntime::timeRemaining() const {
    return m_duration;
}

int DeathMatchRuntime::doorDropTimeRemaining() const {
    return m_ddDuration;
}

void DeathMatchRuntime::start() {
    qDebug() << "Triggering start of animation";

    // Converting the time into milliseconds.
    setTimeRemaining(m_dmcfg->matchDuration() *1000);
    setDoorDropTimeRemaining(m_dmcfg->doorDropTime() * 1000);

    // Clearing any previous animations
    m_matchAnimation->stop();
    m_matchAnimation->clear();

    // Configuring full match count down.
    QPropertyAnimation *durationAnimation = new QPropertyAnimation(this);
    durationAnimation->setDuration(timeRemaining());
    durationAnimation->setStartValue(timeRemaining());
    durationAnimation->setEndValue(0);
    durationAnimation->setEasingCurve(QEasingCurve::Linear);
    durationAnimation->setDirection(QPropertyAnimation::Direction::Backward);
    connect(durationAnimation, &QPropertyAnimation::valueChanged,
            this, &DeathMatchRuntime::updateRemainingTime);
    m_matchAnimation->addAnimation(durationAnimation);

    if(m_dmcfg->doorDropKind() != DeathMatchConfig::DoorDrop::Never) {
        QPropertyAnimation *ddAnimation = new QPropertyAnimation(this);
        ddAnimation->setDuration(doorDropTimeRemaining());
        ddAnimation->setStartValue(doorDropTimeRemaining());
        ddAnimation->setEndValue(0);
        ddAnimation->setEasingCurve(QEasingCurve::Linear);
        ddAnimation->setDirection(QPropertyAnimation::Direction::Backward);
        connect(ddAnimation, &QPropertyAnimation::valueChanged,
                this, &DeathMatchRuntime::updateDoorDropTime);
        connect(ddAnimation, &QPropertyAnimation::finished,
                [&]() {
            emit dropDoorsTriggered(m_dmcfg->doorDropKind());
        });
        m_matchAnimation->addAnimation(ddAnimation);

    }

    m_matchAnimation->start();
}

void DeathMatchRuntime::pause() {
    m_matchAnimation->pause();
}

void DeathMatchRuntime::resume() {
    m_matchAnimation->resume();
}

void DeathMatchRuntime::stop() {
    m_matchAnimation->stop();
}

void DeathMatchRuntime::setTimeRemaining(int value) {
    if (m_duration != value) {
        m_duration = value;
        emit timeRemainingChanged(m_duration);
    }
}

void DeathMatchRuntime::setDoorDropTimeRemaining(int value) {
    if (m_ddDuration != value) {
        m_ddDuration = value;
        emit doorDropTimeRemainingChanged(m_ddDuration);
    }
}

void DeathMatchRuntime::updateRemainingTime(QVariant const& var) {
    bool isOk = false;
    int value = var.toInt(&isOk);
    if (!isOk) {
        std::cout << "Not an integer!" << std::endl;
        return;
    }
    setTimeRemaining(value);
}

void DeathMatchRuntime::updateDoorDropTime(QVariant const& var) {
    bool isOk = false;
    int value = var.toInt(&isOk);
    if (!isOk) {
        std::cout << "Not an integer!" << std::endl;
        return;
    }
    setDoorDropTimeRemaining(value);
}

void DeathMatchRuntime::animationStateChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState) {
    // Handling state changes like start and stop.
    using State = QAbstractAnimation::State;
    switch(oldState) {
    case State::Running:
        switch(newState) {
        case State::Running: break;
        case State::Paused:
            emit paused();
            break;
        case State::Stopped:
            emit matchOver();
            break;
        default:
            std::cout << "Unknown state" << std::endl;
            abort();
        }
        break;
    case State::Paused:
        switch(newState) {
        case State::Paused: break;
        case State::Running:
            emit resumed();
            break;
        case State::Stopped:
            emit matchOver();
            break;
        default:
            std::cout << "Unknown state" << std::endl;
            abort();
        }
        break;
    case State::Stopped:
        switch(newState) {
        case State::Running:
            emit staringMatch(
                        timeRemaining(),
                        m_dmcfg->doorDropKind() != DeathMatchConfig::DoorDrop::Never,
                        doorDropTimeRemaining());
            break;
        case State::Paused:
            // Need to check if this transition is even possible.
            emit paused();
            break;
        case State::Stopped: break;
        default:
            std::cout << "Unknown state" << std::endl;
            abort();
        }
        break;
    default:
        std::cout << "Unknown state" << std::endl;
        abort();
    }
}
