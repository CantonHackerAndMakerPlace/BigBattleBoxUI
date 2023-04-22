#ifndef PLAYERWINSWIDGET_H
#define PLAYERWINSWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <box2d/box2d.h>

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
public slots:
    void start();
    void stop();
private slots:
    void autocomputeSceneSize(const QList<QRectF>&);
private:
    Ui::PlayerWinsWidget *ui;
//    QGraphicsScene *m_scene;
//    QTimer *m_timer;
//    b2World *m_world;
//    b2Body* m_groundBody;
};

#endif // PLAYERWINSWIDGET_H
