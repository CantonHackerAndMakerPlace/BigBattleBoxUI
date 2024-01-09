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
    m_p1OnColorBrightness(p1ColorBrightness),
    m_p1OffColor(p1OffColor),
    m_p1OffColorBrightness(p1OffColorBrightness),
    m_p2OnColor(p2OnColor),
    m_p2OnColorBrightness(p2ColorBrightness),
    m_p2OffColor(p2OffColor),
    m_p2OffColorBrightness(p2OffColorBrightness),
    m_unified(unified)
{
    qDebug() << "Blink LED Configuration"
             << "\n    Number of blinks:" << m_numberOfBlinks
             << "\n    Light duration for color 1:" << m_onDuration
             << "\n    Light duration for color 2:" << m_offDuration
             << "\n    Use player 1 for player 2:" << m_unified
             << "\n    P1"
             << "\n        Color 1:" << m_p1OnColor
             << "\n        Color 1 brightness:" << m_p1OnColorBrightness
             << "\n        Color 2:" << m_p1OffColor
             << "\n        Color 2 Brightness:" << m_p1OffColorBrightness
             << "\n    P2"
             << "\n        Color 1:" << m_p2OnColor
             << "\n        Color 1 brightness:" << m_p2OnColorBrightness
             << "\n        Color 2:" << m_p2OffColor
             << "\n        Color 2 Brightness:" << m_p2OffColorBrightness
             << "\n";
    m_totalTime = m_onDuration + m_offDuration;
}

void Blink::start(GeneralLEDConfiguration *generalConfig, ArduinoClient *client) {
    if (m_unified) {
        client->setAllBrightness(m_p1OnColorBrightness);
        client->setGlobalColor(m_p1OnColor, true);
    } else {
        client->p1SetColor(m_p1OnColor);
        client->p1SetBrightness(m_p1OnColorBrightness);
        client->p2SetColor(m_p2OnColor);
        client->p2SetBrightness(m_p2OnColorBrightness, true);
    }
    m_currentPhaseIsOn = true;
}

void Blink::update(GeneralLEDConfiguration *generalConfig, qint64 elapsedTime, ArduinoClient *client) {
    int moduloTime = elapsedTime % m_totalTime;
    bool isInOnPhase = moduloTime <= m_onDuration;

    if (isInOnPhase) {
        // This is the case when we are switching to on.
        if (!m_currentPhaseIsOn) {
            if (m_unified) {
                client->setAllBrightness(m_p1OnColorBrightness);
                client->setGlobalColor(m_p1OnColor, true);
            } else {
                client->p1SetColor(m_p1OnColor);
                client->p1SetBrightness(m_p1OnColorBrightness);
                client->p2SetColor(m_p2OnColor);
                client->p2SetBrightness(m_p2OnColorBrightness, true);
            }
            m_currentPhaseIsOn = true;
        }
    } else {
        // This is the case we we are switching to off
        if (m_currentPhaseIsOn) {
            if (m_unified) {
                client->setAllBrightness(m_p1OffColorBrightness);
                client->setGlobalColor(m_p1OffColor, true);
            } else {
                client->p1SetColor(m_p1OffColor);
                client->p1SetBrightness(m_p1OffColorBrightness);
                client->p2SetColor(m_p2OffColor);
                client->p2SetBrightness(m_p2OffColorBrightness, true);
            }
            m_currentPhaseIsOn = false;
            if (m_numberOfBlinks != 0) {
                ++m_blinks;
                if (m_blinks >= m_numberOfBlinks) {
                    m_isFinished = true;
                }
            }
        }
    }

}

bool Blink::loops() const {
    return true;
}

bool Blink::isFinished() const {
    return m_isFinished;
}
