#ifndef BREATHCONFIGWIDGET_H
#define BREATHCONFIGWIDGET_H

#include <QWidget>

namespace Ui {
class BreathConfigWidget;
}

class BreathConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BreathConfigWidget(QWidget *parent = nullptr);
    ~BreathConfigWidget();

private:
    Ui::BreathConfigWidget *ui;
};

#endif // BREATHCONFIGWIDGET_H
