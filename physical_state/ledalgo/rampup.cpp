#include "rampup.h"

RampUpConfig::RampUpConfig(int duration,
               QEasingCurve p1InterpolationCurve,
               QColor p1Color,
               int p1MinBrightness,
               int p1MaxBrightness,
               QEasingCurve p2InterpolationCurve,
               QColor p2Color,
               int p2MinBrightness,
               int p2MaxBrightness,
               bool unified)
    :m_duration(duration),
    m_p1InterpolationCurve(p1InterpolationCurve),
    m_p1Color(p1Color),
    m_p1MinBrightness(p1MinBrightness),
    m_p1MaxBrightness(p1MaxBrightness),
    m_p2InterpolationCurve(p2InterpolationCurve),
    m_p2Color(p2Color),
    m_p2MinBrightness(p2MinBrightness),
    m_p2MaxBrightness(p2MaxBrightness),
    m_unified(unified)
{

}

void RampUpConfig::start(GeneralLEDConfiguration *generalConfig, ArduinoClient *client) {

}

void RampUpConfig::update(GeneralLEDConfiguration *generalConfig, qint64 elapsedTime, ArduinoClient *messanger) {

}

bool RampUpConfig::loops() const {
    return true;
}

bool RampUpConfig::isFinished() const {
    return false;
}
