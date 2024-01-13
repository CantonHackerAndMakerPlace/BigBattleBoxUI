#ifndef WINNINGPLAYERLIGHTCONFIGURATION_H
#define WINNINGPLAYERLIGHTCONFIGURATION_H

#include <QObject>
#include "app_state/led/ledalgoconfig/ledalgoconfig.h"

class WinningPlayerLightConfiguration : public QObject
{
    Q_OBJECT
public:
    explicit WinningPlayerLightConfiguration(QString const& keyPrefix, QObject *parent = nullptr);

    LEDAlgoConfig *playerOne() const;
    LEDAlgoConfig *playerTwo() const;
public slots:
    void init(QSettings *settings);
private:
    QString m_keyPrefix;
    LEDAlgoConfig *m_p1;
    LEDAlgoConfig *m_p2;
};

#endif // WINNINGPLAYERLIGHTCONFIGURATION_H
