#include "ledidleconfiguration.h"
#include <QSettings>

LEDIdleConfiguration::LEDIdleConfiguration(QObject *parent)
    :QObject(parent)
    , m_duration(3000, "LEDIdleConfig/p1/duration")
    , m_useP1ForBoth(true, "LEDIdleConfig/useP1ForBoth")
    , m_p1Interpolation(Interpolation::Curve::Linear, "LEDIdleConfig/p1/interpolation")
    , m_p1MinBrightness(10, "LEDIdleConfig/p1/minBrightness")
    , m_p1MaxBrightness(100, "LEDIdleConfig/p1/maxBrightness")
    , m_p1Color(QColor::fromRgb(255,0,0), "LEDIdleConfig/p1/color")
    , m_p2Interpolation(Interpolation::Curve::Linear, "LEDIdleConfig/p2/interpolation")
    , m_p2MinBrightness(10, "LEDIdleConfig/p2/minBrightness")
    , m_p2MaxBrightness(100, "LEDIdleConfig/p2/maxBrightness")
    , m_p2Color(QColor::fromRgb(0,0,255), "LEDIdleConfig/p2/color")
{ }

void LEDIdleConfiguration::loadSettings(QSettings *settings) {
    // Connecting all of the associated settings values.
    m_duration.attachSettings(settings);
    m_useP1ForBoth.attachSettings(settings);
    m_p1Interpolation.attachSettings(settings);
    m_p1MinBrightness.attachSettings(settings);
    m_p1MaxBrightness.attachSettings(settings);
    m_p1Color.attachSettings(settings);
    m_p2Interpolation.attachSettings(settings);
    m_p2MinBrightness.attachSettings(settings);
    m_p2MaxBrightness.attachSettings(settings);
    m_p2Color.attachSettings(settings);
}


IntegerObject& LEDIdleConfiguration::cycleDuration() {
    return m_duration;
}

BooleanObject& LEDIdleConfiguration::useP1ForBoth() {
    return m_useP1ForBoth;
}

InterpolationCurveObject& LEDIdleConfiguration::p1Interpolation() {
    return m_p1Interpolation;
}

IntegerObject& LEDIdleConfiguration::p1MinBrightness() {
    return m_p1MinBrightness;
}

IntegerObject& LEDIdleConfiguration::p1MaxBrightness() {
    return m_p1MaxBrightness;
}

ColorObject& LEDIdleConfiguration::p1Color() {
    return m_p1Color;
}

InterpolationCurveObject& LEDIdleConfiguration::p2Interpolation() {
    return m_p2Interpolation;
}

IntegerObject& LEDIdleConfiguration::p2MinBrightness() {
    return m_p2MinBrightness;
}

IntegerObject& LEDIdleConfiguration::p2MaxBrightness() {
    return m_p2MaxBrightness;
}

ColorObject& LEDIdleConfiguration::p2Color() {
    return m_p2Color;
}
