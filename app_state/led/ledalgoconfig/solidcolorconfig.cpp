#include "solidcolorconfig.h"

SolidColorConfig::SolidColorConfig(QString const& keyPrefix, QObject *parent)
    : QObject{parent}
    , m_keyPrefix(keyPrefix)
    , m_p1Color(Qt::white, m_keyPrefix + "/soilid/p1/color")
    , m_p1brightness(100, m_keyPrefix + "/soilid/p1/brightness")
    , m_p2Color(Qt::white, m_keyPrefix + "/soilid/p2/color")
    , m_p2brightness(100, m_keyPrefix + "/soilid/p2/brightness")
    , m_unified(true, m_keyPrefix + "/soilid/unification")
{
}

void SolidColorConfig::init(QSettings *settings) {
    assert(settings);
    m_p1Color.attachSettings(settings);
    m_p1brightness.attachSettings(settings);
    m_p2Color.attachSettings(settings);
    m_p2brightness.attachSettings(settings);
    m_unified.attachSettings(settings);
}

void SolidColorConfig::setLEDController(LEDController *controller) {
    controller->solidColors(m_p1Color,
                            m_p1brightness,
                            m_p2Color,
                            m_p2brightness,
                            m_unified);
}

ColorObject &SolidColorConfig::p1Color() {
    return m_p1Color;
}

IntegerObject &SolidColorConfig::p1Brightness() {
    return m_p1brightness;
}

ColorObject &SolidColorConfig::p2Color() {
    return m_p2Color;
}

IntegerObject &SolidColorConfig::p2Brightness() {
    return m_p2brightness;
}

BooleanObject &SolidColorConfig::unified() {
    return m_unified;
}
