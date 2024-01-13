#include "ledconfiguration.h"

LEDConfiguration::LEDConfiguration(QObject *parent)
    : QObject{parent}
    , m_generalLedConfig(new GeneralLEDConfiguration(this))
    , m_idleConfig(new LEDIdleConfiguration(this))
    , m_dmConfig(new DeathMatchLEDConfiguration(this))
{ }

GeneralLEDConfiguration *LEDConfiguration::generalLEDConfiguration() const {
    return m_generalLedConfig;
}

LEDIdleConfiguration *LEDConfiguration::idleConfiguration() const {
    return m_idleConfig;
}

DeathMatchLEDConfiguration *LEDConfiguration::deathMatchConfiguration() const {
    return m_dmConfig;
}

void LEDConfiguration::loadSettings(QSettings *settings) {
    assert(settings);
    m_generalLedConfig->loadSettings(settings);
    m_idleConfig->loadSettings(settings);
    m_dmConfig->loadSettings(settings);
}
