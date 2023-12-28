#include "countdownfill.h"

CountDownFill::CountDownFill(int duration,
                             int p1Brightness,
                             QEasingCurve easingCurve,
                             QColor p1ConsumedColor,
                             QColor p1Countolor,
                             QColor p1FinalColor,
                             int p2Brightness,
                             int p1FinalColorBrightness,
                             QColor p2ConsumedColor,
                             QColor p2CountColor,
                             QColor p2FinalColor,
                             int p2FinalColorBrightness,
                             UnificationKindObject::Style unificationStyle)
    :m_duration(duration * 1000),
    m_p1Brightness(p1Brightness),
    m_easingCurve(easingCurve),
    m_p1ConsumedColor(p1ConsumedColor),
    m_p1Countolor(p1Countolor),
    m_p1FinalColor(p1FinalColor),
    m_p1FinalColorBrightness(p1FinalColorBrightness),
    m_p2Brightness(p2Brightness),
    m_p2ConsumedColor(p2ConsumedColor),
    m_p2CountColor(p2CountColor),
    m_p2FinalColor(p2FinalColor),
    m_p2FinalColorBrightness(p2FinalColorBrightness),
    m_unificationStyle(unificationStyle)
{ }


void CountDownFill::start(GeneralLEDConfiguration *generalConfig, ArduinoClient *client) {

}


void CountDownFill::update(GeneralLEDConfiguration *generalConfig, qint64 elapsedTime, ArduinoClient *messanger) {

}

bool CountDownFill::loops() const {
    return true;
}

bool CountDownFill::isFinished() const {
    return false;
}
