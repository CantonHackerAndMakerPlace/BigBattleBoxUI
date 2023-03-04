#include "stateindicatorwidget.h"
#include "ui_stateindicatorwidget.h"

#include <QPainter>
#include <QPainterPath>

StateIndicatorWidget::StateIndicatorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StateIndicatorWidget)
{
    ui->setupUi(this);
}

StateIndicatorWidget::~StateIndicatorWidget() {
    delete ui;
}

QSize StateIndicatorWidget::minimumSizeHint() const  {
    return QSize(50, 50);
}
QSize StateIndicatorWidget::sizeHint() const  {
    return QSize(50, 50);
}

bool StateIndicatorWidget::state() const {
    return m_state;
}

void StateIndicatorWidget::setState(bool arg) {
    if (m_state != arg) {
        m_state = arg;
        emit stateChanged(m_state);
        update();
    }
}

void StateIndicatorWidget::paintEvent(QPaintEvent */* event */) {
    QPainter painter(this);
    QRect bb(0, 0, 50, 50);
    if (m_state) {
        painter.setBrush(Qt::green);
    } else {
        painter.setBrush(Qt::red);
    }
    painter.drawEllipse(bb);
}
