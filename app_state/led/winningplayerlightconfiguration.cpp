#include "winningplayerlightconfiguration.h"

WinningPlayerLightConfiguration::WinningPlayerLightConfiguration(QString const& keyPrefix, QObject *parent)
    : QObject{parent}
    , m_keyPrefix(keyPrefix)
    , m_p1(new LEDAlgoConfig(m_keyPrefix +"/P1Wins/", this))
    , m_p2(new LEDAlgoConfig(m_keyPrefix +"/P2Wins/", this))
{

}

LEDAlgoConfig *WinningPlayerLightConfiguration::playerOne() const {
    return m_p1;
}

LEDAlgoConfig *WinningPlayerLightConfiguration::playerTwo() const {
    return m_p2;
}

void WinningPlayerLightConfiguration::init(QSettings *settings) {
    m_p1->init(settings);
    m_p2->init(settings);
}
