#ifndef RAMPUP_H
#define RAMPUP_H

#include "ledalgo.h"

class RampUp : public LEDAlgo
{
public:
    RampUp(int duration,
           QEasingCurve p1InterpolationCurve,
           QColor p1Color,
           int p1MinBrightness,
           int p1MaxBrightness,
           QEasingCurve p2InterpolationCurve,
           QColor p2Color,
           int p2MinBrightness,
           int p2MaxBrightness,
           bool unified,
           bool loop);

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
    int m_duration;
    QEasingCurve m_p1InterpolationCurve;
    QColor m_p1Color;
    int m_p1MinBrightness;
    int m_p1MaxBrightness;
    QEasingCurve m_p2InterpolationCurve;
    QColor m_p2Color;
    int m_p2MinBrightness;
    int m_p2MaxBrightness;
    bool m_unified;
    bool m_loop;


    // Computed values
    bool m_isFinished = false;
    int m_p1BrightnessRange;
    int m_p2BrightnessRange;
};

#endif // RAMPUP_H
