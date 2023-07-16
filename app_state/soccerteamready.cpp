#include "app_state/soccerteamready.h"

SoccerTeamReady::SoccerTeamReady(QObject *parent)
    : QObject{parent}
{
    connect(this, &SoccerTeamReady::teamReadyChanged,
            this, &SoccerTeamReady::updateReadyText);
}

void SoccerTeamReady::reset() {
    resetTeamReady();
}

void SoccerTeamReady::updateReadyText(bool arg) {
    setReadyText(arg ? "Ready" : "Not Ready");
}
