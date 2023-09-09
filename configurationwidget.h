#ifndef CONFIGURATIONWIDGET_H
#define CONFIGURATIONWIDGET_H

#include <QWidget>
#include <QSettings>

#include "app_state/applicationstate.h"

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


    void init(ApplicationState *state, MediaDialog *media);
private:
    void initPlayerOneConfig();
    void initPlayerTwoConfig();
    void initLedConfig();
    void initSpotLightConfig();
    void initArduinoConfig();
    void initMediaDialog();

    void connectButtonState(PhysicalButton * sw, StateIndicatorWidget *indicator);

    void connectWiringState(PhysicalButton *sw, ButtonConfigWidget *wiringCfg);

    void sendCommand();

signals:
    void clickedBack();
private:
    Ui::ConfigurationWidget *ui;
    QSettings *m_settings;
    ApplicationState *m_state;
    MediaDialog *m_media;

};

#endif // CONFIGURATIONWIDGET_H
