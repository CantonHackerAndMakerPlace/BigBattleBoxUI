#include "deathmatchplayerready.h"

DeathMatchPlayerReady::DeathMatchPlayerReady(PlayerReadyLEDLightConfiguration *config)
    : QObject{nullptr}
    , m_config(config)
{ }

void DeathMatchPlayerReady::start(GeneralLEDConfiguration *generalConfig, ArduinoClient *client) {
    m_client = client;
    QColor p1Color = m_config->p1NotReadyColor();
    int p1Brightness = m_config->p1NotReadyBrightness();
    QColor p2Color = m_config->p2NotReadyColor();
    int p2Brightness = m_config->p2NotReadyBrightness();

    // Handling processing of it.
    m_client->p1SetBrightness(p1Brightness);
    m_client->p1SetColor(p1Color);
    m_client->p2SetBrightness(p2Brightness);
    m_client->p2SetColor(p2Color, true);
    m_isRunning = true;
}

void DeathMatchPlayerReady::update(GeneralLEDConfiguration *generalConfig, qint64 elapsedTime, ArduinoClient *client) {
    if (m_p1StartBlinking) {
        m_p1IsBlinking = true;
        m_p1StartBlinking = false;
        m_p1BlinkStartTime = elapsedTime;
        m_p1CurrentPhaseIsOn = true;
        m_p1NumberOfBlinks = 0;
        client->p1SetBrightness(m_config->p1BlinkOnBrightness());
        client->p1SetColor(m_config->p1BlinkOnColor());
    }
    if (m_p1IsBlinking) {
        handleP1Blink(elapsedTime);
    }

    if (m_p2StartBlinking) {
        m_p2IsBlinking = true;
        m_p2StartBlinking = false;
        m_p2BlinkStartTime = elapsedTime;
        m_p2CurrentPhaseIsOn = true;
        m_p2NumberOfBlinks = 0;
        client->p2SetBrightness(m_config->p2BlinkOnBrightness());
        client->p2SetColor(m_config->p2BlinkOnColor());
    }
    if (m_p2IsBlinking) {
        handleP2Blink(elapsedTime);
    }
}

void DeathMatchPlayerReady::handleP1Blink(qint64 elapsedTime) {
    qint64 computedElapsedTime = elapsedTime - m_p1BlinkStartTime;
    int totalTime = m_config->onDuration() + m_config->offDuration();
    int moduloTime = computedElapsedTime % totalTime;
    bool isInOnPhase = moduloTime <= m_config->onDuration();

    if (isInOnPhase) {
        // This is the case when we are switching to on.
        if (!m_p1CurrentPhaseIsOn) {
            m_client->p1SetColor(m_config->p1BlinkOnColor());
            m_client->p1SetBrightness(m_config->p1BlinkOnBrightness(), true);
            m_p1CurrentPhaseIsOn = true;
        }
    } else {
        // This is the case we we are switching to off
        if (m_p1CurrentPhaseIsOn) {
            m_client->p1SetColor(m_config->p1BlinkOffColor());
            m_client->p1SetBrightness(m_config->p1BlinkOffBrightness(), true);
            m_p1CurrentPhaseIsOn = false;
            ++m_p1NumberOfBlinks;
            if (m_p1NumberOfBlinks >= m_config->numberOfBlinks()) {
                m_p1IsBlinking = false;
                m_client->p1SetBrightness(m_config->p1NotReadyBrightness());
                m_client->p1SetColor(m_config->p1NotReadyColor(), true);
            }
        }
    }
}

void DeathMatchPlayerReady::handleP2Blink(qint64 elapsedTime) {
    qint64 computedElapsedTime = elapsedTime - m_p1BlinkStartTime;
    int totalTime = m_config->onDuration() + m_config->offDuration();
    int moduloTime = computedElapsedTime % totalTime;
    bool isInOnPhase = moduloTime <= m_config->onDuration();

    if (isInOnPhase) {
        // This is the case when we are switching to on.
        if (!m_p2CurrentPhaseIsOn) {
            m_client->p2SetColor(m_config->p2BlinkOnColor());
            m_client->p2SetBrightness(m_config->p2BlinkOnBrightness(), true);
            m_p2CurrentPhaseIsOn = true;
        }
    } else {
        // This is the case we we are switching to off
        if (m_p2CurrentPhaseIsOn) {
            m_client->p2SetColor(m_config->p2BlinkOffColor());
            m_client->p2SetBrightness(m_config->p2BlinkOffBrightness(), true);
            m_p2CurrentPhaseIsOn = false;
            ++m_p2NumberOfBlinks;
            if (m_p2NumberOfBlinks >= m_config->numberOfBlinks()) {
                m_p2IsBlinking = false;
                m_client->p2SetBrightness(m_config->p2NotReadyBrightness());
                m_client->p2SetColor(m_config->p2NotReadyColor(), true);
            }
        }
    }
}

bool DeathMatchPlayerReady::loops() const {
    return true;
}

bool DeathMatchPlayerReady::isFinished() const {
    return false;
}

void DeathMatchPlayerReady::reset() {
    m_isRunning = false;
    m_p1StartBlinking = false;
    m_p1IsBlinking = false;
    m_p1BlinkStartTime = 0;
    m_p1CurrentPhaseIsOn = true;
    m_p1NumberOfBlinks = 0;
    m_p2StartBlinking = false;
    m_p2IsBlinking = false;
    m_p2BlinkStartTime = 0;
    m_p2CurrentPhaseIsOn = true;
    m_p2NumberOfBlinks = 0;
    LEDAlgo::reset();
}

void DeathMatchPlayerReady::dmPlayerOneReady() {
    if (m_isRunning) {
        m_p1IsBlinking = false;
        m_client->p1SetBrightness(m_config->p1ReadyBrightness());
        m_client->p1SetColor(m_config->p1ReadyColor(), true);
    }
}

void DeathMatchPlayerReady::dmPlayerOneCancelledReady() {
    if (m_isRunning) {
        m_p1StartBlinking = true;
    }
}

void DeathMatchPlayerReady::dmPlayerOneCantBeReady() {

}

void DeathMatchPlayerReady::dmPlayerTwoReady() {
    if (m_isRunning) {
        m_p2IsBlinking = false;
    }
}

void DeathMatchPlayerReady::dmPlayerTwoCancelledReady() {
    if (m_isRunning) {
        m_p2StartBlinking = true;
    }
}

void DeathMatchPlayerReady::dmPlayerTwoCantBeReady() {

}

void DeathMatchPlayerReady::isRunning(bool value) {
    m_isRunning = value;
}
