#ifndef DEATHMATCHRUNTIME_H
#define DEATHMATCHRUNTIME_H

#include <QObject>
#include "app_state/deathmatchconfig.h"
#include <QAbstractAnimation>
#include <QParallelAnimationGroup>

class QParallelAnimationGroup;

// This only tracks the current time of the match, but not much else.
// It does emit events so that things associated with it can be
// animated more easily.
class DeathMatchRuntime : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int timeRemaining READ timeRemaining WRITE setTimeRemaining NOTIFY timeRemainingChanged)
    Q_PROPERTY(int doorDropTimeRemaining READ doorDropTimeRemaining WRITE setDoorDropTimeRemaining NOTIFY doorDropTimeRemainingChanged)
    Q_PROPERTY(int doorDropWarningTimeRemaining READ doorDropWarningTimeRemaining WRITE setDoorDropWarningTimeRemaining NOTIFY doorDropWarningTimeRemainingChanged)
    Q_PROPERTY(int matchOverWarningTimeRemaining READ matchOverWarningTimeRemaining WRITE setMatchOverWarningTimeRemaining NOTIFY matchOverWarningTimeRemainingChanged)

public:
    explicit DeathMatchRuntime(QObject *parent = nullptr);

    // Called after construction but before start is called.
    void initialize(DeathMatchConfig *config);

    int timeRemaining() const;
    int doorDropTimeRemaining() const;

    int doorDropWarningTimeRemaining() const;
    int matchOverWarningTimeRemaining() const;
public slots:
    void start();
    void pause();
    void resume();
    void stop();

    void setTimeRemaining(int value);
    void setDoorDropTimeRemaining(int value);

    void setDoorDropWarningTimeRemaining(int value);
    void setMatchOverWarningTimeRemaining(int value);
private slots:
    void updateRemainingTime(QVariant const& var);
    void updateDoorDropTime(QVariant const& var);
    void animationStateChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState);
signals:
    // Value specific time changes.
    void timeRemainingChanged(int arg);
    void doorDropTimeRemainingChanged(int arg);

    void doorDropWarningTimeRemainingChanged(int value);
    void matchOverWarningTimeRemainingChanged(int value);

    // Death match global state changes
    void staringMatch(int duration, bool needsDoorDropTimer, int doorDropTime);

    void paused();
    void resumed();
    void matchOverCountDown(int ms);
    void matchOver();
    void doorDropCountDown(int ms);
    void dropDoorsTriggered(DeathMatchConfig::DoorDrop kind);


private:
    DeathMatchConfig *m_dmcfg;
    int m_duration;
    int m_ddDuration;
    QParallelAnimationGroup *m_matchAnimation;
    int m_doorDropWarnCountDownTime;
    int m_matchOverWarnCountDownTime;
};

#endif // DEATHMATCHRUNTIME_H
