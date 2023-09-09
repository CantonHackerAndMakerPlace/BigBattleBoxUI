#include "generalledconfiguration.h"
#include <QSettings>
#include <util.h>

GeneralLEDConfiguration::GeneralLEDConfiguration(QObject *parent)
    : QObject{parent}
    , m_p1Pin(12, "player_one/led_pin")
    , m_p1LedCount(100, "player_one/led_count")
    , m_p1Direction(0, "player_one/led_direction")
    , m_p2Pin(13, "player_two/led_pin")
    , m_p2LedCount(100, "player_two/led_count")
    , m_p2Direction(1, "player_two/led_direction")
    , m_lightOrder(0, "led/direction")
{ }

void GeneralLEDConfiguration::loadSettings(QSettings *settings) {
    // Connecting all of the configuration to the settings file.
    m_settings = settings;
    m_p1Pin.attachSettings(m_settings);
    m_p1LedCount.attachSettings(m_settings);
    m_p1Direction.attachSettings(m_settings);
    m_p2Pin.attachSettings(m_settings);
    m_p2LedCount.attachSettings(m_settings);
    m_p2Direction.attachSettings(m_settings);
    m_lightOrder.attachSettings(m_settings);
}

IntegerObject& GeneralLEDConfiguration::playerOneLedPin() {
    return m_p1Pin;
}

IntegerObject& GeneralLEDConfiguration::playerOneLedCount() {
    return m_p1LedCount;
}

IntegerObject& GeneralLEDConfiguration::playerOneLedDirection() {
    return m_p1Direction;
}

IntegerObject& GeneralLEDConfiguration::playerTwoLedPin() {
    return m_p2Pin;
}

IntegerObject& GeneralLEDConfiguration::playerTwoLedCount() {
    return m_p2LedCount;
}

IntegerObject& GeneralLEDConfiguration::playerTwoLedDirection() {
    return m_p2Direction;
}

IntegerObject& GeneralLEDConfiguration::lightOrder() {
    return m_lightOrder;
}
