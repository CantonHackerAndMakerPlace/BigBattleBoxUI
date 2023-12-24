#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QEasingCurve>
#include <QColor>
#include <QDateTime>

#include <chrono>

#include <physical_state/ledalgo/ledalgo.h>


class QTimer;
class GeneralLEDConfiguration;
class ArduinoClient;

/// The LEDController is responsible for sending information to the
/// arduino through the messanger in order to construct light patterns.
class LEDController : public QObject
{
    Q_OBJECT
public:
    explicit LEDController(ArduinoClient *client, QObject *parent = nullptr);

public slots:
    /// Enter the off state.
    void off();

    /// Enter the breath state. Breath is always unified and both p1 and p2 are always
    /// the same color.
    void breath(int minBrightness,
                int maxBrightness,
                int duration,
                QEasingCurve easingCurve,
                QColor color);

    /// Consumes the underlying color and fills up the LED strips either independently
    /// or together. The unified parameter will ignore p1 color settings and just use
    /// p1 settings for the entire strip.
    void CountDownFill(int duration,
                       int brightness,
                       QEasingCurve easingCurve,
                       QColor p1ConsumedColor,
                       QColor p1Countolor,
                       QColor p1FinalColor,
                       int p1FinalColorBrightness,
                       QColor p2ConsumedColor,
                       QColor p2CountColor,
                       QColor p2FinalColor,
                       int p2FinalColorBrightness,
                       bool unifiedLedStrips);

    /// Enter the blink state for the number of blinks and end both with the final color.
    void blink(int numberOfBlinks,
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


    /// Enter the sweaping eye state.
    void cylon(int startIndex,
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

    /// Enters the solid colors state where don't do anything but display a
    /// specififc color at a specified brightness.
    void solidColors(QColor p1Color, int p1brightness, QColor p2Color, int p2brightness, bool unified);

    /// Ramp up to a brightness using the specified colors.
    void rampUp(QColor p1Color,
                int p1MinBrightness,
                int p1MaxBrightness,
                QColor p2Color,
                int p2MinBrightness,
                int p2MaxBrightness,
                bool unified);
private slots:

    void onTimeout();

private:
    /// Indicates that we should send messages to the arduino.
    bool m_isReady = false;
    /// Indicates if this is the first message after we have received
    /// the first message signal, this means that additional messages
    /// may need ot be sent.
    bool m_isFirstMessageAfterReady = false;

    /// Timer used to sned messages after some amount of time has elapsed.
    QTimer *m_timer;

    /// A time stamp for when the LED display was started.
    QDateTime m_startState;

    /// Used to send messages to the arduino
    ArduinoClient *m_client;

    /// The general LED configuration. This is used in order to
    /// configure any underlying algorithms based on the number
    /// of lights and orientation.
    GeneralLEDConfiguration *m_generalConfig;

    std::shared_ptr<LEDAlgo> m_algo;
};

#endif // LEDCONTROLLER_H
