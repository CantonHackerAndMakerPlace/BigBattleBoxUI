#ifndef SOLIDCOLORCONFIGWIDGET_H
#define SOLIDCOLORCONFIGWIDGET_H

#include <QWidget>

namespace Ui {
class SolidColorConfigWidget;
}

class SolidColorConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SolidColorConfigWidget(QWidget *parent = nullptr);
    ~SolidColorConfigWidget();

private:
    Ui::SolidColorConfigWidget *ui;
};

#endif // SOLIDCOLORCONFIGWIDGET_H
