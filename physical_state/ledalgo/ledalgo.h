#ifndef LEDALGO_H
#define LEDALGO_H

#include <QDateTime>
#include <chrono>
#include <QColor>
#include <QEasingCurve>
#include <physical_state/arduinoclient.h>
#include <app_state/led/generalledconfiguration.h>

class LEDAlgo
{
public:
    LEDAlgo();
    virtual ~LEDAlgo();

    /// Send the initial configuration and begin the algorithm.
    virtual void start(GeneralLEDConfiguration *generalConfig, ArduinoClient *client) = 0;

    /// This is called ever 33 ish ms in to interpolate the algorithm and send messages to the arduino.
    virtual void update(GeneralLEDConfiguration *generalConfig, qint64 elapsedTime, ArduinoClient *client) = 0;

    /// should return true if the algorithm is designed to loop and not designed
    /// to complete after some amount of time.
    virtual bool loops() const = 0;

    /// Returns true for algorithms who don't loop, and have completed their
    /// evaluation and have haulted evaluation.
    virtual bool isFinished() const = 0;

    bool wasStarted() const;
    void setWasStarted(bool wasStarted);

    virtual void reset();
protected:
    bool m_hasBeenStarted = false;
};

#endif // LEDALGO_H
