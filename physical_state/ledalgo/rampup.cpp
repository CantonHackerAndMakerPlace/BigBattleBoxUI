#include "rampup.h"

RampUp::RampUp(QColor p1Color,
               int p1MinBrightness,
               int p1MaxBrightness,
               QColor p2Color,
               int p2MinBrightness,
               int p2MaxBrightness,
               bool unified)
    :
    m_p1Color(p1Color),
    m_p1MinBrightness(p1MinBrightness),
    m_p1MaxBrightness(p1MaxBrightness),
    m_p2Color(p2Color),
    m_p2MinBrightness(p2MinBrightness),
    m_p2MaxBrightness(p2MaxBrightness),
    m_unified(unified)
{

}

void RampUp::start(GeneralLEDConfiguration *generalConfig) {

}

void RampUp::updateConfig(GeneralLEDConfiguration *generalConfig) {

}

void RampUp::update(qint64 elapsedTime, ArduinoMessanger *messanger) {

}

bool RampUp::loops() const {
    return true;
}

bool RampUp::isFinished() const {
    return false;
}
