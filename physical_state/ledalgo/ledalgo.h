#ifndef LEDALGO_H
#define LEDALGO_H

#include <QDateTime>
#include <chrono>
#include <QColor>
#include <QEasingCurve>
#include <physical_state/arduinomessanger.h>
#include <app_state/led/generalledconfiguration.h>

class LEDAlgo
{
public:
    LEDAlgo();
    virtual ~LEDAlgo();

    /// Send the initial configuration and begin the algorithm.
    virtual void start(GeneralLEDConfiguration *generalConfig) = 0;

    /// Used to snapshot the LED configuration after start is called.
    virtual void updateConfig(GeneralLEDConfiguration *generalConfig) = 0;

    /// This is called ever 33 ish ms in to interpolate the algorithm and send messages to the arduino.
    virtual void update(qint64 elapsedTime, ArduinoMessanger *messanger) = 0;

    /// should return true if the algorithm is designed to loop and not designed
    /// to complete after some amount of time.
    virtual bool loops() const = 0;

    /// Returns true for algorithms who don't loop, and have completed their
    /// evaluation and have haulted evaluation.
    virtual bool isFinished() const = 0;
};

#endif // LEDALGO_H
