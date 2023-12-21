#ifndef IDLELEDCONFIGURATIONWIDGET_H
#define IDLELEDCONFIGURATIONWIDGET_H

#include <QWidget>
#include <app_state/applicationstate.h>

namespace Ui {
class IdleLedConfigurationWidget;
}

class IdleLedConfigurationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IdleLedConfigurationWidget(QWidget *parent = nullptr);
    ~IdleLedConfigurationWidget();
public slots:
    void init(ApplicationState *state);

private:
    Ui::IdleLedConfigurationWidget *ui;
    ApplicationState *m_state;
};

#endif // IDLELEDCONFIGURATIONWIDGET_H
