#include "ledcontroller.h"
#include <physical_state/arduinoclient.h>
#include <QTimer>
#include <physical_state/ledalgo/breath.h>
#include "ledalgo/blink.h"
#include "ledalgo/cylon.h"
#include "ledalgo/breath.h"
#include "ledalgo/countdownfill.h"
#include "ledalgo/lightoff.h"
#include "ledalgo/rampup.h"
#include "ledalgo/solidcolors.h"
#include <app_state/led/ledconfiguration.h>

LEDController::LEDController(LEDConfiguration *config, ArduinoClient *client, QObject *parent)
    : QObject{parent}
    , m_timer(new QTimer(this))
    , m_client(client)
    , m_config(config)
{
    // Connecting to the messaging timer.
    connect(m_timer, &QTimer::timeout,
            this, &LEDController::onTick);

    // Try for 30 msg per second.
    m_timer->start(33);
}


void LEDController::onTick() {
    if (m_isReady && m_algo) {
        // If the algorithm has been started and we no longer need to
        // loop or is finished we can simply exit.
        if (m_algo->wasStarted() && m_algo->isFinished()) {
            return;
        }
        if (!m_algo->wasStarted()) {
            // Recording the current date and time and starting the evaluation.
            m_startTime = QDateTime::currentDateTime();
            m_algo->start(m_config->generalLEDConfiguration(), m_client);
            m_algo->setWasStarted(true);
        }
        auto elapsed = QDateTime::currentDateTime() - m_startTime;
        m_algo->update(m_config->generalLEDConfiguration(), elapsed.count(), m_client);
        if (m_algo->isFinished()) {
            // We can only do this once so check after update to see if the algorithm
            // was completed or not.
            emit algoFinished();
        }
    }
}


void LEDController::off() {
    m_algo = LEDAlgoPointerType(new LightsOff());
}

void LEDController::breath(int duration,
                           int p1MinBrightness,
                           int p1MaxBrightness,
                           QColor p1Color,
                           QEasingCurve p1EasingCurve,
                           int p2MinBrightness,
                           int p2MaxBrightness,
                           QColor p2Color,
                           QEasingCurve p2EasingCurve,
                           bool unified)
{
    m_algo = LEDAlgoPointerType(new Breath(duration,
                                           p1MinBrightness,
                                           p1MaxBrightness,
                                           p1Color,
                                           p1EasingCurve,
                                           p2MinBrightness,
                                           p2MaxBrightness,
                                           p2Color,
                                           p2EasingCurve,
                                           unified));
}

void LEDController::countDownFill(int duration,
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
                                 UnificationKindObject::Kind unificationStyle)
{
    m_algo = LEDAlgoPointerType(new CountDownFill(duration,
                                                  loop,
                                                  timeBetweenLoop,

                                                  p1EasingCurve,
                                                  p1Brightness,
                                                  p1ConsumedColor,
                                                  p1Countolor,
                                                  p1FinalColor,
                                                  p1FinalColorBrightness,

                                                  p2EasingCurve,
                                                  p2Brightness,
                                                  p2ConsumedColor,
                                                  p2CountColor,
                                                  p2FinalColor,
                                                  p2FinalColorBrightness,
                                                  unificationStyle));
}

void LEDController::blink(int numberOfBlinks,
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
                          bool unified)
{
    m_algo = LEDAlgoPointerType(new Blink(numberOfBlinks,
                                          onDuration,
                                          offDuration,
                                          p1OnColor,
                                          p1ColorBrightness,
                                          p1OffColor,
                                          p1OffColorBrightness,
                                          p2OnColor,
                                          p2ColorBrightness,
                                          p2OffColor,
                                          p2OffColorBrightness,
                                          unified));

}


/// Enter the sweaping eye state.
void LEDController::cylon(int eyeLength,
                          int duration,
                          int p1Brightness,
                          QEasingCurve p1InterpolationCurve,
                          QColor p1ForegroundColor,
                          QColor p1BackgroundColor,
                          int p2Brightness,
                          QEasingCurve p2InterpolationCurve,
                          QColor p2ForegroundColor,
                          QColor p2BackgroundColor,
                          UnificationKindObject::Kind unificationKind) {
    m_algo = LEDAlgoPointerType(new Cylon(eyeLength,
                                          duration,
                                          p1Brightness,
                                          p1InterpolationCurve,
                                          p1ForegroundColor,
                                          p1BackgroundColor,
                                          p2Brightness,
                                          p2InterpolationCurve,
                                          p2ForegroundColor,
                                          p2BackgroundColor,
                                          unificationKind));

}

/// Enters the solid colors state where don't do anything but display a
/// specififc color at a specified brightness.
void LEDController::solidColors(QColor p1Color,
                                int p1brightness,
                                QColor p2Color,
                                int p2brightness,
                                bool unified)
{
    m_algo = LEDAlgoPointerType(new SolidColors(p1Color, p1brightness, p2Color, p2brightness, unified));
}

/// Ramp up to a brightness using the specified colors.
void LEDController::rampUp(int duration,
                           QEasingCurve p1Curve,
                           QColor p1Color,
                           int p1MinBrightness,
                           int p1MaxBrightness,
                           QEasingCurve p2Curve,
                           QColor p2Color,
                           int p2MinBrightness,
                           int p2MaxBrightness,
                           bool unified,
                           bool loop)
{
    m_algo = LEDAlgoPointerType(new RampUp(duration,
                                           p1Curve,
                                           p1Color,
                                           p1MinBrightness,
                                           p1MaxBrightness,
                                           p2Curve,
                                           p2Color,
                                           p2MinBrightness,
                                           p2MaxBrightness,
                                           unified,
                                           loop));
}

void LEDController::canSendMessages() {
    m_isReady = true;
}

void LEDController::unableToSendMessages() {
    m_isReady = false;
}

// Handling for LED transitions.
void LEDController::enterConfigurationScreen() {

}

void LEDController::enterGameSelectScreen() {
    qDebug() << "Entered game selection screen setting breath as the current algorithm";
    m_config->idleConfiguration()->algoConfig().setLEDController(this);
}

void LEDController::enterDMConfigScreen() {

}

void LEDController::enterDMCountDownScreen() {

}

void LEDController::postEnterDMCountDownScreen() {

}

void LEDController::enterDMPlayersReadyScreen() {

}

void LEDController::enterDMRunningScreen() {

}

void LEDController::enterDMWinnerDisplayScreen(QString playerName) {

}

void LEDController::enterSoccerConfigScreen() {

}

void LEDController::enterSoccerPlayersReadyScreen() {

}

void LEDController::enterSoccerRunningScreen() {

}

void LEDController::enterSoccerCountDownScreen() {

}

void LEDController::enterSoccerGameOverScreen() {

}

void LEDController::DMCDstart3() {

}

void LEDController::DMCDstart2() {

}

void LEDController::DMCDstart1() {

}

void LEDController::DMCDstartFight() {

}

