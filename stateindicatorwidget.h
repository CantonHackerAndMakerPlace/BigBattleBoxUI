#ifndef STATEINDICATORWIDGET_H
#define STATEINDICATORWIDGET_H

#include <QWidget>
#include <QBrush>
#include <QPen>

namespace Ui {
class StateIndicatorWidget;
}

class StateIndicatorWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool state READ state WRITE setState NOTIFY stateChanged)
public:
    explicit StateIndicatorWidget(QWidget *parent = nullptr);
    ~StateIndicatorWidget();

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    bool state() const;
public slots:
    void setState(bool val);

signals:
    void stateChanged(bool arg);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::StateIndicatorWidget *ui;
    bool m_state = false;
    QPen pen;
    QBrush brush;
};

#endif // STATEINDICATORWIDGET_H
