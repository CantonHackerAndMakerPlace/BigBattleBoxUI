#ifndef LEDALGOCONFIG_H
#define LEDALGOCONFIG_H

#include <QObject>
#include "app_state/led/ledalgoconfig/breathconfig.h"
#include "app_state/led/ledalgoconfig/blinkconfig.h"
#include "app_state/led/ledalgoconfig/countdownfillconfig.h"
#include "app_state/led/ledalgoconfig/cylonconfig.h"
#include "app_state/led/ledalgoconfig/rampupconfig.h"
#include "app_state/led/ledalgoconfig/solidcolorconfig.h"

#include "algokindobject.h"

/// Base class for LED algorithm configuration that will allow for
/// switching between multiple algorithm configurations.
class LEDAlgoConfig : public QObject
{
    Q_OBJECT
public:

    explicit LEDAlgoConfig(QString const& settingsKeyPrefix, QObject *parent = nullptr);

    AlgoKindObject &getAlgoKind();

    BlinkConfig *getBlink() const;
    BreathConfig *getBreath() const;
    CountDownFillConfig *getCountDownFill() const;
    CylonConfig *getCylonConfig() const;
    RampUpConfig *getRampUpConfig() const;
    SolidColorConfig *getSolidColorConfig() const;
public slots:
    void init(QSettings* settings);
    void setLEDController(LEDController* controller);
private:
    AlgoKindObject m_algo;
    BlinkConfig *m_blink;
    BreathConfig *m_breath;
    CountDownFillConfig *m_countDown;
    CylonConfig *m_cylon;
    RampUpConfig *m_rampUp;
    SolidColorConfig *m_solidColors;
};

#endif // LEDALGOCONFIG_H
