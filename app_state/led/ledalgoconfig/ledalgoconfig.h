#ifndef LEDALGOCONFIG_H
#define LEDALGOCONFIG_H

#include <QObject>
#include "app_state/led/ledalgoconfig/breathconfig.h"
#include "app_state/led/ledalgoconfig/blinkconfig.h"
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

public slots:
    void init(QSettings* settings);
    void setLEDController(LEDController* controller);
//signals:
    /// Signal emitted when the kind of algorithm changes.
//    void kindChanged(Kind newKind, Kind oldKind);
private:
    AlgoKindObject m_algo;
    BlinkConfig *m_blink;
    BreathConfig *m_breath;
};

#endif // LEDALGOCONFIG_H
