#ifndef DEATHMATCHGAMESESSION_H
#define DEATHMATCHGAMESESSION_H

#include <QObject>

class DeathMatchGameSession : public QObject
{
    Q_OBJECT
public:
    explicit DeathMatchGameSession(QObject *parent = nullptr);

signals:

};

#endif // DEATHMATCHGAMESESSION_H
