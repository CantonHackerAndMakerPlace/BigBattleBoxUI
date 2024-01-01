#include "countdownfill.h"
#include <algorithm>

CountDownFill::CountDownFill(int duration,
                             bool loop,
                             int timeBetweenLoop,

                             QEasingCurve p1EasingCurve,
                             int p1Brightness,
                             QColor p1ConsumingColor,
                             QColor p1InitialColor,
                             QColor p1FinalColor,
                             int p1FinalColorBrightness,

                             QEasingCurve p2EasingCurve,
                             int p2Brightness,
                             QColor p2ConsumingColor,
                             QColor p2InitialColor,
                             QColor p2FinalColor,
                             int p2FinalColorBrightness,
                             UnificationKindObject::Kind unificationStyle)
    :m_duration(duration),
    m_loop(loop),
    m_timeBetweenLoops(timeBetweenLoop),
    m_p1Brightness(p1Brightness),
    m_p1EasingCurve(p1EasingCurve),
    m_p1ConsumingColor(p1ConsumingColor),
    m_p1InitialColor(p1InitialColor),
    m_p1FinalColor(p1FinalColor),
    m_p1FinalColorBrightness(p1FinalColorBrightness),
    m_p2EasingCurve(p2EasingCurve),
    m_p2Brightness(p2Brightness),
    m_p2ConsumingColor(p2ConsumingColor),
    m_p2InitialColor(p2InitialColor),
    m_p2FinalColor(p2FinalColor),
    m_p2FinalColorBrightness(p2FinalColorBrightness),
    m_unificationStyle(unificationStyle)
{
    qDebug() << "Constructing Countdown fill with the following values"
             << "\n    Duration:" << m_duration
             << "\n    Looping enabled:" << m_loop
             << "\n    timeBetweenLoop:" << m_timeBetweenLoops
             << "\n    p1:"
             << "\n        Initial Brightness:" << m_p1Brightness
             << "\n        Easing Curve:" << m_p1EasingCurve
             << "\n        Consuming Color:" << m_p1ConsumingColor.name()
             << "\n        Initial Color:" << m_p1InitialColor.name()
             << "\n        Final Color:" << m_p1FinalColor.name()
             << "\n        Final Color brightness:" << m_p1FinalColorBrightness
             << "\n    p2:"
             << "\n        Initial Brightness:" << m_p2Brightness
             << "\n        Easing Curve:" << m_p2EasingCurve
             << "\n        Consuming Color:" << m_p2ConsumingColor.name()
             << "\n        Initial Color:" << m_p2InitialColor.name()
             << "\n        Final Color:" << m_p2FinalColor.name()
             << "\n        Final Color brightness:" << m_p2FinalColorBrightness
             << "\n    unification kind: " << UnificationKindObject::getDisplayName(m_unificationStyle)
        ;
}


void CountDownFill::start(GeneralLEDConfiguration *generalConfig, ArduinoClient *client) {
}


void CountDownFill::update(GeneralLEDConfiguration *generalConfig, qint64 elapsedTime, ArduinoClient *client) {
    // This gives us a time relative to our current LED light animation.
    qint64 timeRelativeToCurrentLoop = computeRelativeTime(elapsedTime);

    auto currentIteration = computeCurrentLoopIteration(elapsedTime);
    qint64 numberOfLightsP1 = generalConfig->playerOneLedCount();
    qint64 numberOfLightsP2 = generalConfig->playerTwoLedCount();

    switch(m_state) {
        case NotStarted:
            initialStartOfAlgorithm(client);
            // Note: We fall through here.
        case Consuming:
            {

                if (currentIteration == m_loopCounter && m_duration > timeRelativeToCurrentLoop) {
                    consumeLedStrip(client, timeRelativeToCurrentLoop, numberOfLightsP1, numberOfLightsP2);
                } else {
                    finishConsuming(client);

                }
            }
            break;
        case Waiting:
            handleWaiting(timeRelativeToCurrentLoop, currentIteration);
            break;

        case Finished:
            qDebug() << "finished";
            break;
    }
}

qint64 CountDownFill::computeRelativeTime(qint64 elapsedTime) {
    if (m_loop) {
        return elapsedTime % (m_duration + m_timeBetweenLoops);
    } else {
        return elapsedTime;
    }
}

qint64 CountDownFill::computeCurrentLoopIteration(qint64 elapsedTime) {
    if (m_loop) {
        return elapsedTime / (m_duration + m_timeBetweenLoops);
    } else {
        if (m_duration > elapsedTime) {
            return 1;
        } else {
            return 0;
        }
    }
}

bool CountDownFill::loops() const {
    return m_state != State::Finished;
}

bool CountDownFill::isFinished() const {
    return m_state == State::Finished;
}

