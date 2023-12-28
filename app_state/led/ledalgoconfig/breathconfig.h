#ifndef BREATHCONFIG_H
#define BREATHCONFIG_H

#include <QObject>
#include "integerobject.h"
#include "interpolationcurveobject.h"
#include "colorobject.h"
#include "booleanobject.h"
#include "qrealobject.h"

class LEDController;

class BreathConfig : public QObject
{
    Q_OBJECT
public:
    explicit BreathConfig(QString const& parentKeyPrefix, QObject *parent = nullptr);

    /// The time to breath either in or out.
    IntegerObject& cycleDuration();

    /// Indicates if we should use the player 1 configuration
    /// for p2 as well.
    BooleanObject& unified();

    /// The interpolation curve to use for player one.
    InterpolationCurveObject& p1Interpolation();

    /// The interpolation amplitude.
    QRealObject& p1CurveAmpliatude();

    /// The minimum brightness value.
    IntegerObject& p1MinBrightness();

    /// The maximum brightness value.
    IntegerObject& p1MaxBrightness();

    /// The color to use for player one.
    ColorObject& p1Color();

    /// The interpolation curve to use for player one.
    InterpolationCurveObject& p2Interpolation();

    QRealObject& p2CurveAmpliatude();

    /// The minimum brightness value.
    IntegerObject& p2MinBrightness();

    /// The maximum brightness value.
    IntegerObject& p2MaxBrightness();

    /// The color to use for player one.
    ColorObject& p2Color();
public slots:

    void init(QSettings *settings);
    void setLEDController(LEDController *);
private:
    QString m_settingsPrefix;
    IntegerObject m_duration;
    BooleanObject m_unified;

    // P1 configurations
    InterpolationCurveObject m_p1Interpolation;
    QRealObject m_p1CurveAmplitude;
    IntegerObject m_p1MinBrightness;
    IntegerObject m_p1MaxBrightness;
    ColorObject m_p1Color;

    // P2 configurations
    InterpolationCurveObject m_p2Interpolation;
    QRealObject m_p2CurveAmplitude;
    IntegerObject m_p2MinBrightness;
    IntegerObject m_p2MaxBrightness;
    ColorObject m_p2Color;
};

#endif // BREATHCONFIG_H
