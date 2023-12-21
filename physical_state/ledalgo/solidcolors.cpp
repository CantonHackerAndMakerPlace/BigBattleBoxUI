#include "solidcolors.h"

SolidColors::SolidColors(
    QColor p1Color,
    int p1brightness,
    QColor p2Color,
    int p2brightness,
    bool unified)
:
    m_p1Color(p1Color),
    m_p1brightness(p1brightness),
    m_p2Color(p2Color),
    m_p2brightness(p2brightness),
    m_unified(unified)
{

}

void SolidColors::start(GeneralLEDConfiguration *generalConfig) {

}

void SolidColors::updateConfig(GeneralLEDConfiguration *generalConfig) {

}

void SolidColors::update(qint64 elapsedTime, ArduinoMessanger *messanger) {

}

bool SolidColors::loops() const {
    return true;
}

bool SolidColors::isFinished() const {
    return false;
}
