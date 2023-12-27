#include "breathconfig.h"

BlinkConfig::BlinkConfig(QString const& keyPrefix, QObject *parent)
    : QObject{parent}
    , m_settingsPrefix(keyPrefix)
    , m_duration(3000, m_settingsPrefix + "/blink/duration")
    , m_unified(true, m_settingsPrefix + "/blink/unified")
    , m_p1Interpolation(Interpolation::Curve::Linear, m_settingsPrefix +"blink/p1/interpolation")
    , m_p1CurveAmplitude(1.0, m_settingsPrefix + "blink/p1/curve")
    , m_p1MinBrightness(10, m_settingsPrefix + "blink/p1/minBrightness")
    , m_p1MaxBrightness(100, m_settingsPrefix + "blink/p1/maxBrightness")
    , m_p1Color(Qt::red, m_settingsPrefix + "blink/p1/color")
    , m_p2Interpolation(Interpolation::Curve::Linear, m_settingsPrefix + "blink/p2/interpolation")
    , m_p2CurveAmplitude(1.0, m_settingsPrefix + "blink/p2/curve")
    , m_p2MinBrightness(10, m_settingsPrefix + "blink/p2/minBrightness")
    , m_p2MaxBrightness(100, m_settingsPrefix + "blink/p2/maxBrightness")
    , m_p2Color(Qt::blue, m_settingsPrefix + "blink/p2/color")
{ }

IntegerObject& BlinkConfig::cycleDuration() {
    return m_duration;
}

BooleanObject& BlinkConfig::unified() {
    return m_unified;
}

InterpolationCurveObject& BlinkConfig::p1Interpolation() {
    return m_p1Interpolation;
}

QRealObject& BlinkConfig::p1CurveAmpliatude() {
    return m_p1CurveAmplitude;
}

IntegerObject& BlinkConfig::p1MinBrightness() {
    return m_p1MinBrightness;
}

IntegerObject& BlinkConfig::p1MaxBrightness() {
    return m_p1MaxBrightness;
}

ColorObject& BlinkConfig::p1Color() {
    return m_p1Color;
}

InterpolationCurveObject& BlinkConfig::p2Interpolation() {
    return m_p2Interpolation;
}

QRealObject& BlinkConfig::p2CurveAmpliatude() {
    return m_p2CurveAmplitude;
}

IntegerObject& BlinkConfig::p2MinBrightness() {
    return m_p2MinBrightness;
}

IntegerObject& BlinkConfig::p2MaxBrightness() {
    return m_p2MaxBrightness;
}

ColorObject& BlinkConfig::p2Color() {
    return m_p2Color;
}

void BlinkConfig::init(QSettings *settings) {
    m_duration.attachSettings(settings);
    m_unified.attachSettings(settings);
    m_p1Interpolation.attachSettings(settings);
    m_p1CurveAmplitude.attachSettings(settings);
    m_p1MinBrightness.attachSettings(settings);
    m_p1MaxBrightness.attachSettings(settings);
    m_p1Color.attachSettings(settings);
    m_p2Interpolation.attachSettings(settings);
    m_p2CurveAmplitude.attachSettings(settings);
    m_p2MinBrightness.attachSettings(settings);
    m_p2MaxBrightness.attachSettings(settings);
    m_p2Color.attachSettings(settings);
}

void BlinkConfig::setLEDController(LEDController *contoller) {

}
