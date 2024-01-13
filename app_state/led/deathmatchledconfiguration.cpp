#include "deathmatchledconfiguration.h"

DeathMatchLEDConfiguration::DeathMatchLEDConfiguration(QObject *parent)
    : QObject{parent}
    , m_configScreen(new LEDAlgoConfig("DeathMatchLED/configuration/", this))
    , m_playersReady(new PlayerReadyLEDLightConfiguration("DeathMatchLED/playersReady/", this))
    , m_doorDropLights(new CountDownFillConfig("DeathMatchLED/doorDropLights/", this))
    , m_three(new RampUpConfig("DeathMatchLED/three/", this))
    , m_two(new RampUpConfig("DeathMatchLED/two/", this))
    , m_one(new RampUpConfig("DeathMatchLED/one/", this))
    , m_fight(new RampUpConfig("DeathMatchLED/fight/", this))
    , m_runningLights(new SolidColorConfig("DeathMatchLED/running/", this))
    , m_matchOverCountDown(new CountDownFillConfig("DeathMatchLED/matchOverCountDown/", this))
    , m_winningPlayer(new WinningPlayerLightConfiguration("DeathMatchLED/Winner/", this))
{ }

void DeathMatchLEDConfiguration::loadSettings(QSettings *settings) {
    m_configScreen->init(settings);
    m_playersReady->init(settings);
    m_doorDropLights->init(settings);
    m_three->init(settings);
    m_two->init(settings);
    m_one->init(settings);
    m_fight->init(settings);
    m_runningLights->init(settings);
    m_matchOverCountDown->init(settings);
    m_winningPlayer->init(settings);
}

LEDAlgoConfig *DeathMatchLEDConfiguration::configurationScreenLights() const {
    return m_configScreen;
}

PlayerReadyLEDLightConfiguration *DeathMatchLEDConfiguration::playersReadyLights() const {
    return m_playersReady;
}

CountDownFillConfig *DeathMatchLEDConfiguration::doorDropCountDownLights() const {
    return m_doorDropLights;
}

RampUpConfig *DeathMatchLEDConfiguration::matchStartThree() const {
    return m_three;
}

RampUpConfig *DeathMatchLEDConfiguration::matchStartTwo() const {
    return m_two;
}

RampUpConfig *DeathMatchLEDConfiguration::matchStartOne() const {
    return m_one;
}

RampUpConfig *DeathMatchLEDConfiguration::matchStartFight() const {
    return m_fight;
}

SolidColorConfig *DeathMatchLEDConfiguration::matchRunningLights() const {
    return m_runningLights;
}

CountDownFillConfig *DeathMatchLEDConfiguration::matchOverCountDownLights() const {
    return m_matchOverCountDown;
}

WinningPlayerLightConfiguration *DeathMatchLEDConfiguration::winningPlayerScreen() const{
    return m_winningPlayer;
}
