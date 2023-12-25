#ifndef LIGHTOFF_H
#define LIGHTOFF_H

#include "ledalgo.h"

class LightsOff : public LEDAlgo
{
public:
    LightsOff();

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
    bool m_isFinished = false;
};

#endif // LIGHTOFF_H
