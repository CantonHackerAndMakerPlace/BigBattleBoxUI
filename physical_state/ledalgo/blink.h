#ifndef BLINK_H
#define BLINK_H

#include "ledalgo.h"
#include <QObject>

class Blink : public LEDAlgo
{
public:
    Blink(int numberOfBlinks,
          int onDuration,
          int offDuration,
          QColor p1OnColor,
          int p1ColorBrightness,
          QColor p1OffColor,
          int p1OffColorBrightness,
          QColor p1FinalColor,
          int p1FinalColorBrightness,
          QColor p2OnColor,
          int p2ColorBrightness,
          QColor p2OffColor,
          int p2OffColorBrightness,
          QColor p2FinalColor,
          int p2FinalColorBrightness,
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
    int m_numberOfBlinks;
    int m_onDuration;
    int m_offDuration;
    QColor m_p1OnColor;
    int m_p1ColorBrightness;
    QColor m_p1OffColor;
    int m_p1OffColorBrightness;
    QColor m_p1FinalColor;
    int m_p1FinalColorBrightness;
    QColor m_p2OnColor;
    int m_p2ColorBrightness;
    QColor m_p2OffColor;
    int m_p2OffColorBrightness;
    QColor m_p2FinalColor;
    int m_p2FinalColorBrightness;
    bool m_unified;
};

#endif // BLINK_H
