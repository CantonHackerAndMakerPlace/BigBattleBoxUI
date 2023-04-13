#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
//    b2AABB worldAABB;
//    worldAABB.lowerBound.Set(-200, -100);
//    worldAABB.upperBound.Set(200, 500);
//    b2World *world = new b2World(b2Vec2(0.0f, -10.0f));
}

bool GLWidget::isRunning() const {
    return m_isRunning;
}

void GLWidget::animate() {

}

void GLWidget::start(QString playerName) {

}

void GLWidget::stop() {

}

void GLWidget::paintEvent(QPaintEvent *event) {

}
