#include "cylon.h"

Cylon::Cylon(int eyeLength,
             int duration,
             int p1Brightness,
             QEasingCurve p1InterpolationCurve,
             QColor p1ForegroundColor,
             QColor p1BackgroundColor,
             int p2Brightness,
             QEasingCurve p2InterpolationCurve,
             QColor p2ForegroundColor,
             QColor p2BackgroundColor,
             UnificationKindObject::Kind unificationKind)
    :m_eyeLength(eyeLength),
    m_duration(duration),
    m_p1Brightness(p1Brightness),
    m_p1InterpolationCurve(p1InterpolationCurve),
    m_p1ForegroundColor(p1ForegroundColor),
    m_p1BackgroundColor(p1BackgroundColor),
    m_p2Brightness(p2Brightness),
    m_p2InterpolationCurve(p2InterpolationCurve),
    m_p2ForegroundColor(p2ForegroundColor),
    m_p2BackgroundColor(p2BackgroundColor),
    m_unificationKind(unificationKind)
{ }

void Cylon::start(GeneralLEDConfiguration *generalConfig, ArduinoClient *client) {
    switch(m_unificationKind) {
    case UnificationKindObject::Kind::BothSame:
        client->p1SetBrightness(m_p1Brightness);
        client->p1SetColor(m_p1BackgroundColor);
        client->p1Fill(m_p1ForegroundColor, 0, m_eyeLength);

        client->p2SetBrightness(m_p1Brightness);
        client->p2SetColor(m_p1BackgroundColor);
        client->p2Fill(m_p1ForegroundColor, 0, m_eyeLength, true);
        break;
    case UnificationKindObject::Kind::Separate:
        client->p1SetBrightness(m_p1Brightness);
        client->p1SetColor(m_p1BackgroundColor);
        client->p1Fill(m_p1ForegroundColor, 0, m_eyeLength);
        client->p2SetBrightness(m_p2Brightness);
        client->p2SetColor(m_p2BackgroundColor);
        client->p2Fill(m_p2ForegroundColor, 0, m_eyeLength, true);
        break;
    case UnificationKindObject::Kind::SuperStrip:
        client->p1SetBrightness(m_p1Brightness);
        client->p1SetColor(m_p1BackgroundColor);
        client->p1Fill(m_p1ForegroundColor, 0, m_eyeLength);
        client->p2SetBrightness(m_p1Brightness);
        client->p2SetColor(m_p1BackgroundColor, true);
        break;
    }
    m_p1CurrentEyeOffset = 0;
    m_p1SpaceToTraverse = generalConfig->playerOneLedCount() - m_eyeLength;
    m_p2CurrentEyeOffset = 0;
    m_p2SpaceToTraverse = generalConfig->playerTwoLedCount() - m_eyeLength;
}

void Cylon::update(GeneralLEDConfiguration *generalConfig, qint64 elapsedTime, ArduinoClient *client) {
    // over is 0 back is 1.
    int overOrBack = (elapsedTime / m_duration) % 2;
    if (overOrBack == 0) {
        generalConfig->playerTwoLedCount() - m_eyeLength;
    } else {

    }
//    int m_eyeLength;
//    int m_duration;
//    int m_p1Brightness;
//    QEasingCurve m_p1InterpolationCurve;
//    QColor m_p1ForegroundColor;
//    QColor m_p1BackgroundColor;
//    int m_p2Brightness;
//    QEasingCurve m_p2InterpolationCurve;
//    QColor m_p2ForegroundColor;
//    QColor m_p2BackgroundColor;
//    UnificationKindObject::Kind m_unificationKind;

}

bool Cylon::loops() const { return true; }

bool Cylon::isFinished() const { return false; }
