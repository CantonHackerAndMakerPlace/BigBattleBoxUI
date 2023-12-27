#include "ledalgo.h"

LEDAlgo::LEDAlgo() { }

LEDAlgo::~LEDAlgo() { }


bool LEDAlgo::wasStarted() const {
    return m_hasBeenStarted;
}

void LEDAlgo::setWasStarted(bool wasStarted) {
    m_hasBeenStarted = wasStarted;
}

void LEDAlgo::reset() {
    m_hasBeenStarted = false;
}
