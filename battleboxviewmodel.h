#ifndef BATTLEBOXVIEWMODEL_H
#define BATTLEBOXVIEWMODEL_H

#include <QObject>
#include <QSettings>
#include "soccerconfig.h"
#include "soccermatch.h"
#include "deathmatchconfig.h"
#include "deathmatchplayerreadymodel.h"
#include "soccerteamready.h"
#include <QSettings>

class BattleBoxViewModel : public QObject
{
    Q_OBJECT
public:
    explicit BattleBoxViewModel(QObject *parent = nullptr);
    virtual ~BattleBoxViewModel();

private:
    DeathMatchConfig *m_deathMatch;
    DeathMatchPlayerReadyModel *m_dmprPlayerOne;
    DeathMatchPlayerReadyModel *m_dmprPlayerTwo;
    QString m_DMWinner;
    SoccerConfig *m_soccerConfig;
    SoccerMatch *m_soccerMatch;
    SoccerTeamReady *m_soccerTeamOneReady;
    SoccerTeamReady *m_soccerTeamTwoReady;
    QSettings *m_settings;

    Q_PROPERTY(DeathMatchConfig* m_deathmatch READ deathMatchConfig RESET resetDeathMatchConfig NOTIFY deathMatchConfigChanged)
    Q_PROPERTY(QString m_DMWinner READ deathMatchWinner WRITE setDeathMatchWinner RESET resetDeathMatchWinner NOTIFY notifyDeathMatchWinnerChanged)
    Q_PROPERTY(SoccerConfig *m_soccerConfig READ soccerConfig RESET resetSoccerConfig NOTIFY notifySoccerConfigChanged)
    Q_PROPERTY(SoccerMatch *m_soccerMatch READ soccerMatch RESET resetSoccerMatch NOTIFY notifySoccerMatchChanged)

public:

    /// Used for interacting with externally saved data.
    QSettings *settings() const;
    void loadSettings();
    void saveSettings();

    DeathMatchConfig *deathMatchConfig() const {
        return m_deathMatch;
    }

    DeathMatchPlayerReadyModel *deathMatchPlayerOneReady() const {
        return m_dmprPlayerOne;
    }

    DeathMatchPlayerReadyModel *deathMatchPlayerTwoReady() const {
        return m_dmprPlayerTwo;
    }

    QString deathMatchWinner() const {
        return m_DMWinner;
    }
    SoccerConfig *soccerConfig() const;
    SoccerMatch *soccerMatch() const;

    SoccerTeamReady *soccerTeamOneReady() const {
        return m_soccerTeamOneReady;
    }

    SoccerTeamReady *soccerTeamTwoReady() const {
        return m_soccerTeamTwoReady;
    }
public slots:
    void resetDeathMatchConfig() {
        m_deathMatch->reset();
    }

    void setDeathMatchWinner(QString playerName) {
        m_DMWinner = playerName;
        emit notifyDeathMatchWinnerChanged(m_DMWinner);
    }

    void resetDeathMatchWinner() {
        setDeathMatchWinner("");
    }
    void resetDeathMatchPlayerOneReady();
    void resetDeathMatchPlayerTwoReady();

    void resetSoccerConfig();
    void resetSoccerMatch();

    void resetSoccerTeamOneReady();
    void resetSoccerTeamTwoReady();
signals:
    void deathMatchConfigChanged(DeathMatchConfig *dmc);
    void notifyDeathMatchWinnerChanged(QString arg);
    void notifySoccerConfigChanged(SoccerConfig *sCfg);
    void notifySoccerMatchChanged(SoccerMatch *sCfg);
};

#endif // BATTLEBOXVIEWMODEL_H

