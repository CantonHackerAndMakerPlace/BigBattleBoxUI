#include "blinkconfig.h"
#include "physical_state/ledcontroller.h"

BlinkConfig::BlinkConfig(QString const& settingKeyPrefix, QObject *parent)
    : QObject{parent}
    , m_numberOfBlinks(3, settingKeyPrefix + "/blink/numberOfBlinks")
    , m_onDuration(500, settingKeyPrefix + "/blink/onDuration")
    , m_offDuration(500, settingKeyPrefix + "/blink/offDuration")
    , m_unified(true, settingKeyPrefix + "/blink/unified")
    , m_p1OnColor(Qt::green, settingKeyPrefix + "/blink/p1/onColor")
    , m_p1OnBrightness(100, settingKeyPrefix + "/blink/p1/onBrightness")
    , m_p1OffColor(Qt::blue,settingKeyPrefix + "/blink/p1/offBrightness")
    , m_p1OffBrightness(100, settingKeyPrefix + "/blink/p1/offColor")
    , m_p2OnColor(Qt::magenta, settingKeyPrefix + "/blink/p2/onColor")
    , m_p2OnBrightness(100, settingKeyPrefix + "/blink/p2/onBrightness")
    , m_p2OffColor(Qt::yellow, settingKeyPrefix + "/blink/p2/offColor")
    , m_p2OffBrightness(100, settingKeyPrefix + "/blink/p2/offBrightness")
{ }

void BlinkConfig::init(QSettings* settings) {
    m_numberOfBlinks.attachSettings(settings);
    m_onDuration.attachSettings(settings);
    m_offDuration.attachSettings(settings);
    m_unified.attachSettings(settings);
    m_p1OnColor.attachSettings(settings);
    m_p1OnBrightness.attachSettings(settings);
    m_p1OffColor.attachSettings(settings);
    m_p1OffBrightness.attachSettings(settings);
    m_p2OnColor.attachSettings(settings);
    m_p2OnBrightness.attachSettings(settings);
    m_p2OffColor.attachSettings(settings);
    m_p2OffBrightness.attachSettings(settings);
}

void BlinkConfig::setLEDController(LEDController* controller) {
    controller->blink(m_numberOfBlinks,
                      m_onDuration,
                      m_offDuration,
                      m_p1OnColor,
                      m_p1OnBrightness,
                      m_p1OffColor,
                      m_p1OffBrightness,
                      m_p2OnColor,
                      m_p2OnBrightness,
                      m_p2OffColor,
                      m_p2OffBrightness,
                      m_unified);
}

IntegerObject &BlinkConfig::numberOfBlinks() {
    return m_numberOfBlinks;
}

IntegerObject &BlinkConfig::onDuration() {
    return m_onDuration;
}

IntegerObject &BlinkConfig::offDuration() {
    return m_offDuration;
}

BooleanObject &BlinkConfig::unified() {
    return m_unified;
}

ColorObject &BlinkConfig::p1OnColor() {
    return m_p1OnColor;
}

IntegerObject &BlinkConfig::p1OnBrightness() {
    return m_p1OnBrightness;
}

ColorObject &BlinkConfig::p1OffColor() {
    return m_p1OffColor;
}

IntegerObject &BlinkConfig::p1OffBrightness() {
    return m_p1OffBrightness;
}

ColorObject &BlinkConfig::p2OnColor() {
    return m_p2OnColor;
}

IntegerObject &BlinkConfig::p2OnBrightness() {
    return m_p2OnBrightness;
}

ColorObject &BlinkConfig::p2OffColor() {
    return m_p2OffColor;
}

IntegerObject &BlinkConfig::p2OffBrightness() {
    return m_p2OffBrightness;
}
