#include "solidcolors.h"

SolidColors::SolidColors(
    QColor p1Color,
    int p1brightness,
    QColor p2Color,
    int p2brightness,
    bool unified)
:
    m_p1Color(p1Color),
    m_p1Brightness(p1brightness),
    m_p2Color(p2Color),
    m_p2Brightness(p2brightness),
    m_unified(unified)
{

}

void SolidColors::start(GeneralLEDConfiguration *generalConfig, ArduinoClient *client) {
    if (m_unified) {
        client->setAllBrightness(m_p1Brightness);
        client->setGlobalColor(m_p1Color, true);
    } else {
        client->p1SetBrightness(m_p1Brightness);
        client->p1SetColor(m_p1Color);
        client->p2SetBrightness(m_p2Brightness);
        client->p2SetColor(m_p2Color, true);
    }
}

void SolidColors::update(GeneralLEDConfiguration *generalConfig, qint64 elapsedTime, ArduinoClient *messanger) {

}

bool SolidColors::loops() const {
    return false;
}

bool SolidColors::isFinished() const {
    return true;
}
