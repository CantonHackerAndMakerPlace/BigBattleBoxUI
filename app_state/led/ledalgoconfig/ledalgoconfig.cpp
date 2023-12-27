#include "ledalgoconfig.h"


LEDAlgoConfig::LEDAlgoConfig(QString const& settingsKeyPrefix, QObject *parent)
    : QObject{parent}
    , m_algo(AlgoKindObject::AlgoKind::Blink, settingsKeyPrefix + "/algorithmkind")

    , m_breath(new BreathConfig(settingsKeyPrefix, this))
{
}

void LEDAlgoConfig::init(QSettings *settings) {
    m_breath->init(settings);

}

AlgoKindObject &LEDAlgoConfig::getAlgoKind() {
    return m_algo;
}

void LEDAlgoConfig::setLEDController(LEDController* controller) {
    switch(m_algo) {

    case AlgoKindObject::AlgoKind::Off:
        break;
    case AlgoKindObject::AlgoKind::Blink:
        m_blink->setLEDController(controller);
        break;
    case AlgoKindObject::AlgoKind::Breath:
        m_breath->setLEDController(controller);
        break;
    case AlgoKindObject::AlgoKind::CountDown:
        break;
    case AlgoKindObject::AlgoKind::Cylon:
        break;
    case AlgoKindObject::AlgoKind::RampUp:
        break;
    case AlgoKindObject::AlgoKind::Solid:
        break;
    }
}

BlinkConfig *LEDAlgoConfig::getBlink() const {
    return m_blink;
}

BreathConfig *LEDAlgoConfig::getBreath() const {
    return m_breath;
}
