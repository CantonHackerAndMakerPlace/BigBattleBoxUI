#include "soccerrunningclockwidget.h"
#include "ui_soccerrunningclockwidget.h"
#include "deathmatchrunningclockwidget.h"
#include <QPropertyAnimation>
#include <iostream>
#include <iomanip>
#include <sstream>

SoccerRunningClockWidget::SoccerRunningClockWidget(QWidget *parent) :
    QWidget(parent)
    , ui(new Ui::SoccerRunningClockWidget)
    , m_group(new QParallelAnimationGroup(this))
{
    ui->setupUi(this);
    connect(m_group, &QParallelAnimationGroup::finished,
            [&] {
        emit gameOver();
    });
}

SoccerRunningClockWidget::~SoccerRunningClockWidget() {
    delete ui;
}

void SoccerRunningClockWidget::setup(SoccerMatch *data) {
    assert(!m_data);
    m_data = data;

    ui->stateLabel->setText(m_data->state());
    connect(m_data, &SoccerMatch::notifyStateChanged,
            ui->stateLabel, &QLabel::setText);

    ui->teamOneScoreLabel->setText("0");
    connect(m_data, &SoccerMatch::notifyTeamOneScoreChanged,
            [&](int score) {
        ui->teamOneScoreLabel->setText(QString("%1").arg(score));
    });

    ui->teamTwoScoreLabel->setText("0");
    connect(m_data, &SoccerMatch::notifyTeamTwoScoreChanged,
            [&](int score) {
        ui->teamTwoScoreLabel->setText(QString("%1").arg(score));
    });
    connect(m_data, &SoccerMatch::notifyMatchDurationChanged,
            [&](int newDuration) {
        ui->initialMatchTimeLabel->setText(msToTimeRep(newDuration * 1000));
    });
}

void SoccerRunningClockWidget::start() {
    // Clearing any previous animations
    m_group->stop();
    m_group->clear();

    // I don't like that I can't animate arbitrary properties this bothers me.
    auto duration = m_data->matchDuration() * 1000;
    QPropertyAnimation *durationAnimation = new QPropertyAnimation(this);
    durationAnimation->setDuration(duration);
    durationAnimation->setStartValue(duration);
    durationAnimation->setEndValue(0);
    durationAnimation->setEasingCurve(QEasingCurve::Linear);
    durationAnimation->setDirection(QPropertyAnimation::Direction::Backward);
    connect(durationAnimation, &QPropertyAnimation::valueChanged,
            this, &SoccerRunningClockWidget::updateRemainingTime);
    m_group->addAnimation(durationAnimation);

    // Launching animation
    m_group->start();
}

int SoccerRunningClockWidget::remainingMS() const {
    return m_group->totalDuration() - m_group->currentTime();
}

void SoccerRunningClockWidget::resume() {
    m_group->resume();
    emit resumed();
}

void SoccerRunningClockWidget::stop() {
    m_group->stop();
    emit stopped();

}

void SoccerRunningClockWidget::pause() {
    m_group->pause();
    emit paused();
}

void SoccerRunningClockWidget::updateRemainingTime(QVariant const& var) {
    bool isOk = false;
    int value = var.toInt(&isOk);
    if (!isOk) {
        std::cout << "Not an integer!" << std::endl;
        return;
    }
    ui->timeRemainingLabel->setText(msToTimeRep(value));
}
