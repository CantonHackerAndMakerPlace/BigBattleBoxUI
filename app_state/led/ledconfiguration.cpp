#include "ledconfiguration.h"

LEDConfiguration::LEDConfiguration(QObject *parent)
    : QObject{parent}
    , m_generalLedConfig(new GeneralLEDConfiguration(this))
    , m_idleConfig(new LEDIdleConfiguration(this))
{ }


GeneralLEDConfiguration *LEDConfiguration::generalLEDConfiguration() const {
    return m_generalLedConfig;
}

LEDIdleConfiguration *LEDConfiguration::idleConfiguration() const {
    return m_idleConfig;
}

void LEDConfiguration::loadSettings(QSettings *settings) {
    m_generalLedConfig->loadSettings(settings);
    m_idleConfig->loadSettings(settings);
}
