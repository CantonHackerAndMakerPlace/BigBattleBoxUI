#include "cylonconfig.h"

CylonConfig::CylonConfig(QString const& keyPrefix, QObject *parent)
    : QObject{parent}
    , m_settingsPrefix(keyPrefix)
    , m_eyeLength(5, m_settingsPrefix + "/cylon/eyeLength")
    , m_cycleDuration(3000, m_settingsPrefix + "/cylon/duration")
    , m_p1Brightness(100, m_settingsPrefix + "/cylon/p1/brightness")
    , m_p1Curve(Interpolation::Curve::Linear, m_settingsPrefix + "/cylon/p1/curve")
    , m_p1CurveAmplitude(1.0, m_settingsPrefix + "/cylon/p1/amplitude")
    , m_p1foregroundColor(Qt::red, m_settingsPrefix + "/cylon/p1/foregroundColor")
    , m_p1backgroundColor(Qt::white, m_settingsPrefix + "/cylon/p1/backgroundColor")
    , m_p2Brightness(100, m_settingsPrefix + "/cylon/p2/brightness")
    , m_p2Curve(Interpolation::Curve::Linear, m_settingsPrefix + "/cylon/p2/curve")
    , m_p2CurveAmplitude(1.0, m_settingsPrefix + "/cylon/p2/amplitude")
    , m_p2foregroundColor(Qt::blue, m_settingsPrefix + "/cylon/p2/foregroundColor")
    , m_p2backgroundColor(Qt::white, m_settingsPrefix + "/cylon/p2/backgroundColor")
    , m_unificationKind(UnificationKindObject::Kind::Separate, m_settingsPrefix + "/cylon/unificationKind")
{
}

IntegerObject &CylonConfig::eyeLength() {
    return m_eyeLength;
}

IntegerObject &CylonConfig::cycleDuration() {
    return m_cycleDuration;
}

IntegerObject &CylonConfig::p1Brightness() {
    return m_p1Brightness;
}

IntegerObject &CylonConfig::p2Brightness() {
    return m_p2Brightness;
}

InterpolationCurveObject &CylonConfig::p1Curve() {
    return m_p1Curve;
}

QRealObject &CylonConfig::p1CurveAmplitude() {
    return m_p1CurveAmplitude;
}

ColorObject &CylonConfig::p1ForegroundColor() {
    return m_p1foregroundColor;
}

ColorObject &CylonConfig::p1BackgroundColor() {
    return m_p1backgroundColor;
}

InterpolationCurveObject &CylonConfig::p2Curve() {
    return m_p2Curve;
}

QRealObject &CylonConfig::p2CurveAmplitude() {
    return m_p2CurveAmplitude;
}

ColorObject &CylonConfig::p2ForegroundColor() {
    return m_p2foregroundColor;
}

ColorObject &CylonConfig::p2BackgroundColor() {
    return m_p2backgroundColor;
}

UnificationKindObject &CylonConfig::unificationKind() {
    return m_unificationKind;
}

void CylonConfig::init(QSettings *settings) {
    assert(settings);
    m_eyeLength.attachSettings(settings);
    m_cycleDuration.attachSettings(settings);
    m_p1Brightness.attachSettings(settings);
    m_p1Curve.attachSettings(settings);
    m_p1CurveAmplitude.attachSettings(settings);
    m_p1foregroundColor.attachSettings(settings);
    m_p1backgroundColor.attachSettings(settings);
    m_p2Curve.attachSettings(settings);
    m_p2CurveAmplitude.attachSettings(settings);
    m_p2Brightness.attachSettings(settings);
    m_p2foregroundColor.attachSettings(settings);
    m_p2backgroundColor.attachSettings(settings);
    m_unificationKind.attachSettings(settings);
}

void CylonConfig::setLEDController(LEDController *controller) {
    auto p1Curve = Interpolation(m_p1Curve, m_p1CurveAmplitude);
    auto p2Curve = Interpolation(m_p2Curve, m_p2CurveAmplitude);
    controller->cylon(m_eyeLength,
                      m_cycleDuration,
                      m_p1Brightness,
                      p1Curve.easingCurve(),
                      m_p1foregroundColor,
                      m_p1backgroundColor,
                      m_p2Brightness,
                      p2Curve.easingCurve(),
                      m_p2foregroundColor,
                      m_p2backgroundColor,
                      m_unificationKind);
}
