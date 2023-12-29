#include "ledidleconfiguration.h"
#include <QSettings>

LEDIdleConfiguration::LEDIdleConfiguration(QObject *parent)
    :QObject(parent)
    , m_algoConfig(new LEDAlgoConfig("IdleConfiguration", this))
{
    qDebug() << "Constructing LEDIdleConfiguration";
}

LEDAlgoConfig &LEDIdleConfiguration::algoConfig() {
    return *m_algoConfig;
}

void LEDIdleConfiguration::loadSettings(QSettings *settings) {
    assert(settings);
    qDebug() << "Initializing settings for LEDIdleConfiguration";
    // Connecting all of the associated settings values.
    m_algoConfig->init(settings);
}


//IntegerObject& LEDIdleConfiguration::cycleDuration() {
//    return m_duration;
//}

//BooleanObject& LEDIdleConfiguration::useP1ForBoth() {
//    return m_useP1ForBoth;
//}

//InterpolationCurveObject& LEDIdleConfiguration::p1Interpolation() {
//    return m_p1Interpolation;
//}

//IntegerObject& LEDIdleConfiguration::p1MinBrightness() {
//    return m_p1MinBrightness;
//}

//IntegerObject& LEDIdleConfiguration::p1MaxBrightness() {
//    return m_p1MaxBrightness;
//}

//ColorObject& LEDIdleConfiguration::p1Color() {
//    return m_p1Color;
//}

//InterpolationCurveObject& LEDIdleConfiguration::p2Interpolation() {
//    return m_p2Interpolation;
//}

//IntegerObject& LEDIdleConfiguration::p2MinBrightness() {
//    return m_p2MinBrightness;
//}

//IntegerObject& LEDIdleConfiguration::p2MaxBrightness() {
//    return m_p2MaxBrightness;
//}

//ColorObject& LEDIdleConfiguration::p2Color() {
//    return m_p2Color;
//}
