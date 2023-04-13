#ifndef PLAYERWINSWIDGET_H
#define PLAYERWINSWIDGET_H

#include <QWidget>
//#include <box2d/box2d.h>

namespace Ui {
class PlayerWinsWidget;
}

class PlayerWinsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerWinsWidget(QWidget *parent = nullptr);
    ~PlayerWinsWidget();

    /// Draw area
//    void paintEvent(QPaintEvent *);

    /// Updates physics.
//    void timerEvent(QTimerEvent *event);connect(timer, &QTimer::timeout, openGL, &GLWidget::animate);
private:
    Ui::PlayerWinsWidget *ui;
};

#endif // PLAYERWINSWIDGET_H
