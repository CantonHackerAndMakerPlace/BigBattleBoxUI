#ifndef APPLICATIONSTATE_H
#define APPLICATIONSTATE_H

#include <QObject>
#include "app_state/screen.h"
#include "app_state/battleboxviewmodel.h"
#include "physical_state/battleboxphysicalstate.h"
#include "app_state/led/ledconfiguration.h"
#include "physical_state/ledcontroller.h"
#include <physical_state/arduinoclient.h>

/// The goal of this class is to managed the global state of the program's UI
/// and any of the other state associated with it. The goal of this
/// refactoring is to ensure that all of the events go through a single place
/// that isn't part of a widget. This allows us to more easilly control
/// state by enfocing all changes go through the ApplicaitonState.
class ApplicationState : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationState(QObject *parent = nullptr);

    /// Returns the screen changing event structure. This keeps track of
    /// and emits events related too when we switch screens.
    Screen *screen() const;

    /// Returns access to the view model that controls battle box data.
    BattleBoxViewModel *data() const;

    /// The phyical state part of the battlebox. This is used to keep track of things
    /// like when a button is pressed, released, and the state of the relays. This
    /// is managed primarilly by the arduino connection manager and is used in order
    /// to provide the correct state at any given time.5
    BattleBoxPhysicalState *physicalState() const;

    /// Returns the LEDConfiguration object.
    LEDConfiguration *ledConfig() const;

    ArduinoClient *arduinoClient() const;

    LEDController *ledController() const;

private:
    // Loading setting functions and setting up signals and slots during
    // initialization.
    void initSettings();
    void attachSettingToSwitch(PhysicalButton *button, const char* settingsKey);
    void initBattleBoxState();

    void initLightPatternControls();

private:
    Screen *m_screen;
    BattleBoxViewModel *m_model = nullptr;
    BattleBoxPhysicalState *m_physicalState = nullptr;
    LEDConfiguration *m_ledConfig = nullptr;
    ArduinoClient *m_arduinoClient = nullptr;
    LEDController *m_ledController = nullptr;
};

#endif // APPLICATIONSTATE_H
