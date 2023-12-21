#include "blink.h"

Blink::Blink(int numberOfBlinks,
             int onDuration,
             int offDuration,
             QColor p1OnColor,
             int p1ColorBrightness,
             QColor p1OffColor,
             int p1OffColorBrightness,
             QColor p1FinalColor,
             int p1FinalColorBrightness,
             QColor p2OnColor,
             int p2ColorBrightness,
             QColor p2OffColor,
             int p2OffColorBrightness,
             QColor p2FinalColor,
             int p2FinalColorBrightness,
             bool unified)
    :
    m_numberOfBlinks(numberOfBlinks),
    m_onDuration(onDuration),
    m_offDuration(offDuration),
    m_p1OnColor(p1OnColor),
    m_p1ColorBrightness(p1ColorBrightness),
    m_p1OffColor(p1OffColor),
    m_p1OffColorBrightness(p1OffColorBrightness),
    m_p1FinalColor(p1FinalColor),
    m_p1FinalColorBrightness(p1FinalColorBrightness),
    m_p2OnColor(p2OnColor),
    m_p2ColorBrightness(p2ColorBrightness),
    m_p2OffColor(p2OffColor),
    m_p2OffColorBrightness(p2OffColorBrightness),
    m_p2FinalColor(p2FinalColor),
    m_p2FinalColorBrightness(p2FinalColorBrightness),
    m_unified(unified)
{

}

void Blink::start(GeneralLEDConfiguration *generalConfig) {

}

void Blink::updateConfig(GeneralLEDConfiguration *generalConfig) {

}

void Blink::update(qint64 elapsedTime, ArduinoMessanger *messanger) {

}

bool Blink::loops() const {
    return true;
}

bool Blink::isFinished() const {
    return false;
}
