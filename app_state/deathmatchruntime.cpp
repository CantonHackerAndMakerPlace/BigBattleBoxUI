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

int DeathMatchRuntime::doorDropWarningTimeRemaining() const {
    return m_doorDropWarnCountDownTime;
}

int DeathMatchRuntime::matchOverWarningTimeRemaining() const {
    return m_matchOverWarnCountDownTime;
}

void DeathMatchRuntime::setDoorDropWarningTimeRemaining(int value) {
    if (m_doorDropWarnCountDownTime != value) {
        m_doorDropWarnCountDownTime = value;
        emit doorDropWarningTimeRemainingChanged(value);
    }
}

void DeathMatchRuntime::setMatchOverWarningTimeRemaining(int value) {
    if (m_matchOverWarnCountDownTime != value) {
        m_matchOverWarnCountDownTime = value;
        emit matchOverWarningTimeRemainingChanged(value);
    }
}

void DeathMatchRuntime::start() {
    qDebug() << "Triggering start of animation";

    // Converting the time into milliseconds.
    setTimeRemaining(m_dmcfg->matchDuration() * 1000);
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

    // Updating the match over time so we can correctly trigger when an event completes.
    setMatchOverWarningTimeRemaining(timeRemaining() - (m_dmcfg->matchOverWarningTime() * 1000));

    // Constructing the animation that will trigger the deathmatch time
    QPropertyAnimation *matchOverCountDownTriggerAnimation = new QPropertyAnimation(this);
    matchOverCountDownTriggerAnimation->setDuration(matchOverWarningTimeRemaining());
    matchOverCountDownTriggerAnimation->setStartValue(matchOverWarningTimeRemaining());
    matchOverCountDownTriggerAnimation->setEndValue(0);
    matchOverCountDownTriggerAnimation->setEasingCurve(QEasingCurve::Linear);
    matchOverCountDownTriggerAnimation->setDirection(QPropertyAnimation::Direction::Backward);
    connect(matchOverCountDownTriggerAnimation, &QPropertyAnimation::finished,
            [&]() {
                emit matchOverCountDown(m_dmcfg->matchOverWarningTime() * 1000);
            });
    m_matchAnimation->addAnimation(matchOverCountDownTriggerAnimation);

    if(m_dmcfg->doorDropKind() != DeathMatchConfig::DoorDrop::Never) {
        setDoorDropWarningTimeRemaining(doorDropTimeRemaining() - (m_dmcfg->doorDropWarningTime() *1000));
        QPropertyAnimation *ddCountDownTriggerAnimation = new QPropertyAnimation(this);
        ddCountDownTriggerAnimation->setDuration(doorDropWarningTimeRemaining());
        ddCountDownTriggerAnimation->setStartValue(doorDropWarningTimeRemaining());
        ddCountDownTriggerAnimation->setEndValue(0);
        ddCountDownTriggerAnimation->setEasingCurve(QEasingCurve::Linear);
        ddCountDownTriggerAnimation->setDirection(QPropertyAnimation::Direction::Backward);
        connect(ddCountDownTriggerAnimation, &QPropertyAnimation::finished,
                [&]() {
                    emit doorDropCountDown(m_dmcfg->doorDropWarningTime() * 1000);
                });
        m_matchAnimation->addAnimation(ddCountDownTriggerAnimation);


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
