#include "breath.h"

Breath::Breath(int duration,
               int p1MinBrightness,
               int p1MaxBrightness,
               QColor p1Color,
               QEasingCurve p1EasingCurve,
               int p2MinBrightness,
               int p2MaxBrightness,
               QColor p2Color,
               QEasingCurve p2EasingCurve,
               bool unified)
    :m_duration(duration),
    m_p1MinBrightness(p1MinBrightness),
    m_p1MaxBrightness(p1MaxBrightness),
    m_p1Color(p1Color),
    m_p2MinBrightness(p2MinBrightness),
    m_p2MaxBrightness(p2MaxBrightness),
    m_p2Color(p2Color),
    m_unified(unified),
    m_p1EasingCurve(p1EasingCurve),
    m_p2EasingCurve(p2EasingCurve)
{

}

void Breath::start(GeneralLEDConfiguration *generalConfig, ArduinoClient *client) {
    if (m_unified) {
        client->setGlobalColor(m_p1Color);
        client->setAllBrightness(m_p1MinBrightness, true);
    } else {
        client->p1SetColor(m_p1Color);
        client->p2SetColor(m_p2Color);
        client->p1SetBrightness(m_p1MinBrightness);
        client->p2SetBrightness(m_p2MinBrightness, true);
    }
}

void Breath::update(GeneralLEDConfiguration*, qint64 elapsedTime, ArduinoClient *client) {
    // 0 means that we are going from min to max,
    // 1 means max to min.
    int inOrOut = (elapsedTime / m_duration) % 2;

    // This is the number of milliseconds into a cycle.
    int cycleTime = elapsedTime % m_duration;

    // Mapping the cycleTime into a number between 0 and 1 represented as a
    // percentage of the duration.
    qreal percentageOfTimeElapsed = (cycleTime * 1.0) / (m_duration * 1.0);

    // Mapping progress using easing curve function.
    qreal p1CurveValue = m_p1EasingCurve.valueForProgress(percentageOfTimeElapsed);

    // Converting to a brightness value.
    int p1BrightnessMagnatude = m_p1MaxBrightness - m_p1MinBrightness;

    // We need to calculate the current brightness value.
    if (inOrOut) {

        // Moving the new brightness back into the correct domain between min and max.
        // Because some of the curves don't always result in a positive value we allow
        // values to go below the min but we limit that value to being zero.
        int p1NewBrightness = std::min(m_p1MaxBrightness, std::max(0, int(floor(p1BrightnessMagnatude * p1CurveValue)) + m_p1MinBrightness));
        if (m_unified) {
            client->setAllBrightness(p1NewBrightness, true);
        } else {
            qDebug() <<"Skipping non unified implementation for now.";
            // Converting player twos breath using their own curve.
//            qreal p2CurveValue = m_p2EasingCurve.valueForProgress(percentageOfTimeElapsed);
        }
    } else {
//        qDebug() << "handling breath out case instead of breath in.";
        // Converting from counting up to counting down.
        qreal p1InvertedCurveValue = 1.0 - p1CurveValue;

        int p1NewBrightness = std::min(m_p1MaxBrightness, std::max(0, int(floor(p1BrightnessMagnatude * p1InvertedCurveValue)) + m_p1MinBrightness));
        if (m_unified) {
            client->setAllBrightness(p1NewBrightness, true);
        }
    }
}

bool Breath::loops() const { return true; }

bool Breath::isFinished() const { return false; }
