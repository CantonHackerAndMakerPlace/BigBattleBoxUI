#ifndef SOCCERRESUMECOUNTDOWNWIDGET_H
#define SOCCERRESUMECOUNTDOWNWIDGET_H

#include <QWidget>
#include <QSequentialAnimationGroup>

namespace Ui {
class SoccerResumeCountDownWidget;
}

class SoccerResumeCountDownWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SoccerResumeCountDownWidget(QWidget *parent = nullptr);
    ~SoccerResumeCountDownWidget();
public slots:
    void start();
    void cancel();
signals:
    void started();
    void cancelled();
    void resumed();
private:
    Ui::SoccerResumeCountDownWidget *ui;
    QSequentialAnimationGroup *m_group;
};

#endif // SOCCERRESUMECOUNTDOWNWIDGET_H
