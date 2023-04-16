#ifndef CONFETTIGI_H
#define CONFETTIGI_H

#include <QGraphicsItem>

class ConfettiGI : public QGraphicsItem
{
public:
    ConfettiGI();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
              QWidget *widget) override;

protected:
    void advance(int step) override;

private:
    qreal angle = 0;
    qreal speed = 0;
    qreal mouseEyeDirection = 0;
    QColor color;
};

#endif // CONFETTIGI_H
