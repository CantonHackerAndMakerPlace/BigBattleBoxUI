#ifndef CYLONCONFIGWIDGET_H
#define CYLONCONFIGWIDGET_H

#include <QWidget>

namespace Ui {
class CylonConfigWidget;
}

class CylonConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CylonConfigWidget(QWidget *parent = nullptr);
    ~CylonConfigWidget();

private:
    Ui::CylonConfigWidget *ui;
};

#endif // CYLONCONFIGWIDGET_H
