#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QEasingCurve>
#include <QColor>
#include <QDateTime>

#include <chrono>

#include <physical_state/ledalgo/ledalgo.h>
#include "unificationkindobject.h"


class LEDConfiguration;
class QTimer;
class GeneralLEDConfiguration;
class ArduinoClient;
class DeathMatchPlayerReady;

using LEDAlgoPointerType = std::shared_ptr<LEDAlgo>;
using DMPlayersReadyAlgoPointerType = std::shared_ptr<DeathMatchPlayerReady>;

/// The LEDController is responsible for sending information to the
/// arduino through the messanger in order to construct light patterns.
class LEDController : public QObject
{
    Q_OBJECT
public:
    explicit LEDController(LEDConfiguration *config, ArduinoClient *client, QObject *parent = nullptr);

public slots:
    /// Enter the off state.
    void off();

    /// Enter the breath state. Breath is always unified and both p1 and p2 are always
    /// the same color.
    void breath(int duration,
                int p1MinBrightness,
                int p1MaxBrightness,
                QColor p1Color,
                QEasingCurve p1EasingCurve,
                int p2MinBrightness,
                int p2MaxBrightness,
                QColor p2Color,
                QEasingCurve p2EasingCurve5,
                bool unified);

    /// Consumes the underlying color and fills up the LED strips either independently
    /// or together. The unified parameter will ignore p1 color settings and just use
    /// p1 settings for the entire strip.
    void countDownFill(int duration,
                       bool loop,
                       int timeBetweenLoop,
                       QEasingCurve p1EasingCurve,
                       int p1Brightness,
                       QColor p1ConsumedColor,
                       QColor p1Countolor,
                       QColor p1FinalColor,
                       int p1FinalColorBrightness,
                       QEasingCurve p2EasingCurve,
                       int p2Brightness,
                       QColor p2ConsumedColor,
                       QColor p2CountColor,
                       QColor p2FinalColor,
                       int p2FinalColorBrightness,
                       UnificationKindObject::Kind unificationStyle);

    /// Enter the blink state for the number of blinks and end both with the final color.
    void blink(int numberOfBlinks,
               int onDuration,
               int offDuration,
               QColor p1OnColor,
               int p1ColorBrightness,
               QColor p1OffColor,
               int p1OffColorBrightness,
               QColor p2OnColor,
               int p2ColorBrightness,
               QColor p2OffColor,
               int p2OffColorBrightness,
               bool unified);


    /// Enter the sweaping eye state.
    void cylon(int eyeLength,
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

    /// Enters the solid colors state where don't do anything but display a
    /// specififc color at a specified brightness.
    void solidColors(QColor p1Color, int p1brightness, QColor p2Color, int p2brightness, bool unified);

    /// Ramp up to a brightness using the specified colors.
    void rampUp(int duration,
                QEasingCurve p1Curve,
                QColor p1Color,
                int p1MinBrightness,
                int p1MaxBrightness,
                QEasingCurve p2Curve,
                QColor p2Color,
                int p2MinBrightness,
                int p2MaxBrightness,
                bool unified,
                bool loop);

    void canSendMessages();
    void unableToSendMessages();

    // light transition slots.
    void enterConfigurationScreen();
    void enterGameSelectScreen();
    void enterDMConfigScreen();
    void enterDMCountDownScreen();
    void postEnterDMCountDownScreen();
    void enterDMPlayersReadyScreen();
    void leaveDMPlayersReadyScreen();
    void enterDMRunningScreen();
    void enterDMWinnerDisplayScreen(QString playerName);
    void enterSoccerConfigScreen();
    void enterSoccerPlayersReadyScreen();
    void enterSoccerRunningScreen();
    void enterSoccerCountDownScreen();
    void enterSoccerGameOverScreen();

    // This must be connected inside of the battlebox main window I think.
    void DMCDstart3();
    void DMCDstart2();
    void DMCDstart1();
    void DMCDstartFight();

    void dmPlayerOneWins(QString name);
    void dmPlayerTwoWins(QString name);
signals:
    void dmPlayerOneReady();
    void dmPlayerOneCancelledReady();
    void dmPlayerOneCantBeReady();

    void dmPlayerTwoReady();
    void dmPlayerTwoCancelledReady();
    void dmPlayerTwoCantBeReady();
    // Algorithm finished
    void algoFinished();
private slots:

    void onTick();

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
    QDateTime m_startTime;

    /// Used to send messages to the arduino
    ArduinoClient *m_client;

    /// The general LED configuration. This is used in order to
    /// configure any underlying algorithms based on the number
    /// of lights and orientation.
    LEDConfiguration *m_config;

    LEDAlgoPointerType m_algo;

    DMPlayersReadyAlgoPointerType m_dmPlayersReady;
};

#endif // LEDCONTROLLER_H
