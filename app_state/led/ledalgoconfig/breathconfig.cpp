#include "breathconfig.h"
#include "physical_state/ledcontroller.h"

BreathConfig::BreathConfig(QString const& keyPrefix, QObject *parent)
    : QObject{parent}
    , m_settingsPrefix(keyPrefix)
    , m_duration(3000, m_settingsPrefix + "/breath/duration")
    , m_unified(true, m_settingsPrefix + "/breath/unified")
    , m_p1Interpolation(Interpolation::Curve::Linear, m_settingsPrefix +"/breath/p1/interpolation")
    , m_p1CurveAmplitude(1.0, m_settingsPrefix + "/breath/p1/curve")
    , m_p1MinBrightness(10, m_settingsPrefix + "/breath/p1/minBrightness")
    , m_p1MaxBrightness(100, m_settingsPrefix + "/breath/p1/maxBrightness")
    , m_p1Color(Qt::red, m_settingsPrefix + "/breath/p1/color")
    , m_p2Interpolation(Interpolation::Curve::Linear, m_settingsPrefix + "/breath/p2/interpolation")
    , m_p2CurveAmplitude(1.0, m_settingsPrefix + "/breath/p2/curve")
    , m_p2MinBrightness(10, m_settingsPrefix + "/breath/p2/minBrightness")
    , m_p2MaxBrightness(100, m_settingsPrefix + "/breath/p2/maxBrightness")
    , m_p2Color(Qt::blue, m_settingsPrefix + "/breath/p2/color")
{ }

IntegerObject& BreathConfig::cycleDuration() {
    return m_duration;
}

BooleanObject& BreathConfig::unified() {
    return m_unified;
}

InterpolationCurveObject& BreathConfig::p1Interpolation() {
    return m_p1Interpolation;
}

QRealObject& BreathConfig::p1CurveAmpliatude() {
    return m_p1CurveAmplitude;
}

IntegerObject& BreathConfig::p1MinBrightness() {
    return m_p1MinBrightness;
}

IntegerObject& BreathConfig::p1MaxBrightness() {
    return m_p1MaxBrightness;
}

ColorObject& BreathConfig::p1Color() {
    return m_p1Color;
}

InterpolationCurveObject& BreathConfig::p2Interpolation() {
    return m_p2Interpolation;
}

QRealObject& BreathConfig::p2CurveAmpliatude() {
    return m_p2CurveAmplitude;
}

IntegerObject& BreathConfig::p2MinBrightness() {
    return m_p2MinBrightness;
}

IntegerObject& BreathConfig::p2MaxBrightness() {
    return m_p2MaxBrightness;
}

ColorObject& BreathConfig::p2Color() {
    return m_p2Color;
}

void BreathConfig::init(QSettings *settings) {
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

void BreathConfig::setLEDController(LEDController *controller) {
    auto p1Interpolation = Interpolation(m_p1Interpolation, m_p1CurveAmplitude);
    auto p2Interpolation = Interpolation(m_p2Interpolation, m_p2CurveAmplitude);
    controller->breath(m_duration,
                       m_p1MinBrightness,
                       m_p1MaxBrightness,
                       m_p1Color,
                       p1Interpolation.easingCurve(),
                       m_p2MinBrightness,
                       m_p2MaxBrightness,
                       m_p2Color,
                       p2Interpolation.easingCurve(),
                       m_unified);
}
