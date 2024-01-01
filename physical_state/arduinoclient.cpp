#include "arduinoclient.h"
#include <app_state/led/generalledconfiguration.h>
#include <physical_state/arduinomessanger.h>
#include <physical_state/arduinoconnectionmanager.h>

ArduinoClient::ArduinoClient(GeneralLEDConfiguration *generalLEDConfig,
                             ArduinoMessanger *messanger,
                             QObject *parent)
    : QObject{parent}
    , m_config(generalLEDConfig)
    , m_messanger(messanger)
{
    connect(m_messanger, &ArduinoMessanger::receivedFirstResponse,
            this, &ArduinoClient::onConnected);

    connect(m_messanger->connectionManager(), &ArduinoConnectionManager::disconnected,
            this, &ArduinoClient::disconnected);
}

GeneralLEDConfiguration *ArduinoClient::generalLEDConfig() const {
    return m_config;
}

ArduinoMessanger *ArduinoClient::messanger() const {
    return m_messanger;
}

int ArduinoClient::computePlayerOneIndex(int providedIndex) {
    if (providedIndex >= m_config->playerOneLedCount().value()) {
        return 0;
    }
    if (m_config->playerOneLedDirection().value()) {
        // Forward
        return providedIndex;
    } else {
        // backward
        return (m_config->playerOneLedCount().value() - providedIndex);
    }
}

int ArduinoClient::computePlayerTwoIndex(int providedIndex){
    if (providedIndex >= m_config->playerTwoLedCount().value()) {
        return 0;
    }
    if (m_config->playerTwoLedDirection().value()) {
        // Forward
        return providedIndex;
    } else {
        // backward
        return (m_config->playerTwoLedCount().value() - providedIndex);
    }
}


ArduinoClient::FillInfo ArduinoClient::computePlayerOneFill(int providedIndex, int providedCount) {
    if (providedIndex >= m_config->playerOneLedCount().value()) {
        return {0, 0};
    }
    if (m_config->playerOneLedDirection().value()) {
        // Forward
        return { providedIndex, providedCount };
    } else {
        // backward
        return { computePlayerOneIndex(providedIndex) - providedCount, providedCount};
    }
}

ArduinoClient::FillInfo ArduinoClient::computePlayerTwoFill(int providedIndex, int providedCount) {
    if (providedIndex >= m_config->playerTwoLedCount().value()) {
        return {0, 0};
    }
    if (m_config->playerTwoLedDirection().value()) {
        // Forward
        return { providedIndex, providedCount };
    } else {
        // backward
        return { computePlayerTwoIndex(providedIndex) - providedCount, providedCount};
    }
}

void ArduinoClient::contigiousSetPixel(QColor color, int index, bool show) {
    //        m_messanger->
    if (index >= m_config->playerOneLedCount().value()) {
        // Sending to player two
        int computedIndex = computePlayerTwoIndex(index - m_config->playerOneLedCount().value());
        m_messanger->sendLEDSetPixelColor(0, computedIndex, color);
    } else {
        int computedIndex = computePlayerTwoIndex(index);
        m_messanger->sendLEDSetPixelColor(0, computedIndex, color);
    }
    if (show) {
        m_messanger->sendLEDAllShow();
    }
}

void ArduinoClient::contigiousFill(QColor color, int index, int count, bool show) {
    // Building the fill command for player two.
    if ((index + count) > m_config->playerOneLedCount().value()) {
        int p2Count = (index + count) - m_config->playerOneLedCount().value();
        int p2StartingIndex = 0;
        if (index > m_config->playerOneLedCount().value()) {
            // Change to be relative to the p2 LED strand otherwise leave the value
            // as zero and start at the beginning.
            p2StartingIndex = index - m_config->playerOneLedCount().value();
        }
        auto p2Fill = computePlayerTwoFill(p2StartingIndex, p2Count);
        m_messanger->sendLEDFill(1, color, p2Fill.index, p2Fill.count);
    }

    // Building the fill command for player one.
    if (index < m_config->playerOneLedCount().value()) {
        // No need to fill player two because the lights don't reach
        // that far.
        // Starting index doesn't change but the number of led within the count does change.
        int computedCount = std::min(index + count, m_config->playerOneLedCount().value()) - index;
        auto p1Fill = computePlayerTwoFill(index, computedCount);
        m_messanger->sendLEDFill(0, color, p1Fill.index, p1Fill.count);
    }
    if (show) {
        m_messanger->sendLEDAllShow();
    }
}

void ArduinoClient::mirroredSetPixel(QColor color, int index, bool show) {
    int p1Index = computePlayerOneIndex(index);
    int p2Index = computePlayerTwoIndex(index);

    m_messanger->sendLEDSetPixelColor(0, p1Index, color);
    m_messanger->sendLEDSetPixelColor(1, p2Index, color);
    if (show)
        m_messanger->sendLEDAllShow();
}

