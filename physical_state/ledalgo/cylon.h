#ifndef CYLON_H
#define CYLON_H

#include "ledalgo.h"
#include "unificationkindobject.h"

class Cylon : public LEDAlgo
{
public:
    Cylon(int startIndex,
        int stopIndex,
        int eyeLength,
        int duration,
        int p1Brightness,
        int p2Brightness,
        QEasingCurve interpolationCurve,
        QColor p1foregroundColor,
        QColor p1backgroundColor,
        QColor p2foregroundColor,
        QColor p2backgroundColor,
        UnificationKindObject::Style unificationKind);

    /// Send the initial configuration and begin the algorithm.
    virtual void start(GeneralLEDConfiguration *generalConfig, ArduinoClient *client) override;

    /// This is called ever 33 ish ms in to interpolate the algorithm and send messages to the arduino.
    virtual void update(GeneralLEDConfiguration *generalConfig, qint64 elapsedTime, ArduinoClient *messanger) override;

    /// should return true if the algorithm is designed to loop and not designed
    /// to complete after some amount of time.
    virtual bool loops() const override;

    /// Returns true for algorithms who don't loop, and have completed their
    /// evaluation and have haulted evaluation.
    virtual bool isFinished() const override;

private:
    int m_startIndex;
    int m_stopIndex;
    int m_eyeLength;
    int m_duration;
    int m_p1Brightness;
    int m_p2Brightness;
    QEasingCurve m_interpolationCurve;
    QColor m_p1foregroundColor;
    QColor m_p1backgroundColor;
    QColor m_p2foregroundColor;
    QColor m_p2backgroundColor;
    UnificationKindObject::Style m_unificationKind;
};

#endif // CYLON_H
