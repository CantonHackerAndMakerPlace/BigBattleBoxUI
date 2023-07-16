#ifndef SOCCERTEAMSREADY_H
#define SOCCERTEAMSREADY_H

#include <QObject>

class SoccerTeamReady : public QObject
{
    Q_OBJECT
public:
    explicit SoccerTeamReady(QObject *parent = nullptr);

    // Properties
    Q_PROPERTY(bool m_teamReady READ teamReady WRITE setTeamReady RESET resetTeamReady NOTIFY teamReadyChanged)
    Q_PROPERTY(QString m_readyText READ readyText WRITE setReadyText RESET resetReadyText NOTIFY readyTextChanged)
    bool teamReady() const {
        return m_teamReady;
    }

    QString readyText() const {
        return m_readyText;
    }

    void setTeamReady(bool arg) {
        if (m_teamReady != arg) {
            m_teamReady = arg;
            emit teamReadyChanged(m_teamReady);
        }
    }
    void resetTeamReady() {
        setTeamReady(false);
    }

    void setReadyText(QString arg) {
        if (m_readyText != arg) {
            m_readyText = arg;
            emit readyTextChanged(m_readyText);
        }
    }
    void resetReadyText() {
        setReadyText("Not Ready");
    }
    void reset();
private slots:
    void updateReadyText(bool arg);
signals:
    void teamReadyChanged(bool arg);
    void readyTextChanged(QString arg);
private:
    bool m_teamReady = false;
    QString m_readyText = "Not Ready";
};

#endif // SOCCERPLAYERSREADY_H
