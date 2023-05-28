#ifndef CONFIGURATIONWIDGET_H
#define CONFIGURATIONWIDGET_H

#include <QWidget>
#include <QSettings>

#include "battleboxphysicalstate.h"

class StateIndicatorWidget;
class ButtonConfigWidget;
class MediaDialog;
namespace Ui {
class ConfigurationWidget;
}

class ConfigurationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigurationWidget(QWidget *parent = nullptr);
    ~ConfigurationWidget();


    void init(QSettings *settings, BattleBoxPhysicalState *physicalState, MediaDialog *media);
private:
    void initPlayerOneConfig();
    void initPlayerTwoConfig();
    void initLedConfig();
    void initSpotLightConfig();
    void initArduinoConfig();
    void initMediaDialog();

    void connectButtonState(PhysicalButton * sw, StateIndicatorWidget *indicator);

    void connectWiringState(PhysicalButton *sw, ButtonConfigWidget *wiringCfg);

signals:
    void clickedBack();
private:
    Ui::ConfigurationWidget *ui;
    QSettings *m_settings;
    BattleBoxPhysicalState *m_state;
    MediaDialog *m_media;

};

#endif // CONFIGURATIONWIDGET_H
