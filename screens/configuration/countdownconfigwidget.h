#ifndef COUNTDOWNCONFIGWIDGET_H
#define COUNTDOWNCONFIGWIDGET_H

#include <QWidget>

namespace Ui {
class CountDownConfigWidget;
}

class CountDownConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CountDownConfigWidget(QWidget *parent = nullptr);
    ~CountDownConfigWidget();

private:
    Ui::CountDownConfigWidget *ui;
};

#endif // COUNTDOWNCONFIGWIDGET_H
