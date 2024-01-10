#include "rampup.h"

RampUp::RampUp(int duration,
               QEasingCurve p1InterpolationCurve,
               QColor p1Color,
               int p1MinBrightness,
               int p1MaxBrightness,
               QEasingCurve p2InterpolationCurve,
               QColor p2Color,
               int p2MinBrightness,
               int p2MaxBrightness,
               bool unified,
               bool loop)
    :m_duration(duration),
    m_p1InterpolationCurve(p1InterpolationCurve),
    m_p1Color(p1Color),
    m_p1MinBrightness(p1MinBrightness),
    m_p1MaxBrightness(p1MaxBrightness),
    m_p2InterpolationCurve(p2InterpolationCurve),
    m_p2Color(p2Color),
    m_p2MinBrightness(p2MinBrightness),
    m_p2MaxBrightness(p2MaxBrightness),
    m_unified(unified),
    m_loop(loop)
{
    qDebug() << "Ramp Up LED Algorithm"
             << "\n    Duration:" << m_duration
             << "\n    Use p1 for p2:" << m_unified
             << "\n    loop:" << m_loop
             << "\n    p1:"
             << "\n        Curve:" << m_p1InterpolationCurve
             << "\n        Color:" << m_p1Color
             << "\n        Min Brightness:" << m_p1MinBrightness
             << "\n        Max Brightness:" << m_p1MaxBrightness
             << "\n    p2:"
             << "\n        Curve:" << m_p2InterpolationCurve
             << "\n        Color:" << m_p2Color
             << "\n        Min Brightness:" << m_p2MinBrightness
             << "\n        Max Brightness:" << m_p2MaxBrightness
             << "\n";
}

void RampUp::start(GeneralLEDConfiguration *generalConfig, ArduinoClient *client) {
    if (m_unified) {
        client->setGlobalColor(m_p1Color);
        client->setAllBrightness(m_p1MinBrightness, true);
    } else {
        client->p1SetColor(m_p1Color);
        client->p1SetBrightness(m_p1MinBrightness);
        client->p2SetColor(m_p2Color);
        client->p2SetBrightness(m_p2MinBrightness, true);
    }
    m_p1BrightnessRange = m_p1MaxBrightness - m_p1MinBrightness;
    m_p2BrightnessRange = m_p2MaxBrightness - m_p2MinBrightness;
}

void RampUp::update(GeneralLEDConfiguration *generalConfig, qint64 elapsedTime, ArduinoClient *client) {
    if (elapsedTime > m_duration) {
        if (!m_loop) {
            // If we are not looping we need to make sure that we finish on the maximum value.
            if (m_unified) {
                client->setGlobalColor(m_p1Color);
                client->setAllBrightness(m_p1MaxBrightness, true);
            } else {
                client->p1SetColor(m_p1Color);
                client->p1SetBrightness(m_p1MaxBrightness);
                client->p2SetColor(m_p2Color);
                client->p2SetBrightness(m_p2MaxBrightness, true);
            }
            qDebug() << "Derp";
            m_isFinished = true;
            return;
        }
    }

    int remainingTime = elapsedTime % m_duration;
    qreal percentTimeComplete = std::max(0.0, std::min(1.0, qreal(remainingTime) / qreal(m_duration)));
    qreal p1InterpolatedPercent = std::round(100.0 * std::max(0.0, std::min(1.0, m_p1InterpolationCurve.valueForProgress(percentTimeComplete))))/100.0;
    int p1Brightness = (p1InterpolatedPercent * m_p1BrightnessRange) + m_p1MinBrightness;
    if (m_unified) {
        client->setAllBrightness(p1Brightness, true);
    } else {
        client->p1SetBrightness(p1Brightness);
        qreal p2InterpolatedPercent = std::round(100.0 * std::max(0.0, std::min(1.0, m_p2InterpolationCurve.valueForProgress(percentTimeComplete))))/100.0;
        int p2Brightness = (p2InterpolatedPercent * m_p2BrightnessRange) + m_p2MinBrightness;
        client->p1SetBrightness(p2Brightness, true);
    }
}

bool RampUp::loops() const {
    return m_loop;
}

bool RampUp::isFinished() const {
    return !m_loop && m_isFinished;
}
