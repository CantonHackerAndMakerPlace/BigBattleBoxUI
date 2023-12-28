#include "rampupconfig.h"
#include "physical_state/ledcontroller.h"

RampUpConfig::RampUpConfig(QString const& keyPrefix, QObject *parent)
    : QObject{parent}
    , m_keyPrefix(keyPrefix)
    , m_cycleDuration(3000, m_keyPrefix + "/rampup/duration")
    , m_p1Curve(Interpolation::Curve::Linear, m_keyPrefix + "/rampup/p1/curve")
    , m_p1Amplitude(1.0, m_keyPrefix + "/rampup/p1/amplitude")
    , m_p1Color(Qt::green, m_keyPrefix + "/rampup/p1/color")
    , m_p1MinBrightness(10, m_keyPrefix + "/rampup/p1/minBrightness")
    , m_p1MaxBrightness(255, m_keyPrefix + "/rampup/p1/maxBrightness")
    , m_p2Curve(Interpolation::Curve::Linear, m_keyPrefix + "/rampup/p2/curve")
    , m_p2Amplitude(1.0, m_keyPrefix + "/rampup/p2/amplitude")
    , m_p2Color(Qt::green, m_keyPrefix + "/rampup/p2/color")
    , m_p2MinBrightness(10, m_keyPrefix + "/rampup/p2/minBrightness")
    , m_p2MaxBrightness(255, m_keyPrefix + "/rampup/p2/maxBrightness")
    , m_unified(true, m_keyPrefix + "/rampup/unified")
{ }

void RampUpConfig::init(QSettings *settings) {
    m_cycleDuration.attachSettings(settings);
    m_p1Curve.attachSettings(settings);
    m_p1Amplitude.attachSettings(settings);
    m_p1Color.attachSettings(settings);
    m_p1MinBrightness.attachSettings(settings);
    m_p1MaxBrightness.attachSettings(settings);
    m_p2Curve.attachSettings(settings);
    m_p2Amplitude.attachSettings(settings);
    m_p2Color.attachSettings(settings);
    m_p2MinBrightness.attachSettings(settings);
    m_p2MaxBrightness.attachSettings(settings);
    m_unified.attachSettings(settings);
}

void RampUpConfig::setLEDController(LEDController *controller) {
    auto p1Curve = Interpolation(m_p1Curve, m_p1Amplitude);
    auto p2Curve = Interpolation(m_p2Curve, m_p2Amplitude);
    controller->rampUp(m_cycleDuration,
                       p1Curve.easingCurve(),
                       m_p1Color,
                       m_p1MinBrightness,
                       m_p1MaxBrightness,
                       p2Curve.easingCurve(),
                       m_p2Color,
                       m_p2MinBrightness,
                       m_p2MaxBrightness,
                       m_unified);
}


IntegerObject &RampUpConfig::cycleDuration() {
    return m_cycleDuration;
}

InterpolationCurveObject &RampUpConfig::p1Curve() {
    return m_p1Curve;
}

QRealObject &RampUpConfig::p1Amplitude() {
    return m_p1Amplitude;
}

ColorObject &RampUpConfig::p1Color() {
    return m_p1Color;
}

IntegerObject &RampUpConfig::p1MinBrightness() {
    return m_p1MinBrightness;
}

IntegerObject &RampUpConfig::p1MaxBrightness() {
    return m_p1MaxBrightness;
}

InterpolationCurveObject &RampUpConfig::p2Curve() {
    return m_p2Curve;
}

QRealObject &RampUpConfig::p2Amplitude() {
    return m_p2Amplitude;
}

ColorObject &RampUpConfig::p2Color() {
    return m_p2Color;
}

IntegerObject &RampUpConfig::p2MinBrightness() {
    return m_p2MinBrightness;
}

IntegerObject &RampUpConfig::p2MaxBrightness() {
    return m_p2MaxBrightness;
}

BooleanObject &RampUpConfig::unified() {
    return m_unified;
}
