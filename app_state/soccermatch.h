#ifndef SOCCERMATCH_H
#define SOCCERMATCH_H

#include <QObject>
#include <QDebug>

class SoccerConfig;

class SoccerMatch : public QObject
{
    Q_OBJECT
public:
    explicit SoccerMatch(QObject *parent = nullptr);
    virtual ~SoccerMatch();
private:
    Q_PROPERTY(int m_matchTimeMs READ matchDuration WRITE setMatchDuration RESET resetMatchDuration NOTIFY notifyMatchDurationChanged)
    Q_PROPERTY(QString m_teamOneName READ teamOneName WRITE setTeamOneName RESET resetTeamOneName NOTIFY notifyTeamOneNameChanged)
    Q_PROPERTY(QString m_teamTwoName READ teamTwoName WRITE setTeamTwoName RESET resetTeamTwoName NOTIFY notifyTeamTwoNameChanged)
    Q_PROPERTY(int m_teamOneScore READ teamOneScore WRITE setTeamOneScore RESET resetTeamOneScore NOTIFY notifyTeamOneScoreChanged)
    Q_PROPERTY(int m_teamTwoScore READ teamTwoScore WRITE setTeamTwoScore RESET resetTeamTwoScore NOTIFY notifyTeamTwoScoreChanged)
    Q_PROPERTY(QString m_state READ state WRITE setState RESET resetState NOTIFY notifyStateChanged)
    Q_PROPERTY(int m_maxScore READ maxScore WRITE setMaxScore RESET resetMaxScore NOTIFY notifyMaxScoreChanged)
public:
    int matchDuration() const{
        return m_matchTimeMs;
    }

    QString teamOneName() const{
        return m_teamOneName;
    }

    QString teamTwoName() const{
        return m_teamTwoName;
    }

    int teamOneScore() const {
        return m_teamOneScore;
    }

    int teamTwoScore() const {
        return m_teamTwoScore;
    }

    QString state() const {
        return m_state;
    }
    int maxScore() const {
        return m_maxScore;
    }
public slots:
    void setMatchDuration(int arg) {
        if (m_matchTimeMs != arg) {
            m_matchTimeMs = arg;
            emit notifyMatchDurationChanged(m_matchTimeMs);
        }
    }

    void resetMatchDuration() {
        setMatchDuration(0);
    }

    void setTeamOneName(QString arg) {
        if (m_teamOneName != arg) {
            m_teamOneName = arg;
            emit notifyTeamOneNameChanged(m_teamOneName);
        }
    }
    void resetTeamOneName() {
        setTeamOneName("");
    }

    void setTeamTwoName(QString arg) {
        if (m_teamTwoName != arg) {
            m_teamTwoName = arg;
            emit notifyTeamTwoNameChanged(m_teamTwoName);
        }
    }

    void resetTeamTwoName() {
        setTeamOneName("");
    }

    void setTeamOneScore(int arg) {
        if (m_teamOneScore != arg) {
            m_teamOneScore = arg;
            emit notifyTeamOneScoreChanged(m_teamOneScore);
        }
    }

    void resetTeamOneScore() {
        setTeamOneScore(0);
    }

    void setTeamTwoScore(int arg) {
        if (m_teamTwoScore != arg) {
            m_teamTwoScore = arg;
            emit notifyTeamTwoScoreChanged(m_teamTwoScore);
        }
    }

    void resetTeamTwoScore() {
        setTeamTwoScore(0);
    }

    void setState(QString state) {
        if(m_state != state) {
            m_state = state;
            emit notifyStateChanged(m_state);
        }
    }
    void resetState() {
        setState("Running");
    }

    void setMaxScore(int arg) {
        if (m_maxScore != arg) {
            m_maxScore = arg;
            emit notifyMaxScoreChanged(m_maxScore);
        }
    }
    void resetMaxScore() {
        setMaxScore(0);
    }

    void reset() {
        resetMatchDuration();
        resetTeamOneName();
        resetTeamTwoName();
        resetTeamOneScore();
        resetTeamTwoScore();
        resetState();
        resetMaxScore();
    }

    void loadSoccerConfig(SoccerConfig *cfg);

signals:
    void notifyMatchDurationChanged(int arg);
    void notifyTeamOneNameChanged(QString arg);
    void notifyTeamTwoNameChanged(QString arg);
    void notifyTeamOneScoreChanged(int arg);
    void notifyTeamTwoScoreChanged(int arg);
    void notifyStateChanged(QString arg);
    void notifyMaxScoreChanged(int arg);

private:
    int m_matchTimeMs = 0;
    QString m_teamOneName = "";
    QString m_teamTwoName = "";
    int m_teamOneScore = 0;
    int m_teamTwoScore = 0;
    QString m_state = "Running";
    int m_maxScore = 0;

};

#endif // SOCCERMATCH_H
