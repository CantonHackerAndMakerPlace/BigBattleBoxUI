#include "cylonconfig.h"

CylonConfig::CylonConfig(QString const& keyPrefix, QObject *parent)
    : QObject{parent}
    , m_settingsPrefix(keyPrefix)
    , m_startIndex(0, m_settingsPrefix + "/cylon/startIndex")
    , m_stopIndex(100, m_settingsPrefix + "/cylon/stopIndex")
    , m_eyeLength(5, m_settingsPrefix + "/cylon/eyeLength")
    , m_cycleDuration(3000, m_settingsPrefix + "/cylon/duration")
    , m_p1Brightness(100, m_settingsPrefix + "/cylon/p1/brightness")
    , m_p2Brightness(100, m_settingsPrefix + "/cylon/p2/brightness")
    , m_curve(Interpolation::Curve::Linear, m_settingsPrefix + "/cylon/curve")
    , m_curveAmplitude(1.0, m_settingsPrefix + "/cylon/amplitude")
    , m_p1foregroundColor(Qt::red, m_settingsPrefix + "/cylon/p1/foregroundColor")
    , m_p1backgroundColor(Qt::white, m_settingsPrefix + "/cylon/p1/backgroundColor")
    , m_p2foregroundColor(Qt::blue, m_settingsPrefix + "/cylon/p2/foregroundColor")
    , m_p2backgroundColor(Qt::white, m_settingsPrefix + "/cylon/p2/backgroundColor")
    , m_unificationKind(UnificationKindObject::Style::Separate, m_settingsPrefix + "/cylon/unificationKind")
{ }

IntegerObject &CylonConfig::startIndex() {
    return m_startIndex;
}

IntegerObject &CylonConfig::stopIndex() {
    return m_stopIndex;
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

InterpolationCurveObject &CylonConfig::curve() {
    return m_curve;
}

QRealObject &CylonConfig::curveAmplitude() {
    return m_curveAmplitude;
}

ColorObject &CylonConfig::p1foregroundColor() {
    return m_p1foregroundColor;
}

ColorObject &CylonConfig::p1backgroundColor() {
    return m_p1backgroundColor;
}

ColorObject &CylonConfig::p2foregroundColor() {
    return m_p2foregroundColor;
}

ColorObject &CylonConfig::p2backgroundColor() {
    return m_p2backgroundColor;
}

UnificationKindObject &CylonConfig::unificationKind() {
    return m_unificationKind;
}

void CylonConfig::init(QSettings *settings) {
    m_startIndex.attachSettings(settings);
    m_stopIndex.attachSettings(settings);
    m_eyeLength.attachSettings(settings);
    m_cycleDuration.attachSettings(settings);
    m_p1Brightness.attachSettings(settings);
    m_p2Brightness.attachSettings(settings);
    m_curve.attachSettings(settings);
    m_curveAmplitude.attachSettings(settings);
    m_p1foregroundColor.attachSettings(settings);
    m_p1backgroundColor.attachSettings(settings);
    m_p2foregroundColor.attachSettings(settings);
    m_p2backgroundColor.attachSettings(settings);
    m_unificationKind.attachSettings(settings);
}

void CylonConfig::setLEDController(LEDController *controller) {
    auto curve = Interpolation(m_curve, m_curveAmplitude);
    controller->cylon(m_startIndex,
                      m_stopIndex,
                      m_eyeLength,
                      m_cycleDuration,
                      m_p1Brightness,
                      m_p2Brightness,
                      curve.easingCurve(),
                      m_p1backgroundColor,
                      m_p1foregroundColor,
                      m_p2backgroundColor,
                      m_p2foregroundColor,
                      m_unificationKind);
}
