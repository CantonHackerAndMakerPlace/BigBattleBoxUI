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

void SolidColors::start(GeneralLEDConfiguration *generalConfig, ArduinoClient *client) {

}

void SolidColors::update(GeneralLEDConfiguration *generalConfig, qint64 elapsedTime, ArduinoClient *messanger) {

}

bool SolidColors::loops() const {
    return false;
}

bool SolidColors::isFinished() const {
    return true;
}
