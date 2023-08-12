#ifndef INTERPOLATIONSELECTORWIDGET_H
#define INTERPOLATIONSELECTORWIDGET_H

#include <QWidget>

namespace Ui {
class InterpolationSelectorWidget;
}

class InterpolationSelectorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InterpolationSelectorWidget(QWidget *parent = nullptr);
    ~InterpolationSelectorWidget();

private:
    Ui::InterpolationSelectorWidget *ui;
};

#endif // INTERPOLATIONSELECTORWIDGET_H
