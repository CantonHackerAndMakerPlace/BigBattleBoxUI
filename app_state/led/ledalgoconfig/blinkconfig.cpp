#include "blinkconfig.h"
#include "physical_state/ledcontroller.h"

BlinkConfig::BlinkConfig(QString const& settingKeyPrefix, QObject *parent)
    : QObject{parent}
    , m_numberOfBlinks(3, settingKeyPrefix + "/blink/numberOfBlinks")
    , m_onDuration(500, settingKeyPrefix + "/blink/onDuration")
    , m_offDuration(500, settingKeyPrefix + "/blink/offDuration")
    , m_unified(true, settingKeyPrefix +" /blink/unified")
    , m_p1OnColor(Qt::green, settingKeyPrefix + "/blink/p1/onColor")
    , m_p1OnBrightness(100, settingKeyPrefix + "/blink/p1/onBrightness")
    , m_p1OffColor(Qt::blue,settingKeyPrefix + "/blink/p1/offBrightness")
    , m_p1OffBrightness(100, settingKeyPrefix + "/blink/p1/offColor")
    , m_p2OnColor(Qt::magenta, settingKeyPrefix + "/blink/p2/onColor")
    , m_p2OnBrightness(100, settingKeyPrefix + "/blink/p2/onBrightness")
    , m_p2OffColor(Qt::yellow, settingKeyPrefix + "/blink/p2/offColor")
    , m_p2OffBrightness(100, settingKeyPrefix + "/blink/p2/offBrightness")
{
    qDebug() << "Constructing BlinkConfig";
}

void BlinkConfig::init(QSettings* settings) {
    qDebug() << "Attaching settings BlinkConfig";
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
