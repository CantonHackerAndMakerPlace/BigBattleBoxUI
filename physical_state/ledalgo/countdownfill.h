#ifndef COUNTDOWNFILL_H
#define COUNTDOWNFILL_H

#include "ledalgo.h"
#include <QObject>

class CountDownFill : public LEDAlgo
{
public:
    CountDownFill(int duration,
                  int p1brightness,
                  QEasingCurve easingCurve,
                  QColor p1ConsumedColor,
                  QColor p1Countolor,
                  QColor p1FinalColor,
                  int p2brightness,
                  int p1FinalColorBrightness,
                  QColor p2ConsumedColor,
                  QColor p2CountColor,
                  QColor p2FinalColor,
                  int p2FinalColorBrightness,
                  bool unifiedLedStrips);

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
    qint64 m_duration;
    int m_p1Brightness;
    QEasingCurve m_easingCurve;
    QColor m_p1ConsumedColor;
    QColor m_p1Countolor;
    QColor m_p1FinalColor;
    int m_p1FinalColorBrightness;
    int m_p2Brightness;
    QColor m_p2ConsumedColor;
    QColor m_p2CountColor;
    QColor m_p2FinalColor;
    int m_p2FinalColorBrightness;
    bool m_unifiedLedStrips;
};

#endif // COUNTDOWNFILL_H
