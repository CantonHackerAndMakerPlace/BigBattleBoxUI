#ifndef CYLON_H
#define CYLON_H

#include "ledalgo.h"
#include "unificationkindobject.h"

class Cylon : public LEDAlgo
{
public:
    Cylon(int eyeLength,
          int duration,
          int p1Brightness,
          QEasingCurve p1InterpolationCurve,
          QColor p1ForegroundColor,
          QColor p1BackgroundColor,
          int p2Brightness,
          QEasingCurve p2InterpolationCurve,
          QColor p2ForegroundColor,
          QColor p2BackgroundColor,
          UnificationKindObject::Kind unificationKind);

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
    int m_eyeLength;
    int m_duration;
    int m_p1Brightness;
    QEasingCurve m_p1InterpolationCurve;
    QColor m_p1ForegroundColor;
    QColor m_p1BackgroundColor;
    int m_p2Brightness;
    QEasingCurve m_p2InterpolationCurve;
    QColor m_p2ForegroundColor;
    QColor m_p2BackgroundColor;
    UnificationKindObject::Kind m_unificationKind;

    // Computation used to track the eye's position.
    int m_p1CurrentEyeOffset;
    int m_p1SpaceToTraverse;
    int m_p2CurrentEyeOffset;
    int m_p2SpaceToTraverse;

};

#endif // CYLON_H
