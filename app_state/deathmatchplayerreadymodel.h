#ifndef DEATHMATCHPLAYERREADYMODEL_H
#define DEATHMATCHPLAYERREADYMODEL_H

#include <QObject>

class DeathMatchPlayerReadyModel: public QObject
{
    Q_OBJECT
public:
    explicit DeathMatchPlayerReadyModel(QObject *parent = nullptr);

private:
    bool m_doorClosed = false;
    bool m_playerReady = false;
    QString m_readyText = "Not Ready";
    QString m_doorText = "Open";

    // Properties
    Q_PROPERTY(bool doorClosed READ doorClosed WRITE setDoorClosed RESET resetDoorClosed NOTIFY doorClosedChanged)
    Q_PROPERTY(bool playerReady READ playerReady WRITE setPlayerReady RESET resetPlayerReady NOTIFY playerReadyChanged)
    Q_PROPERTY(QString readyText READ readyText WRITE setReadyText RESET resetReadyText NOTIFY readyTextChanged)
    Q_PROPERTY(QString doorText READ doorText WRITE setDoorText RESET resetDoorText NOTIFY doorTextChanged)

public:
    bool doorClosed() const;
    bool playerReady() const;
    QString readyText() const;
    QString doorText() const;
public slots:
    void setDoorClosed(bool arg);
    void setDoorClosedForRound(bool arg);
    void resetDoorClosed();

    void setPlayerReady(bool arg);
    void setPlayerReadyForRound(bool arg);
    void resetPlayerReady();

    void setReadyText(QString arg);
    void resetReadyText();

    void setDoorText(QString arg);
    void resetDoorText();

    void reset();

private slots:
    void updateReadyText(bool arg);
    void updateDoorText(bool arg);
signals:
    void doorClosedChanged(bool arg);
    void playerReadyChanged(bool arg);
    void readyTextChanged(QString arg);
    void doorTextChanged(QString arg);
    void doorNotClosed(QString msg);
};
#endif // DEATHMATCHPLAYERREADYMODEL_H
