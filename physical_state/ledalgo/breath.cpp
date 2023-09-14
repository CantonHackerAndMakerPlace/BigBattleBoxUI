#include "breath.h"

Breath::Breath(int minBrightness,
               int maxBrightness,
               int duration,
               QEasingCurve easingCurve,
               QColor color)
{

}

void Breath::start(GeneralLEDConfiguration *generalConfig) {

}

void Breath::updateConfig(GeneralLEDConfiguration *generalConfig) {

}

void Breath::update(qint64 elapsedTime, ArduinoMessanger *messanger) {

}

bool Breath::loops() const { return true; }

bool Breath::isFinished() const { return false; }
