#include "app_state/battleboxviewmodel.h"
#include "deathmatchconfig.h"
#include <QApplication>
#include <QFile>

BattleBoxViewModel::BattleBoxViewModel(QObject *parent)
    : QObject{parent}
    , m_deathMatch(new DeathMatchConfig(this))
    , m_dmprPlayerOne(new DeathMatchPlayerReadyModel(this))
    , m_dmprPlayerTwo(new DeathMatchPlayerReadyModel(this))
    , m_dmRt(new DeathMatchRuntime(this))
    , m_soccerConfig(new SoccerConfig(this))
    , m_soccerMatch(new SoccerMatch(this))
    , m_soccerTeamOneReady(new SoccerTeamReady(this))
    , m_soccerTeamTwoReady(new SoccerTeamReady(this))
    , m_settings(nullptr)
{
    m_dmRt->initialize(m_deathMatch);
}

BattleBoxViewModel::~BattleBoxViewModel() { }

QSettings *BattleBoxViewModel::settings() const {
    return m_settings;
}

void BattleBoxViewModel::loadSettings() {
    QString settingsFile = QApplication::applicationDirPath() + "/settings.ini";
    m_settings = new QSettings(settingsFile, QSettings::IniFormat, this);
}

void BattleBoxViewModel::saveSettings() {
    m_settings->sync();
}

void BattleBoxViewModel::resetDeathMatchPlayerOneReady() {
    m_dmprPlayerOne->reset();
}

void BattleBoxViewModel::resetDeathMatchPlayerTwoReady() {
    m_dmprPlayerTwo->reset();
}


void BattleBoxViewModel::resetSoccerConfig() {
    soccerConfig()->reset();
}

void BattleBoxViewModel::resetSoccerMatch() {
    soccerMatch()->reset();
}

SoccerConfig *BattleBoxViewModel::soccerConfig() const {
    return m_soccerConfig;
}

SoccerMatch *BattleBoxViewModel::soccerMatch() const {
    return m_soccerMatch;
}

void BattleBoxViewModel::resetSoccerTeamOneReady() {
    m_soccerTeamOneReady->reset();
}

void BattleBoxViewModel::resetSoccerTeamTwoReady() {
    m_soccerTeamTwoReady->reset();
}
