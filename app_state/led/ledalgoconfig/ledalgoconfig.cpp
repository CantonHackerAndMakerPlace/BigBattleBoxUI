#include "ledalgoconfig.h"


LEDAlgoConfig::LEDAlgoConfig(QString const& settingsKeyPrefix, QObject *parent)
    : QObject{parent}
    , m_algo(AlgoKindObject::AlgoKind::Blink, settingsKeyPrefix + "/algorithmkind")
    , m_blink(new BlinkConfig(settingsKeyPrefix, this))
    , m_breath(new BreathConfig(settingsKeyPrefix, this))
    , m_countDown(new CountDownFillConfig(settingsKeyPrefix, this))
    , m_cylon(new CylonConfig(settingsKeyPrefix, this))
    , m_rampUp(new RampUpConfig(settingsKeyPrefix, this))
    , m_solidColors(new SolidColorConfig(settingsKeyPrefix, this))
{ }

void LEDAlgoConfig::init(QSettings *settings) {
    m_algo.attachSettings(settings);
    m_blink->init(settings);
    m_breath->init(settings);
    m_breath->init(settings);
    m_countDown->init(settings);
    m_cylon->init(settings);
    m_rampUp->init(settings);
    m_solidColors->init(settings);
}

AlgoKindObject &LEDAlgoConfig::getAlgoKind() {
    return m_algo;
}

void LEDAlgoConfig::setLEDController(LEDController* controller) {
    switch(m_algo) {

    case AlgoKindObject::AlgoKind::Off:
        controller->off();
        break;
    case AlgoKindObject::AlgoKind::Blink:
        m_blink->setLEDController(controller);
        break;
    case AlgoKindObject::AlgoKind::Breath:
        m_breath->setLEDController(controller);
        break;
    case AlgoKindObject::AlgoKind::CountDown:
        m_countDown->setLEDController(controller);
        break;
    case AlgoKindObject::AlgoKind::Cylon:
        m_cylon->setLEDController(controller);
        break;
    case AlgoKindObject::AlgoKind::RampUp:
        m_rampUp->setLEDController(controller);
        break;
    case AlgoKindObject::AlgoKind::Solid:
        m_solidColors->setLEDController(controller);
        break;
    }
}

BlinkConfig *LEDAlgoConfig::getBlink() const {
    return m_blink;
}

BreathConfig *LEDAlgoConfig::getBreath() const {
    return m_breath;
}

CountDownFillConfig *LEDAlgoConfig::getCountDownFill() const {
    return m_countDown;
}

RampUpConfig *LEDAlgoConfig::getRampUpConfig() const {
    return m_rampUp;
}
SolidColorConfig *LEDAlgoConfig::getSolidColorConfig() const {
    return m_solidColors;
}
