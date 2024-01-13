#ifndef LEDCONFIGURATION_H
#define LEDCONFIGURATION_H

#include <QObject>
#include <QSettings>

#include <app_state/led/generalledconfiguration.h>
#include <app_state/led/ledidleconfiguration.h>
#include <app_state/led/deathmatchledconfiguration.h>

class LEDConfiguration : public QObject
{
    Q_OBJECT
public:
    explicit LEDConfiguration(QObject *parent = nullptr);

    /// Returns a pointer to the current General LED configuration object
    GeneralLEDConfiguration *generalLEDConfiguration() const;

    /// Returns a pointer to the current Idle LED configuration Object.
    LEDIdleConfiguration *idleConfiguration() const;

    /// Returns deathmatch LED settings
    DeathMatchLEDConfiguration *deathMatchConfiguration() const;

public slots:
    void loadSettings(QSettings *settings);

private:
    GeneralLEDConfiguration *m_generalLedConfig;
    LEDIdleConfiguration *m_idleConfig;
    DeathMatchLEDConfiguration *m_dmConfig;
};

#endif // LEDCONFIGURATION_H