void ArduinoClient::mirroredFill(QColor color, int index, int count, bool show) {
    auto p1Fill = computePlayerOneFill(index, count);
    m_messanger->sendLEDFill(0, color, p1Fill.index, p1Fill.count);

    auto p2Fill = computePlayerTwoFill(index, count);
    m_messanger->sendLEDFill(1, color, p2Fill.index, p2Fill.count);

    if (show)
        m_messanger->sendLEDAllShow();
}

void ArduinoClient::mirroredFill(QColor color, int index, qreal percentage, bool show) {
    auto numberOfLightsToFillP1 = std::min(m_config->playerOneLedCount() - index, int(std::floor(percentage * (m_config->playerOneLedCount() - index))));
    auto p1Fill = computePlayerOneFill(index, numberOfLightsToFillP1);
    m_messanger->sendLEDFill(0, color, p1Fill.index, p1Fill.count);


    auto numberOfLightsToFillP2 = std::min(m_config->playerTwoLedCount() - index, int(std::floor(percentage * (m_config->playerTwoLedCount() - index))));
    auto p2Fill = computePlayerTwoFill(index, numberOfLightsToFillP2);
    m_messanger->sendLEDFill(1, color, p2Fill.index, p2Fill.count);

    if (show)
        m_messanger->sendLEDAllShow();
}

void ArduinoClient::setGlobalColor(QColor color, bool show) {
    auto p1Fill = computePlayerOneFill(0, m_config->playerOneLedCount().value());
    m_messanger->sendLEDFill(0, color, p1Fill.index, p1Fill.count);

    auto p2Fill = computePlayerTwoFill(0, m_config->playerTwoLedCount().value());
    m_messanger->sendLEDFill(1, color, p2Fill.index, p2Fill.count);

    m_messanger->sendLEDAllShow();
}

void ArduinoClient::setAllBrightness(int brightness, bool show) {
    m_messanger->sendLEDAllSetBrightness(brightness);
    if (show)
        m_messanger->sendLEDAllShow();
}

void ArduinoClient::p1SetBrightness(int brightness, bool show) {
    m_messanger->sendLEDSetBrightness(0, brightness);
    if (show)
        m_messanger->sendLEDAllShow();
}

void ArduinoClient::p1Fill(QColor color, int index, int count, bool show) {
    auto fill = computePlayerOneFill(index, count);
    m_messanger->sendLEDFill(0, color, fill.index, fill.count);
    if (show)
        m_messanger->sendLEDAllShow();
}

void ArduinoClient::p1SetPixel(QColor color, int index, bool show) {
    auto newIndex = computePlayerOneIndex(index);
    m_messanger->sendLEDSetPixelColor(0, newIndex, color);
    if (show)
        m_messanger->sendLEDAllShow();
}

void ArduinoClient::p1SetColor(QColor color, bool show) {
    auto p1Fill = computePlayerOneFill(0, m_config->playerOneLedCount().value());
    m_messanger->sendLEDFill(0, color, p1Fill.index, p1Fill.count);
    if(show)
        m_messanger->sendLEDAllShow();
}

void ArduinoClient::p2SetBrightness(int brightness, bool show) {
    m_messanger->sendLEDSetBrightness(1, brightness);
    if (show)
        m_messanger->sendLEDAllShow();
}

void ArduinoClient::p2Fill(QColor color, int index, int count, bool show) {
    auto fill = computePlayerTwoFill(index, count);
    m_messanger->sendLEDFill(1, color, fill.index, fill.count);
    if (show)
        m_messanger->sendLEDAllShow();
}

void ArduinoClient::p2SetPixel(QColor color, int index, bool show) {
    auto newIndex = computePlayerTwoIndex(index);
    m_messanger->sendLEDSetPixelColor(1, newIndex, color);
    if (show)
        m_messanger->sendLEDAllShow();
}

void ArduinoClient::p2SetColor(QColor color, bool show) {
    auto p2Fill = computePlayerTwoFill(0, m_config->playerTwoLedCount().value());
    m_messanger->sendLEDFill(1, color, p2Fill.index, p2Fill.count);
    if (show)
        m_messanger->sendLEDAllShow();
}

void ArduinoClient::setSpotLights(bool p1, bool p2) {
    m_messanger->sendSetSpotLights(p1, p2);
}

void ArduinoClient::setP1SpotLight(bool v) {
    m_messanger->sendSetP1SpotLight(v);
}
void ArduinoClient::setP2SpotLight(bool v) {
    m_messanger->sendSetP2SpotLight(v);
}

// NOTE: This should probably move somewhere else.
void ArduinoClient::onConnected() {
    // Sending messages to updating the current LED configuration.
    m_messanger->sendLEDReconfig(0,
            m_config->playerOneLedPin().value(),
            m_config->playerOneLedCount().value());

    m_messanger->sendLEDReconfig(1,
            m_config->playerTwoLedPin().value(),
            m_config->playerTwoLedCount().value());
}
