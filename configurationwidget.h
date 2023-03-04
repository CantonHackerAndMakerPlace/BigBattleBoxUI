#ifndef CONFIGURATIONWIDGET_H
#define CONFIGURATIONWIDGET_H

#include <QWidget>
#include <QSettings>

#include "battleboxphysicalstate.h"

class StateIndicatorWidget;
class ButtonConfigWidget;
namespace Ui {
class ConfigurationWidget;
}

class ConfigurationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigurationWidget(QWidget *parent = nullptr);
    ~ConfigurationWidget();


    void init(QSettings *settings, BattleBoxPhysicalState *physicalState);
private:
    void initPlayerOneConfig();
    void initPlayerTwoConfig();
    void initLedConfig();
    void initSpotLightConfig();
    void initArduinoConfig();

    void connectButtonState(PhysicalButton * sw, StateIndicatorWidget *indicator);

    void connectWiringState(PhysicalButton *sw, ButtonConfigWidget *wiringCfg);

signals:
    void clickedBack();
private:
    Ui::ConfigurationWidget *ui;
    QSettings *m_settings;
    BattleBoxPhysicalState *m_state;

};

#endif // CONFIGURATIONWIDGET_H
