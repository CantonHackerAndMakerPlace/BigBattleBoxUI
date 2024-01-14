#ifndef DEATHMATCHPLAYERREADY_H
#define DEATHMATCHPLAYERREADY_H

#include <QObject>
#include "ledalgo.h"
#include "app_state/led/playerreadyledlightconfiguration.h"

class DeathMatchPlayerReady : public QObject, public LEDAlgo
{
    Q_OBJECT
public:
    explicit DeathMatchPlayerReady(PlayerReadyLEDLightConfiguration *config);

    virtual void start(GeneralLEDConfiguration *generalConfig, ArduinoClient *client);

    virtual void update(GeneralLEDConfiguration *generalConfig, qint64 elapsedTime, ArduinoClient *client);

    virtual bool loops() const;

    virtual bool isFinished() const;

    virtual void reset();
public slots:
    void dmPlayerOneReady();
    void dmPlayerOneCancelledReady();
    void dmPlayerOneCantBeReady();

    void dmPlayerTwoReady();
    void dmPlayerTwoCancelledReady();
    void dmPlayerTwoCantBeReady();
    void isRunning(bool value);
private:
    void handleP1Blink(qint64 elapsedTime);
    void handleP2Blink(qint64 elapsedTime);
private:
    bool m_isRunning = false;
    PlayerReadyLEDLightConfiguration *m_config = nullptr;
    ArduinoClient *m_client = nullptr;

    bool m_p1StartBlinking = false;
    bool m_p1IsBlinking = false;
    qint64 m_p1BlinkStartTime = 0;
    bool m_p1CurrentPhaseIsOn = true;
    int m_p1NumberOfBlinks = 0;
    bool m_p2StartBlinking = false;
    bool m_p2IsBlinking = false;
    qint64 m_p2BlinkStartTime = 0;
    bool m_p2CurrentPhaseIsOn = true;
    int m_p2NumberOfBlinks = 0;
};

#endif // DEATHMATCHPLAYERREADY_H
