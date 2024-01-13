#ifndef DEATHMATCHLEDCONFIGURATION_H
#define DEATHMATCHLEDCONFIGURATION_H

#include <QObject>
#include "app_state/led/ledalgoconfig/ledalgoconfig.h"
#include "app_state/led/playerreadyledlightconfiguration.h"
#include "winningplayerlightconfiguration.h"

class DeathMatchLEDConfiguration : public QObject
{
    Q_OBJECT
public:
    explicit DeathMatchLEDConfiguration(QObject *parent = nullptr);

    /// LED Pattern when configuring a deathmatch
    LEDAlgoConfig *configurationScreenLights() const;

    /// LED configuration for the players ready screen.
    PlayerReadyLEDLightConfiguration *playersReadyLights() const;

    /// LED configuration for door drop count down
    CountDownFillConfig *doorDropCountDownLights() const;

    /// Ramp up for number three.
    RampUpConfig *matchStartThree() const;

    /// Ramp up for number Two.
    RampUpConfig *matchStartTwo() const;

    /// Ramp up for number One.
    RampUpConfig *matchStartOne() const;

    /// Ramp up for number Fight.
    RampUpConfig *matchStartFight() const;

    /// Lights during the match.
    SolidColorConfig *matchRunningLights() const;

    /// The countdown strip consumtion.
    CountDownFillConfig *matchOverCountDownLights() const;

    /// Player winning
    WinningPlayerLightConfiguration *winningPlayerScreen() const;

public slots:
    void loadSettings(QSettings *settings);
private:

    LEDAlgoConfig *m_configScreen;
    PlayerReadyLEDLightConfiguration *m_playersReady;
    CountDownFillConfig *m_doorDropLights;
    RampUpConfig *m_three;
    RampUpConfig *m_two;
    RampUpConfig *m_one;
    RampUpConfig *m_fight;
    SolidColorConfig *m_runningLights;
    CountDownFillConfig *m_matchOverCountDown;
    WinningPlayerLightConfiguration *m_winningPlayer;
};

#endif // DEATHMATCHLEDCONFIGURATION_H
