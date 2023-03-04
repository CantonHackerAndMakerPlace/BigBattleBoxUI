#include "deathmatchrunningclockwidget.h"
#include "ui_deathmatchrunningclockwidget.h"
#include "deathmatchconfig.h"
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <iostream>
#include <iomanip>
#include <sstream>

DeathMatchRunningClockWidget::DeathMatchRunningClockWidget(QWidget *parent) :
    QWidget(parent)
    , ui(new Ui::DeathMatchRunningClockWidget)
    , m_dmcfg(nullptr)
{
    m_dmcdAnimationGroup = new QParallelAnimationGroup(this);
    ui->setupUi(this);

    connect(m_dmcdAnimationGroup, &QParallelAnimationGroup::stateChanged,
            this, &DeathMatchRunningClockWidget::animationStateChanged);
}

DeathMatchRunningClockWidget::~DeathMatchRunningClockWidget()
{
    delete ui;
}

void DeathMatchRunningClockWidget::setup(DeathMatchConfig *cfg) {
    assert(!m_dmcfg);
    m_dmcfg = cfg;
}

constexpr int MILLISECONDS_PER_MINUTES = 60000;
constexpr int MILLISECONDS_PER_SECOND = 1000;

QString msToTimeRep(int ms) {
    std::stringstream s;
    auto minutes = std::div(ms, MILLISECONDS_PER_MINUTES);
    auto seconds = std::div(minutes.rem, MILLISECONDS_PER_SECOND);
    if (minutes.quot > 0) {
        s << minutes.quot<< "m ";
    }
    if (seconds.quot > 0) {
        s << std::setfill('0') << std::setw(2) << seconds.quot;
    } else {
        s << "0";
    }
    s << "." <<std::setfill('0') << std::setw(3) << seconds.rem;
    auto temp = s.str();
    return QString(temp.c_str());
}

void DeathMatchRunningClockWidget::updateRemainingTime(QVariant const& var) {
    bool isOk = false;
    int value = var.toInt(&isOk);
    if (!isOk) {
        std::cout << "Not an integer!" << std::endl;
        return;
    }
    ui->timeRemainingLabel->setText(msToTimeRep(value));
}

void DeathMatchRunningClockWidget::updateDoorDropTime(QVariant const& var) {
    bool isOk = false;
    int value = var.toInt(&isOk);
    if (!isOk) {
        std::cout << "Not an integer!" << std::endl;
        return;
    }
    ui->doorDropTimeRemainingLabel->setText(msToTimeRep(value));
}

void DeathMatchRunningClockWidget::animationStateChanged(QAbstractAnimation::State newState,
                                                         QAbstractAnimation::State oldState) {
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
            emit started();
            break;
        case State::Paused:
            // Need to check if this transition is even possible.
            emit started();
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

void DeathMatchRunningClockWidget::start() {

    // Clearing any previous animations
    m_dmcdAnimationGroup->stop();
    m_dmcdAnimationGroup->clear();

    // I don't like that I can't animate arbitrary properties this bothers me.
    auto duration = m_dmcfg->matchDuration() * 1000;
    QPropertyAnimation *durationAnimation = new QPropertyAnimation(this);
    durationAnimation->setDuration(duration);
    durationAnimation->setStartValue(duration);
    durationAnimation->setEndValue(0);
    durationAnimation->setEasingCurve(QEasingCurve::Linear);
    durationAnimation->setDirection(QPropertyAnimation::Direction::Backward);
    connect(durationAnimation, &QPropertyAnimation::valueChanged,
            this, &DeathMatchRunningClockWidget::updateRemainingTime);
    m_dmcdAnimationGroup->addAnimation(durationAnimation);

    if(m_dmcfg->doorDropKind() != DeathMatchConfig::DoorDrop::Never) {
        auto ddDropTime = m_dmcfg->doorDropTime() * 1000;
        QPropertyAnimation *ddAnimation = new QPropertyAnimation(this);
        ddAnimation->setTargetObject(this);
        ddAnimation->setDuration(ddDropTime);
        ddAnimation->setStartValue(ddDropTime);
        ddAnimation->setEndValue(0);
        ddAnimation->setEasingCurve(QEasingCurve::Linear);
        ddAnimation->setDirection(QPropertyAnimation::Direction::Backward);
        connect(ddAnimation, &QPropertyAnimation::valueChanged,
                this, &DeathMatchRunningClockWidget::updateDoorDropTime);
        m_dmcdAnimationGroup->addAnimation(ddAnimation);

        ui->doorDropTimeLabel->setText(msToTimeRep(ddDropTime));
        ui->doorDropTimeRemainingLabel->setText("Waffles");
    } else {
        ui->doorDropTimeRemainingLabel->setText("n/a");
        ui->doorDropTimeLabel->setText("n/a");
    }

    // Setting things up for the rest of the labels.
    ui->initialMatchTime->setText(msToTimeRep(duration));
    ui->doorDropSettingLabel->setText(m_dmcfg->doorDropKindAsString());

    // Launching animation
    m_dmcdAnimationGroup->start();

}

void DeathMatchRunningClockWidget::pause() {
    m_dmcdAnimationGroup->pause();
}

void DeathMatchRunningClockWidget::resume() {
    m_dmcdAnimationGroup->resume();
}

void DeathMatchRunningClockWidget::stop() {
    m_dmcdAnimationGroup->stop();
}
