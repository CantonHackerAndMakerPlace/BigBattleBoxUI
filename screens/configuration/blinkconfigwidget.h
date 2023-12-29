#ifndef BLINKCONFIGWIDGET_H
#define BLINKCONFIGWIDGET_H

#include <QWidget>

namespace Ui {
class BlinkConfigWidget;
}

class BlinkConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BlinkConfigWidget(QWidget *parent = nullptr);
    ~BlinkConfigWidget();

private:
    Ui::BlinkConfigWidget *ui;
};

#endif // BLINKCONFIGWIDGET_H
