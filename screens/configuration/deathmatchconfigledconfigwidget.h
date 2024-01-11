#ifndef DEATHMATCHCONFIGLEDCONFIGWIDGET_H
#define DEATHMATCHCONFIGLEDCONFIGWIDGET_H

#include <QWidget>

namespace Ui {
class DeathMatchConfigLEDConfigWidget;
}

class DeathMatchConfigLEDConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DeathMatchConfigLEDConfigWidget(QWidget *parent = nullptr);
    ~DeathMatchConfigLEDConfigWidget();

private:
    Ui::DeathMatchConfigLEDConfigWidget *ui;
};

#endif // DEATHMATCHCONFIGLEDCONFIGWIDGET_H
