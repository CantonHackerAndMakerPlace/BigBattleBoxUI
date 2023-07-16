#ifndef SOCCERCONFIG_H
#define SOCCERCONFIG_H

#include <QObject>
#include <QDebug>

class SoccerConfig: public QObject
{
    Q_OBJECT
public:
    explicit SoccerConfig(QObject *parent = nullptr);
    virtual ~SoccerConfig();
private:
    Q_PROPERTY(int m_matchDuration READ matchDuration WRITE setMatchDuration RESET resetMatchDuration NOTIFY notifyMatchDurationChanged)
    Q_PROPERTY(QString m_teamOneName READ teamOneName WRITE setTeamOneName RESET resetTeamOneName NOTIFY notifyTeamOneNameChanged)
    Q_PROPERTY(QString m_teamTwoName READ teamTwoName WRITE setTeamTwoName RESET resetTeamTwoName NOTIFY notifyTeamTwoNameChanged)
    Q_PROPERTY(int m_maxScore READ maxScore WRITE setMaxScore RESET resetMaxScore NOTIFY notifyMaxScoreChanged)
public:
    int matchDuration() const{
        return m_matchDuration;
    }

    QString teamOneName() const{
        return m_teamOneName;
    }

    QString teamTwoName() const{
        return m_teamTwoName;
    }

    int maxScore() const {
        return m_maxScore;
    }
public slots:
    void setMatchDuration(int arg) {
        if (m_matchDuration != arg) {
            m_matchDuration = arg;
            emit notifyMatchDurationChanged(m_matchDuration);
        }
    }

    void resetMatchDuration() {
        setMatchDuration(180);
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
        setTeamTwoName("");
    }

    void setMaxScore(int arg) {
        if (m_maxScore!= arg) {
            m_maxScore= arg;
            emit notifyMaxScoreChanged(m_maxScore);
        }
    }

    void resetMaxScore() {
        setMaxScore(3);
    }

    void reset() {
        resetMatchDuration();
        resetTeamOneName();
        resetTeamTwoName();
        resetMaxScore();
    }

signals:
    void notifyMatchDurationChanged(int arg);
    void notifyTeamOneNameChanged(QString arg);
    void notifyTeamTwoNameChanged(QString arg);
    void notifyMaxScoreChanged(int arg);
    void error(QString message);

public:
    void saveToFile(QString path);
    void loadFromFile(QString path);

private:
    std::optional<QString> getJsonString(QString path, QJsonObject &obj, QString name);
    std::optional<int> getJsonInt(QString path, QJsonObject &obj, QString name);

private:
    int m_matchDuration = 180;
    QString m_teamOneName = "";
    QString m_teamTwoName = "";
    int m_maxScore = 3;
};

#endif // SOCCERCONFIG_H
