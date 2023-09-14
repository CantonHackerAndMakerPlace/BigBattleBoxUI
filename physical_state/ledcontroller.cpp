#include "ledcontroller.h"
#include <physical_state/arduinoclient.h>
#include <QTimer>
#include <physical_state/ledalgo/breath.h>

LEDController::LEDController(ArduinoClient *client, QObject *parent)
    : QObject{parent}
    , m_timer(new QTimer(this))
    , m_client(client)
{
    // Connecting to the messagint timer.
    connect(m_timer, &QTimer::timeout,
            this, &LEDController::onTimeout);

    // Handling connect and disconnect for the arduino.

    // TODO: We may need additional code here in order to re-initialize
    // any of the state before we can continue.
    connect(m_client, &ArduinoClient::connected,
            [&] { m_isReady = true; });

    connect(m_client, &ArduinoClient::disconnected,
            [&] { m_isReady = false; });

    // Must wait for the arduino to fully connect and we have receive the fist status message.
    // Otherwise we risk having to re-send everything.

    // Try for 30 msg per second.
    m_timer->start(33);
}


void LEDController::onTimeout() {
    if (!m_isReady) {
        switch(m_state){

        case LEDPattern::Off:
        case LEDPattern::Breath:
        case LEDPattern::CountDownFill:
        case LEDPattern::Blink:
        case LEDPattern::Cylon:
        case LEDPattern::SolidColors:
        case LEDPattern::RampUp:
            break;
        }
    }
}


void LEDController::off() {

}

void LEDController::breath(int minBrightness,
            int maxBrightness,
            int duration,
            QEasingCurve easingCurve,
                           QColor color) {

}

void LEDController::CountDownFill(int duration,
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
                                  bool unifiedLedStrips) {

}

void LEDController::blink(int numberOfBlinks,
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
                          bool unified) {

}


/// Enter the sweaping eye state.
void LEDController::cylon(int startIndex,
           int stopIndex,
           int eyeLength,
           int duration,
           int brightness,
           QEasingCurve interpolationCurve,
           QColor p1foregroundColor,
           QColor p1backgroundColor,
           QColor p2foregroundColor,
           QColor p2backgroundColor,
           bool unified) {

}

/// Enters the solid colors state where don't do anything but display a
/// specififc color at a specified brightness.
void LEDController::solidColors(QColor p1Color, int p1brightness, QColor p2Color, int p2brightness, bool unified) {

}

/// Ramp up to a brightness using the specified colors.
void LEDController::rampUp(int minBrightness, int maxBrightness, bool unified) {

}
