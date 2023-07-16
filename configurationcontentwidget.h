#ifndef CONFIGURATIONCONTENTWIDGET_H
#define CONFIGURATIONCONTENTWIDGET_H

#include <QWidget>
#include "physical_state/battleboxphysicalstate.h"
#include "physical_state/physicalbutton.h"

class BattleBoxViewModel;

namespace Ui {
class ConfigurationContentWidget;
}

class ConfigurationContentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigurationContentWidget(QWidget *parent = nullptr);
    ~ConfigurationContentWidget();

    void initialize(BattleBoxViewModel *data);

signals:
    // A bunch of signals that are used to help with triggering
    // or changing specific behaviors internally or externally.

    // Signal emitted when the user clicks the back button.
    void clickedBackToGameSelection();

    /// Trigger spot light configuration.
    void configureSpotLights(bool one, bool two);
    void spotLightsOn();
    void spotLightsOff();

    /// This is used for changing the kind of switch we
    /// use for NO/NC configuration of a kind of switch.
    void configureSwitchLogic(BattleBoxPhysicalState::Player player,
                              PhysicalButton::SwitchConfig kind,
                              QString switchName);

    /// Triggering door routines for either opening or
    /// closing the doors. This may require some additional
    /// functionality within the main window class eventually.
    void triggerDoorsOpen(bool playerOne, bool playerTwo);
    void triggerDoorsClose(bool playerOne, bool playerTwo);

    /// LED light configurations.
    /// position is always zero or one.
    void showLED(int position);
    void ledReconfig(int position, int arduinoPin, int ledCount);

    /// When this is triggered we need to make sure we call show on
    /// the media dialog. This is in case someone closed it.
    void showMediaDialog();

//    void setLEDColor(int index, int n, uint8_t r, uint8_t g, uint8_t b);
//    void fillLed(uint8_t r, uint8_t g, uint8_t b, int fist, int count);
//    void fillLed(uint8_t r, uint8_t g, uint8_t b, int fist, int count);
private:
    Ui::ConfigurationContentWidget *ui;
    BattleBoxViewModel *m_data;
};

#endif // CONFIGURATIONCONTENTWIDGET_H
