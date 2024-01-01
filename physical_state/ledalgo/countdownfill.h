#ifndef COUNTDOWNFILL_H
#define COUNTDOWNFILL_H

#include "ledalgo.h"
#include <QObject>
#include "unificationkindobject.h"

class CountDownFill : public LEDAlgo
{
public:
    CountDownFill(int duration,
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
                  UnificationKindObject::Kind unificationStyle);

    /// Send the initial configuration and begin the algorithm.
    virtual void start(GeneralLEDConfiguration *generalConfig, ArduinoClient *client) override;

    /// This is called ever 33 ish ms in to interpolate the algorithm and send messages to the arduino.
    virtual void update(GeneralLEDConfiguration *generalConfig, qint64 elapsedTime, ArduinoClient *client) override;

    /// should return true if the algorithm is designed to loop and not designed
    /// to complete after some amount of time.
    virtual bool loops() const override;

    /// Returns true for algorithms who don't loop, and have completed their
    /// evaluation and have haulted evaluation.
    virtual bool isFinished() const override;

private:
    void initialStartOfAlgorithm(ArduinoClient *client);
    void finishConsuming(ArduinoClient *client);
    void handleWaiting(qint64 relativeTime, qint64 loopCount);
    void consumeLedStrip(ArduinoClient *client, qint64 relativeTime, int p1LEDCount, int p2LEDCount);

    void consumeBothSame(ArduinoClient *client, qreal percentComplete);
    void consumeSeparate(ArduinoClient *client, int p1LEDCount, int p2LEDCount, qreal percentComplete);
    void consumeSuperStrip(ArduinoClient *client, int p1LEDCount, int p2LEDCount, qreal percentComplete);
//    void setFinished(ArduinoClient *client);
    enum State {
        NotStarted,
        Consuming,
        Waiting,
        Finished,
    };

    qint64 computeRelativeTime(qint64 currentTime);
    qint64 computeCurrentLoopIteration(qint64 currentTime);

private:
    qint64 m_duration;
    int m_p1Brightness;
    bool m_loop;
    int m_timeBetweenLoops;

    QEasingCurve m_p1EasingCurve;
    QColor m_p1ConsumingColor;
    QColor m_p1InitialColor;
    QColor m_p1FinalColor;
    int m_p2Brightness;

    QEasingCurve m_p2EasingCurve;
    int m_p1FinalColorBrightness;
    QColor m_p2ConsumingColor;
    QColor m_p2InitialColor;
    QColor m_p2FinalColor;
    int m_p2FinalColorBrightness;
    UnificationKindObject::Kind m_unificationStyle;

    State m_state = State::NotStarted;
    qint64 m_loopCounter = 0;
};

#endif // COUNTDOWNFILL_H