void CountDownFill::initialStartOfAlgorithm(ArduinoClient *client) {
    switch (m_unificationStyle) {
    case UnificationKindObject::Kind::SuperStrip:
    case UnificationKindObject::Kind::BothSame:
        client->p1SetColor(m_p1InitialColor, false);
        client->p1SetBrightness(m_p1Brightness, false);
        client->p2SetColor(m_p1InitialColor, false);
        client->p2SetBrightness(m_p1Brightness, true);
        break;
    case UnificationKindObject::Kind::Separate:
        client->p1SetColor(m_p1InitialColor, false);
        client->p1SetBrightness(m_p1Brightness, false);
        client->p2SetColor(m_p2InitialColor, false);
        client->p2SetBrightness(m_p2Brightness, true);
        break;

    }
    m_state = State::Consuming;
}

void CountDownFill::finishConsuming(ArduinoClient *client) {
    switch (m_unificationStyle) {
    case UnificationKindObject::Kind::SuperStrip:
    case UnificationKindObject::Kind::BothSame:
        client->p1SetColor(m_p1FinalColor, false);
        client->p1SetBrightness(m_p1FinalColorBrightness, false);
        client->p2SetColor(m_p1FinalColor, false);
        client->p2SetBrightness(m_p1FinalColorBrightness, true);
        break;
    case UnificationKindObject::Kind::Separate:
        client->p1SetColor(m_p1FinalColor, false);
        client->p1SetBrightness(m_p1FinalColorBrightness, false);
        client->p2SetColor(m_p2FinalColor, false);
        client->p2SetBrightness(m_p2FinalColorBrightness, true);
        break;
    }

    if (m_loop) {
        m_state = Waiting;
    } else {
        m_state = Finished;
    }
}

void CountDownFill::handleWaiting(qint64 relativeTime, qint64 loopCount) {
    if (loopCount > m_loopCounter) {
        ++m_loopCounter;
        m_state = NotStarted;
    }
}

void CountDownFill::consumeLedStrip(ArduinoClient *client, qint64 relativeTime, int p1LEDCount, int p2LEDCount) {
    qreal percentageOfDurationComplete = qreal(relativeTime)/qreal(m_duration);
    // Keeping values between 0 and 1
    percentageOfDurationComplete = std::max(0.0, percentageOfDurationComplete);
    percentageOfDurationComplete = std::min(1.0, percentageOfDurationComplete);
    switch(m_unificationStyle) {

        case UnificationKindObject::Kind::BothSame:
            consumeBothSame(client, percentageOfDurationComplete);
            break;
        case UnificationKindObject::Kind::Separate:
            consumeSeparate(client, p1LEDCount, p2LEDCount, percentageOfDurationComplete);
            break;
        case UnificationKindObject::Kind::SuperStrip:
            consumeSuperStrip(client, p1LEDCount, p2LEDCount, percentageOfDurationComplete);
            break;
    }
}

void CountDownFill::consumeBothSame(ArduinoClient *client, qreal percentComplete) {
    qreal percentageOfLights = m_p1EasingCurve.valueForProgress(percentComplete);
    // Making sure to try and keep this between 0 and 1.
    percentageOfLights = std::max(0.0, percentageOfLights);
    percentageOfLights = std::min(1.0, percentageOfLights);
    client->mirroredFill(m_p1ConsumingColor, 0, percentageOfLights, true);
}

void CountDownFill::consumeSeparate(ArduinoClient *client, int p1LEDCount, int p2LEDCount, qreal percentComplete) {

    qreal p1PercentageOfLights = m_p1EasingCurve.valueForProgress(percentComplete);
    // Making sure to try and keep this between 0 and 1.
    p1PercentageOfLights = std::max(0.0, p1PercentageOfLights);
    p1PercentageOfLights = std::min(1.0, p1PercentageOfLights);
    auto p1LightCount = std::max(0, std::min(p1LEDCount, int(std::floor(p1PercentageOfLights * p1LEDCount))));
    client->p1Fill(m_p1ConsumingColor, 0, p1LightCount, false);

    qreal p2PercentageOfLights = m_p2EasingCurve.valueForProgress(percentComplete);
    // Making sure to try and keep this between 0 and 1.
    p2PercentageOfLights = std::max(0.0, p2PercentageOfLights);
    p2PercentageOfLights = std::min(1.0, p2PercentageOfLights);
    auto p2LightCount = std::max(0, std::min(p2LEDCount, int(std::floor(p2PercentageOfLights * p2LEDCount))));
    client->p2Fill(m_p2ConsumingColor, 0, p2LightCount, true);
}

void CountDownFill::consumeSuperStrip(ArduinoClient *client, int p1LEDCount, int p2LEDCount, qreal percentComplete) {

}
