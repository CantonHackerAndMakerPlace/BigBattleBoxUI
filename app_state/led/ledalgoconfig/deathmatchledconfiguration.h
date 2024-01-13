#ifndef DEATHMATCHLEDCONFIGURATION_H
#define DEATHMATCHLEDCONFIGURATION_H

#include <QObject>

class DeathMatchLEDConfiguration : public QObject
{
    Q_OBJECT
public:
    explicit DeathMatchLEDConfiguration(QObject *parent = nullptr);

signals:

};

#endif // DEATHMATCHLEDCONFIGURATION_H
