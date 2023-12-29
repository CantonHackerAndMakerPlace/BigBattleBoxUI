#ifndef OFFCONFIGWIDGET_H
#define OFFCONFIGWIDGET_H

#include <QWidget>

namespace Ui {
class OffConfigWidget;
}

class OffConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OffConfigWidget(QWidget *parent = nullptr);
    ~OffConfigWidget();

private:
    Ui::OffConfigWidget *ui;
};

#endif // OFFCONFIGWIDGET_H
