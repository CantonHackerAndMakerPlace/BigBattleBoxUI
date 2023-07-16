#ifndef SOCCERRUNNINGCLOCKWIDGET_H
#define SOCCERRUNNINGCLOCKWIDGET_H

#include <QWidget>
#include <app_state/soccermatch.h>
#include <QParallelAnimationGroup>

namespace Ui {
class SoccerRunningClockWidget;
}

class SoccerRunningClockWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SoccerRunningClockWidget(QWidget *parent = nullptr);
    ~SoccerRunningClockWidget();

    // sets up the slots and animations associated with
    // this widget. Should only ever be called once.
    void setup(SoccerMatch *data);

    int remainingMS() const;
public slots:
    void start();
    void resume();
    void stop();
    void pause();

private slots:
    void updateRemainingTime(QVariant const& var);
signals:
    void started();
    void resumed();
    void paused();
    void stopped();
    void gameOver();
private:
    Ui::SoccerRunningClockWidget *ui;
    SoccerMatch *m_data = nullptr;
    QParallelAnimationGroup *m_group;

};

#endif // SOCCERRUNNINGCLOCKWIDGET_H
