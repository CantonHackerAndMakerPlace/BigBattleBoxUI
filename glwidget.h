#ifndef GLWIDGET_H
#define GLWIDGET_H

//#include <QOpenGLWidget>
#include <QWidget>
#include <box2d/box2d.h>

class GLWidget : public QWidget
{
    Q_OBJECT
public:
    GLWidget(QWidget *parent = nullptr);


    bool isRunning() const;
public slots:
    void animate();

    void start(QString playerName);
    void stop();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    b2World *world = nullptr;
    bool m_isRunning = false;
    int m_elapsed = 0;
};

/// Base class for all of the shapes with the confetti widget thing I'm making.
/// TODO: Make sure that I figure out how box2d works and map that into the Qt
/// updating structure.
class DrawnPhyicsObject : QObject {
public:

};

class WallShape {
public:
};

// This is used internally by this widget.
class ConfettiShape {
public:
};

#endif // GLWIDGET_H
