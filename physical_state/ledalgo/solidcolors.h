#ifndef SOLIDCOLORS_H
#define SOLIDCOLORS_H

#include "ledalgo.h"

class SolidColors : public LEDAlgo
{
public:
    SolidColors(QColor p1Color,
                int p1brightness,
                QColor p2Color,
                int p2brightness,
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
    int m_p1brightness;
    QColor m_p2Color;
    int m_p2brightness;
    bool m_unified;
};

#endif // SOLIDCOLORS_H
