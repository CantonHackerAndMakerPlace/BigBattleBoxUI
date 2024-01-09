#include "ledidleconfiguration.h"
#include <QSettings>

LEDIdleConfiguration::LEDIdleConfiguration(QObject *parent)
    :QObject(parent)
    , m_algoConfig(new LEDAlgoConfig("IdleConfiguration", this))
{ }

LEDAlgoConfig &LEDIdleConfiguration::algoConfig() {
    return *m_algoConfig;
}

void LEDIdleConfiguration::loadSettings(QSettings *settings) {
    assert(settings);
    // Connecting all of the associated settings values.
    m_algoConfig->init(settings);
}
