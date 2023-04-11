#ifndef DEATHMATCHRUNNINGCLOCKWIDGET_H
#define DEATHMATCHRUNNINGCLOCKWIDGET_H

#include <QWidget>
#include <QAbstractAnimation>

class QParallelAnimationGroup;
class DeathMatchConfig;
class DeathMatchRuntime;
class DMRDataModel;

QString msToTimeRep(int ms);
namespace Ui {
class DeathMatchRunningClockWidget;
}

class DeathMatchRunningClockWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DeathMatchRunningClockWidget(QWidget *parent = nullptr);
    ~DeathMatchRunningClockWidget();

    void setup(DeathMatchConfig *cfg, DeathMatchRuntime *rt);
public slots:
    void start();
    void pause();
    void resume();
    void stop();

private slots:
    void staringMatch(int duration, bool needsDoorDropTimer, int doorDropTime);
    void updateRemainingTime(int var);
    void updateDoorDropTime(int var);
//    void animationStateChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState);

signals:
    void started();
    void paused();
    void resumed();
    void matchOver();
    void drop_doors(int doorDropKind);

private:
    Ui::DeathMatchRunningClockWidget *ui;
    DeathMatchConfig *m_dmcfg;
    DeathMatchRuntime *m_dmRt;
    QParallelAnimationGroup *m_dmcdAnimationGroup;
};

#endif // DEATHMATCHRUNNINGCLOCKWIDGET_H
