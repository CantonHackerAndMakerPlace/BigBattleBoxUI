#include "deathmatchrunningclockwidget.h"
#include "ui_deathmatchrunningclockwidget.h"
#include "app_state/deathmatchconfig.h"
#include "app_state/deathmatchruntime.h"
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include "util.h"

DeathMatchRunningClockWidget::DeathMatchRunningClockWidget(QWidget *parent) :
    QWidget(parent)
    , ui(new Ui::DeathMatchRunningClockWidget)
    , m_dmcfg(nullptr)
    , m_dmRt(nullptr)
{
    m_dmcdAnimationGroup = new QParallelAnimationGroup(this);
    ui->setupUi(this);
}

DeathMatchRunningClockWidget::~DeathMatchRunningClockWidget()
{
    delete ui;
}

void DeathMatchRunningClockWidget::setup(DeathMatchConfig *cfg, DeathMatchRuntime *runtime) {
    assert(!m_dmcfg);
    assert(!m_dmRt);
    m_dmcfg = cfg;
    m_dmRt = runtime;

    // Connecting slots to the DeathMatchRuntime Model.
    connect(m_dmRt, &DeathMatchRuntime::timeRemainingChanged,
            this, &DeathMatchRunningClockWidget::updateRemainingTime);
    connect(m_dmRt, &DeathMatchRuntime::doorDropTimeRemainingChanged,
            this, &DeathMatchRunningClockWidget::updateDoorDropTime);
    connect(m_dmRt, &DeathMatchRuntime::staringMatch,
            this, &DeathMatchRunningClockWidget::staringMatch);
}

void DeathMatchRunningClockWidget::staringMatch(int duration, bool needsDoorDropTimer, int doorDropTime) {
    if(needsDoorDropTimer) {
        ui->doorDropTimeLabel->setText(msToTimeRep(doorDropTime));
        ui->doorDropTimeRemainingLabel->setText("Waffles");
    } else {
        ui->doorDropTimeRemainingLabel->setText("n/a");
        ui->doorDropTimeLabel->setText("n/a");
    }

    // Setting things up for the rest of the labels.
    ui->initialMatchTime->setText(msToTimeRep(duration));
    ui->doorDropSettingLabel->setText(m_dmcfg->doorDropKindAsString());
}

void DeathMatchRunningClockWidget::updateRemainingTime(int value) {
    ui->timeRemainingLabel->setText(msToTimeRep(value));
}

void DeathMatchRunningClockWidget::updateDoorDropTime(int value) {
    ui->doorDropTimeRemainingLabel->setText(msToTimeRep(value));
}


void DeathMatchRunningClockWidget::start() {
    m_dmRt->start();
}

void DeathMatchRunningClockWidget::pause() {
    m_dmRt->pause();
}

void DeathMatchRunningClockWidget::resume() {
    m_dmRt->resume();
}

void DeathMatchRunningClockWidget::stop() {
    m_dmRt->stop();
}
