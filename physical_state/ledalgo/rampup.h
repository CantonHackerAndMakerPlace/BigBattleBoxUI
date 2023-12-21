#ifndef RAMPUP_H
#define RAMPUP_H

#include "ledalgo.h"

class RampUp : public LEDAlgo
{
public:
    RampUp(QColor p1Color,
           int p1MinBrightness,
           int p1MaxBrightness,
           QColor p2Color,
           int p2MinBrightness,
           int p2MaxBrightness,
           bool unified);

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
    QColor m_p1Color;
    int m_p1MinBrightness;
    int m_p1MaxBrightness;
    QColor m_p2Color;
    int m_p2MinBrightness;
    int m_p2MaxBrightness;
    bool m_unified;
};

#endif // RAMPUP_H
