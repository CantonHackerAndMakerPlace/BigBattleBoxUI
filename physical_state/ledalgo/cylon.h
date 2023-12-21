#ifndef CYLON_H
#define CYLON_H

#include "ledalgo.h"

class Cylon : public LEDAlgo
{
public:
    Cylon(int startIndex,
        int stopIndex,
        int eyeLength,
        int duration,
        int brightness,
        QEasingCurve interpolationCurve,
        QColor p1foregroundColor,
        QColor p1backgroundColor,
        QColor p2foregroundColor,
        QColor p2backgroundColor,
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
    int m_startIndex;
    int m_stopIndex;
    int m_eyeLength;
    int m_duration;
    int m_brightness;
    QEasingCurve m_interpolationCurve;
    QColor m_p1foregroundColor;
    QColor m_p1backgroundColor;
    QColor m_p2foregroundColor;
    QColor m_p2backgroundColor;
    bool m_unified;
};

#endif // CYLON_H
