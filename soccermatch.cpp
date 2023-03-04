#include "soccermatch.h"
#include "soccerconfig.h"

SoccerMatch::SoccerMatch(QObject *parent)
    : QObject{parent}
{

}

SoccerMatch::~SoccerMatch() { }

void SoccerMatch::loadSoccerConfig(SoccerConfig *cfg) {
    setState("Running");
    setMatchDuration(cfg->matchDuration());
    setTeamOneName(cfg->teamOneName() == "" ? "Team One" : cfg->teamOneName());
    setTeamTwoName(cfg->teamTwoName() == "" ? "Team Two" : cfg->teamTwoName());
    setMaxScore(cfg->maxScore());
    resetTeamOneScore();
    resetTeamTwoScore();
}
