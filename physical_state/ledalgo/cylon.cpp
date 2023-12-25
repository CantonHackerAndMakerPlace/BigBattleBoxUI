#include "cylon.h"

Cylon::Cylon(int startIndex,
             int stopIndex,
             int eyeLength,
             int duration,
             int brightness,
             QEasingCurve interpolationCurve,
             QColor p1foregroundColor,
             QColor p1backgroundColor,
             QColor p2foregroundColor,
             QColor p2backgroundColor,
             bool unified)
    :m_startIndex(startIndex),
    m_stopIndex(stopIndex),
    m_eyeLength(eyeLength),
    m_duration(duration),
    m_brightness(brightness),
    m_interpolationCurve(interpolationCurve),
    m_p1foregroundColor(p1foregroundColor),
    m_p1backgroundColor(p1backgroundColor),
    m_p2foregroundColor(p2foregroundColor),
    m_p2backgroundColor(p2backgroundColor),
    m_unified(unified)
{

}

void Cylon::start(GeneralLEDConfiguration *generalConfig, ArduinoClient *client) {

}

void Cylon::update(GeneralLEDConfiguration *generalConfig, qint64 elapsedTime, ArduinoClient *messanger) {

}

bool Cylon::loops() const { return true; }

bool Cylon::isFinished() const { return false; }
