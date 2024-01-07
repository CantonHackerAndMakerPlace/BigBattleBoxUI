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
{
    qDebug() << "Cylon Sweep Configuration"
             << "\n    Eye Length:" << m_eyeLength
             << "\n    Duration:" << m_duration
             << "\n    Unification kind:" << UnificationKindObject::getDisplayName(m_unificationKind)
             << "\n    P1:"
             << "\n        Brightness: " << m_p1Brightness
             << "\n        Curve: " << m_p1InterpolationCurve
             << "\n        Eye Color: " << m_p1ForegroundColor
             << "\n        Background Color: " << m_p1BackgroundColor
             << "\n    P2:"
             << "\n        Brightness: " << m_p2Brightness
             << "\n        Curve: " << m_p2InterpolationCurve
             << "\n        Eye Color: " << m_p2ForegroundColor
             << "\n        Background Color: " << m_p2BackgroundColor
             <<"\n";
}

void Cylon::start(GeneralLEDConfiguration *generalConfig, ArduinoClient *client) {
    m_generalConfig = generalConfig;
    switch(m_unificationKind) {
    case UnificationKindObject::Kind::BothSame:
        client->p1SetBrightness(m_p1Brightness);
        client->p1SetColor(m_p1BackgroundColor);
        client->p1Fill(m_p1ForegroundColor, 0, m_eyeLength);
        client->p2SetBrightness(m_p1Brightness);
        client->p2SetColor(m_p1BackgroundColor);
        client->p2Fill(m_p1ForegroundColor, 0, m_eyeLength, true);

        m_p1SpaceToTraverse = generalConfig->playerOneLedCount() - m_eyeLength;
        m_p2SpaceToTraverse = generalConfig->playerTwoLedCount() - m_eyeLength;
        break;
    case UnificationKindObject::Kind::Separate:
        client->p1SetBrightness(m_p1Brightness);
        client->p1SetColor(m_p1BackgroundColor);
        client->p1Fill(m_p1ForegroundColor, 0, m_eyeLength);
        client->p2SetBrightness(m_p2Brightness);
        client->p2SetColor(m_p2BackgroundColor);
        client->p2Fill(m_p2ForegroundColor, 0, m_eyeLength, true);

        m_p1SpaceToTraverse = generalConfig->playerOneLedCount() - m_eyeLength;
        m_p2SpaceToTraverse = generalConfig->playerTwoLedCount() - m_eyeLength;
        break;
    case UnificationKindObject::Kind::SuperStrip:
        client->p1SetBrightness(m_p1Brightness);
        client->p1SetColor(m_p1BackgroundColor);
        client->p1Fill(m_p1ForegroundColor, 0, m_eyeLength);
        client->p2SetBrightness(m_p1Brightness);
        client->p2SetColor(m_p1BackgroundColor, true);

        m_p1SpaceToTraverse = generalConfig->playerTwoLedCount() + generalConfig->playerOneLedCount() - m_eyeLength;
        m_p2SpaceToTraverse = 0;
        break;
    }
}

void Cylon::update(GeneralLEDConfiguration *generalConfig, qint64 elapsedTime, ArduinoClient *client) {
    // over is 0 back is 1.
    bool goingUp = !bool((elapsedTime / m_duration) % 2);
    int timeRemaining = elapsedTime % m_duration;
    qreal percentComplete = std::min(1.0, std::max(0.0 , qreal(timeRemaining) / qreal(m_duration)));
    qDebug() << "Percent complete: " << percentComplete;
    // Going Up
    if (goingUp) {
        fillLightPosition(percentComplete, client);
    } else {
        // Going down
        percentComplete = 1 - percentComplete;
        fillLightPosition(percentComplete, client);
    }
}

bool Cylon::loops() const { return true; }

bool Cylon::isFinished() const { return false; }

void Cylon::fillLightPosition(qreal percentageComplete, ArduinoClient *client) {
    switch(m_unificationKind){

    case UnificationKindObject::Kind::BothSame:
        fillLightPositionBothSame(percentageComplete, client);
        break;
    case UnificationKindObject::Kind::Separate:
        fillLightPositionSeparate(percentageComplete, client);
        break;
    case UnificationKindObject::Kind::SuperStrip:
        fillLightPositionSuperStrip(percentageComplete, client);
        break;
    }
}


