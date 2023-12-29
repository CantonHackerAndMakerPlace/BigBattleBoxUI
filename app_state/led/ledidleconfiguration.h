#ifndef LEDIDLECONFIGURATION_H
#define LEDIDLECONFIGURATION_H
#include <QObject>

#include "app_state/led/ledalgoconfig/ledalgoconfig.h"

class QSettings;

class LEDIdleConfiguration: public QObject
{
    Q_OBJECT
public:
    explicit LEDIdleConfiguration(QObject *parent = nullptr);

    /// The algorithm's global selection.
    LEDAlgoConfig &algoConfig();

public slots:
    void loadSettings(QSettings *settings);
private:
    QSettings *m_settings;
    LEDAlgoConfig *m_algoConfig;
};

#endif // LEDIDLECONFIGURATION_H
