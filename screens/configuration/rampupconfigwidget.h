#ifndef RAMPUPCONFIGWIDGET_H
#define RAMPUPCONFIGWIDGET_H

#include <QWidget>

namespace Ui {
class RampUpConfigWidget;
}

class RampUpConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RampUpConfigWidget(QWidget *parent = nullptr);
    ~RampUpConfigWidget();

private:
    Ui::RampUpConfigWidget *ui;
};

#endif // RAMPUPCONFIGWIDGET_H