void Cylon::fillLightPositionBothSame(qreal percentageComplete, ArduinoClient *client) {
    qreal interpolatedPercentage = std::round(100.0 *std::min(1.0, std::max(0.0, m_p1InterpolationCurve.valueForProgress(percentageComplete))))/100.0;

    // Computing index of p1 and p2
    int indexInsideOfP1 = std::min(qreal(m_p1SpaceToTraverse), std::max(0.0, std::floor(interpolatedPercentage * m_p1SpaceToTraverse)));
    int indexInsideOfP2 = std::min(qreal(m_p2SpaceToTraverse), std::max(0.0, std::floor(interpolatedPercentage * m_p2SpaceToTraverse)));

    bool writeShowAll = false;

    if (m_p1CurrentIndex != indexInsideOfP1) {
        client->p1Fill(m_p1BackgroundColor, m_p1CurrentIndex, m_eyeLength);
        client->p1Fill(m_p1ForegroundColor, indexInsideOfP1, m_eyeLength);
        m_p1CurrentIndex = indexInsideOfP1;
        writeShowAll = true;
    }

    if (m_p2CurrentIndex != indexInsideOfP2) {
        client->p2Fill(m_p1BackgroundColor, m_p2CurrentIndex, m_eyeLength);
        client->p2Fill(m_p1ForegroundColor, indexInsideOfP2, m_eyeLength);
        m_p2CurrentIndex = indexInsideOfP2;
        writeShowAll = true;
    }
    if (writeShowAll) {
        client->ledShowAll();
    }
}

void Cylon::fillLightPositionSeparate(qreal percentageComplete, ArduinoClient *client) {
    qreal interpolatedPercentageP1 = std::round(100.0 *std::min(1.0, std::max(0.0, m_p1InterpolationCurve.valueForProgress(percentageComplete))))/100.0;
    qreal interpolatedPercentageP2 = std::round(100.0 *std::min(1.0, std::max(0.0, m_p2InterpolationCurve.valueForProgress(percentageComplete))))/100.0;

    int indexInsideOfP1 = std::min(qreal(m_p1SpaceToTraverse), std::max(0.0, std::floor(interpolatedPercentageP1 * m_p1SpaceToTraverse)));
    int indexInsideOfP2 = std::min(qreal(m_p2SpaceToTraverse), std::max(0.0, std::floor(interpolatedPercentageP2 * m_p2SpaceToTraverse)));

    bool writeShowAll = false;
    if (m_p1CurrentIndex != indexInsideOfP1) {
        client->p1Fill(m_p1BackgroundColor, m_p1CurrentIndex, m_eyeLength);
        client->p1Fill(m_p1ForegroundColor, indexInsideOfP1, m_eyeLength);
        m_p1CurrentIndex = indexInsideOfP1;
        writeShowAll = true;
    }

    if (m_p2CurrentIndex != indexInsideOfP2) {
        client->p2Fill(m_p2BackgroundColor, m_p2CurrentIndex, m_eyeLength);
        client->p2Fill(m_p2ForegroundColor, indexInsideOfP2, m_eyeLength);
        m_p2CurrentIndex = indexInsideOfP2;
        writeShowAll = true;
    }
    if (writeShowAll) {
        client->ledShowAll();
    }
}

void Cylon::fillLightPositionSuperStrip(qreal percentageComplete, ArduinoClient *client) {
    qreal interpolatedPercentageP1 = std::round(100.0 *std::min(1.0, std::max(0.0, m_p1InterpolationCurve.valueForProgress(percentageComplete))))/100.0;
    int indexOffset = std::min(qreal(m_p1SpaceToTraverse), std::max(0.0, std::floor(interpolatedPercentageP1 * m_p1SpaceToTraverse)));

    if (indexOffset != m_p1CurrentIndex) {
        client->contigiousFill(m_p1BackgroundColor, m_p1CurrentIndex , m_eyeLength);
        client->contigiousFill(m_p1ForegroundColor, indexOffset, m_eyeLength, true);
        m_p1CurrentIndex = indexOffset;
    }
}
