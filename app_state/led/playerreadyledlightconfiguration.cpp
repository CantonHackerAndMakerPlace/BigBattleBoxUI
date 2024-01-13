#include "playerreadyledlightconfiguration.h"

PlayerReadyLEDLightConfiguration::PlayerReadyLEDLightConfiguration(QString const& keyPrefix, QObject *parent)
    : QObject{parent}
    , m_keyPrefix(keyPrefix)
    , m_blinkOnCancel(true, m_keyPrefix + "")
    , m_numberOfBlinks(3, m_keyPrefix + "")
    , m_onDuration(500, m_keyPrefix + "")
    , m_offDuration(500, m_keyPrefix + "")
    // Player one stuff.
    , m_p1ColorNotReady(Qt::red, m_keyPrefix + "")
    , m_p1NotReadyBrightness(50, m_keyPrefix + "")
    , m_p1ColorReadyColor(Qt::red, m_keyPrefix + "")
    , m_p1ReadyBrightness(50, m_keyPrefix + "")
    , m_p1BlinkOnColor(Qt::red, m_keyPrefix + "")
    , m_p1BlinkOnBrightness(50, m_keyPrefix + "")
    , m_p1BlinkOffColor(Qt::white, m_keyPrefix + "")
    , m_p1BlinkOffBrightness(50, m_keyPrefix + "")
    // Player two stuff.
    , m_p2ColorNotReady(Qt::blue, m_keyPrefix + "")
    , m_p2NotReadyBrightness(50, m_keyPrefix + "")
    , m_p2ColorReadyColor(Qt::blue, m_keyPrefix + "")
    , m_p2ReadyBrightness(50, m_keyPrefix + "")
    , m_p2BlinkOnColor(Qt::blue, m_keyPrefix + "")
    , m_p2BlinkOnBrightness(50, m_keyPrefix + "")
    , m_p2BlinkOffColor(Qt::blue, m_keyPrefix + "")
    , m_p2BlinkOffBrightness(50, m_keyPrefix + "")
{ }

BooleanObject &PlayerReadyLEDLightConfiguration::blinkOnCancel() {
    return m_blinkOnCancel;
}

IntegerObject &PlayerReadyLEDLightConfiguration::numberOfBlinks() {
    return m_numberOfBlinks;
}

IntegerObject &PlayerReadyLEDLightConfiguration::onDuration() {
    return m_onDuration;
}

IntegerObject &PlayerReadyLEDLightConfiguration::offDuration() {
    return m_offDuration;
}


// Player one stuff.
ColorObject &PlayerReadyLEDLightConfiguration::p1ColorNotReady() {
    return m_p1ColorNotReady;
}

IntegerObject &PlayerReadyLEDLightConfiguration::p1NotReadyBrightness() {
    return m_p1NotReadyBrightness;
}

ColorObject &PlayerReadyLEDLightConfiguration::p1ColorReadyColor() {
    return m_p1ColorReadyColor;
}

IntegerObject &PlayerReadyLEDLightConfiguration::p1ReadyBrightness() {
    return m_p1ReadyBrightness;
}

ColorObject &PlayerReadyLEDLightConfiguration::p1BlinkOnColor() {
    return m_p1BlinkOnColor;
}

IntegerObject &PlayerReadyLEDLightConfiguration::p1BlinkOnBrightness() {
    return m_p1BlinkOnBrightness;
}

ColorObject &PlayerReadyLEDLightConfiguration::p1BlinkOffColor() {
    return m_p1BlinkOffColor;
}

IntegerObject &PlayerReadyLEDLightConfiguration::p1BlinkOffBrightness() {
    return m_p1BlinkOffBrightness;
}

ColorObject &PlayerReadyLEDLightConfiguration::p2ColorNotReady() {
    return m_p2ColorNotReady;
}

IntegerObject &PlayerReadyLEDLightConfiguration::p2NotReadyBrightness() {
    return m_p2NotReadyBrightness;
}

ColorObject &PlayerReadyLEDLightConfiguration::p2ColorReadyColor() {
    return m_p2ColorReadyColor;
}

IntegerObject &PlayerReadyLEDLightConfiguration::p2ReadyBrightness() {
    return m_p2ReadyBrightness;
}

ColorObject &PlayerReadyLEDLightConfiguration::p2BlinkOnColor() {
    return m_p2BlinkOnColor;
}

IntegerObject &PlayerReadyLEDLightConfiguration::p2BlinkOnBrightness() {
    return m_p2BlinkOnBrightness;
}

ColorObject &PlayerReadyLEDLightConfiguration::p2BlinkOffColor() {
    return m_p2BlinkOffColor;
}

IntegerObject &PlayerReadyLEDLightConfiguration::p2BlinkOffBrightness() {
    return m_p2BlinkOffBrightness;
}

void PlayerReadyLEDLightConfiguration::init(QSettings *settings){
    m_blinkOnCancel.attachSettings(settings);
    m_numberOfBlinks.attachSettings(settings);
    m_onDuration.attachSettings(settings);
    m_offDuration.attachSettings(settings);
    m_p1ColorNotReady.attachSettings(settings);
    m_p1NotReadyBrightness.attachSettings(settings);
    m_p1ColorReadyColor.attachSettings(settings);
    m_p1ReadyBrightness.attachSettings(settings);
    m_p1BlinkOnColor.attachSettings(settings);
    m_p1BlinkOnBrightness.attachSettings(settings);
    m_p1BlinkOffColor.attachSettings(settings);
    m_p1BlinkOffBrightness.attachSettings(settings);
    m_p2ColorNotReady.attachSettings(settings);
    m_p2NotReadyBrightness.attachSettings(settings);
    m_p2ColorReadyColor.attachSettings(settings);
    m_p2ReadyBrightness.attachSettings(settings);
    m_p2BlinkOnColor.attachSettings(settings);
    m_p2BlinkOnBrightness.attachSettings(settings);
    m_p2BlinkOffColor.attachSettings(settings);
    m_p2BlinkOffBrightness.attachSettings(settings);
}
