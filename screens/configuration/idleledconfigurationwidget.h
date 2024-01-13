#ifndef IDLELEDCONFIGURATIONWIDGET_H
#define IDLELEDCONFIGURATIONWIDGET_H

#include <QWidget>
#include "app_state/led/ledalgoconfig/ledalgoconfig.h"
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
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
    // Default value properties.
public:
    explicit IdleLedConfigurationWidget(QWidget *parent = nullptr);
    ~IdleLedConfigurationWidget();
public:
    bool hasChanges() const;
    QString title();
public slots:
    void init(LEDAlgoConfig *state);
    void save();
    void cancel();
    void revertToDefault();
    void setTitle(QString value);
private slots:
    void setCurrentConfigPage(AlgoKindObject::AlgoKind kind);
signals:
    void titleChanged(QString value);
private:

    template<typename T>
    void connectToControlButtons(T *page);

    Ui::IdleLedConfigurationWidget *ui;
    LEDAlgoConfig *m_config = nullptr;
};

#endif // IDLELEDCONFIGURATIONWIDGET_H
