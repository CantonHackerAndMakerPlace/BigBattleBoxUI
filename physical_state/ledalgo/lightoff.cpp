#include "lightoff.h"

LightsOff::LightsOff()
{

}

void LightsOff::start(GeneralLEDConfiguration *, ArduinoClient *client) { }

void LightsOff::update(GeneralLEDConfiguration *generalConfig, qint64 elapsedTime, ArduinoClient *client) {
    // Setting all of the lighjts to white and setting the brightness to zero.
    client->setGlobalColor(QColor(Qt::white));
    client->setAllBrightness(0, true);
    m_isFinished = true;
}

bool LightsOff::loops() const {
    return false;
}

bool LightsOff::isFinished() const {
    return m_isFinished;
}
