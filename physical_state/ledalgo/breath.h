#ifndef BREATH_H
#define BREATH_H

#include "ledalgo.h"

class Breath : public LEDAlgo
{
public:
    Breath(int duration,
           int p1MinBrightness,
           int p1MaxBrightness,
           QColor p1Color,
           QEasingCurve p1EasingCurve,
           int p2MinBrightness,
           int p2MaxBrightness,
           QColor p2Color,
           QEasingCurve p2EasingCurve,
           bool unified);


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
    // Constant data used to evaluate the algorithm
    // these shouldn't change.
    int m_duration;
    int m_p1MinBrightness;
    int m_p1MaxBrightness;
    QColor m_p1Color;
    int m_p2MinBrightness;
    int m_p2MaxBrightness;
    QColor m_p2Color;
    bool m_unified;
    QEasingCurve m_p1EasingCurve;
    QEasingCurve m_p2EasingCurve;

    // Values used during the evaluation of an algorithm.
    bool m_goingUp = true;


};

#endif // BREATH_H
