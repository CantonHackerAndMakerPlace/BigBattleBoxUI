#ifndef IDLELEDCONFIGURATIONWIDGET_H
#define IDLELEDCONFIGURATIONWIDGET_H

#include <QWidget>
#include <app_state/applicationstate.h>
#include <app_state/led/interpolation.h>
#include <defaultrestorable.h>

class ColorSelectionWidget;
class BrightnessSelectionWidget;
class InterpolationSelectorWidget;

namespace Ui {
class IdleLedConfigurationWidget;
}

class IdleLedConfigurationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IdleLedConfigurationWidget(QWidget *parent = nullptr);
    ~IdleLedConfigurationWidget();
public:
    bool hasChanges() const;
public slots:
    void init(ApplicationState *state);
    void save();
    void cancel();
    void revertToDefault();
private slots:
    void setCurrentConfigPage(AlgoKindObject::AlgoKind kind);
private:

    template<typename T>
    void connectToControlButtons(T *page);

    Ui::IdleLedConfigurationWidget *ui;
    ApplicationState *m_state;
};

#endif // IDLELEDCONFIGURATIONWIDGET_H
