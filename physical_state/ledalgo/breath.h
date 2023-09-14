#ifndef BREATH_H
#define BREATH_H

#include "ledalgo.h"

class Breath : public LEDAlgo
{
public:
    Breath(int minBrightness,
           int maxBrightness,
           int duration,
           QEasingCurve easingCurve,
           QColor color);


    /// Send the initial configuration and begin the algorithm.
    virtual void start(GeneralLEDConfiguration *generalConfig);

    /// Used to snapshot the LED configuration after start is called.
    virtual void updateConfig(GeneralLEDConfiguration *generalConfig);

    /// This is called ever 33 ish ms in to interpolate the algorithm and send messages to the arduino.
    virtual void update(qint64 elapsedTime, ArduinoMessanger *messanger);

    /// should return true if the algorithm is designed to loop and not designed
    /// to complete after some amount of time.
    virtual bool loops() const;

    /// Returns true for algorithms who don't loop, and have completed their
    /// evaluation and have haulted evaluation.
    virtual bool isFinished() const;

private:
    int minBrightness;
    int maxBrightness;
    int m_duration;
    QEasingCurve m_curve;
    QColor m_color;
};

#endif // BREATH_H
