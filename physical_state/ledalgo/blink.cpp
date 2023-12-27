#include "blink.h"

Blink::Blink(int numberOfBlinks,
             int onDuration,
             int offDuration,
             QColor p1OnColor,
             int p1ColorBrightness,
             QColor p1OffColor,
             int p1OffColorBrightness,
             QColor p2OnColor,
             int p2ColorBrightness,
             QColor p2OffColor,
             int p2OffColorBrightness,
             bool unified)
    :
    m_numberOfBlinks(numberOfBlinks),
    m_onDuration(onDuration),
    m_offDuration(offDuration),
    m_p1OnColor(p1OnColor),
    m_p1ColorBrightness(p1ColorBrightness),
    m_p1OffColor(p1OffColor),
    m_p1OffColorBrightness(p1OffColorBrightness),
    m_p2OnColor(p2OnColor),
    m_p2ColorBrightness(p2ColorBrightness),
    m_p2OffColor(p2OffColor),
    m_p2OffColorBrightness(p2OffColorBrightness),
    m_unified(unified)
{

}

void Blink::start(GeneralLEDConfiguration *generalConfig, ArduinoClient *client) {

}

void Blink::update(GeneralLEDConfiguration *generalConfig, qint64 elapsedTime, ArduinoClient *messanger) {

}

bool Blink::loops() const {
    return true;
}

bool Blink::isFinished() const {
    return false;
}
