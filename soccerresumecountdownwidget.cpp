#include "soccerresumecountdownwidget.h"
#include "ui_soccerresumecountdownwidget.h"
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

SoccerResumeCountDownWidget::SoccerResumeCountDownWidget(QWidget *parent) :
    QWidget(parent)
    , ui(new Ui::SoccerResumeCountDownWidget)
    , m_group(new QSequentialAnimationGroup(this))
{
    ui->setupUi(this);

    // Configuring signals.
    QGraphicsOpacityEffect *eff1 = new QGraphicsOpacityEffect(ui->countDownLabel);
    ui->countDownLabel->setGraphicsEffect(eff1);
    {
        QPropertyAnimation *a = new QPropertyAnimation(eff1, "opacity");
        a->setDuration(1000);
        a->setStartValue(0);
        a->setEndValue(1);
        a->setEasingCurve(QEasingCurve::InBack);
        connect(a, &QPropertyAnimation::stateChanged,
                [&](QAbstractAnimation::State newState, QAbstractAnimation::State) {
            if(newState == QAbstractAnimation::State::Running) {
                ui->countDownLabel->setText("3");
            }
        });
        m_group->addAnimation(a);
    }
    {
        QPropertyAnimation *a = new QPropertyAnimation(eff1, "opacity");
        a->setDuration(1000);
        a->setStartValue(0);
        a->setEndValue(1);
        a->setEasingCurve(QEasingCurve::InBack);
        connect(a, &QPropertyAnimation::stateChanged,
                [&](QAbstractAnimation::State newState, QAbstractAnimation::State) {
            if(newState == QAbstractAnimation::State::Running) {
                ui->countDownLabel->setText("2");
            }
        });
        m_group->addAnimation(a);
    }
    {
        QPropertyAnimation *a = new QPropertyAnimation(eff1, "opacity");
        a->setDuration(1000);
        a->setStartValue(0);
        a->setEndValue(1);
        a->setEasingCurve(QEasingCurve::InBack);
        connect(a, &QPropertyAnimation::stateChanged,
                [&](QAbstractAnimation::State newState, QAbstractAnimation::State) {
            if(newState == QAbstractAnimation::State::Running) {
                ui->countDownLabel->setText("1");
            }
        });
        m_group->addAnimation(a);
    }
    {
        QPropertyAnimation *a = new QPropertyAnimation(eff1, "opacity");
        a->setDuration(1000);
        a->setStartValue(0);
        a->setEndValue(1);
        a->setEasingCurve(QEasingCurve::InBack);
        connect(a, &QPropertyAnimation::stateChanged,
                [&](QAbstractAnimation::State newState, QAbstractAnimation::State) {
            if(newState == QAbstractAnimation::State::Running) {
                ui->countDownLabel->setText("GO!!!");
            }
        });
        m_group->addAnimation(a);
    }
    connect(m_group, &QSequentialAnimationGroup::finished,
            [&] { emit resumed(); });

}

SoccerResumeCountDownWidget::~SoccerResumeCountDownWidget()
{
    delete ui;
}

void SoccerResumeCountDownWidget::start(){
    m_group->start();
    emit started();
}

void SoccerResumeCountDownWidget::cancel() {
    m_group->stop();
    emit cancelled();
}
