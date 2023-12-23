#ifndef LEDIDLECONFIGURATION_H
#define LEDIDLECONFIGURATION_H
#include <QObject>

#include "integerobject.h"
#include "interpolationcurveobject.h"
#include "colorobject.h"
#include "booleanobject.h"

class QSettings;

class LEDIdleConfiguration: public QObject
{
    Q_OBJECT
public:
    explicit LEDIdleConfiguration(QObject *parent = nullptr);

    /// The amount of time for a single cycle of the idle
    /// algorithm configuration to occur
    IntegerObject& cycleDuration();

    /// Indicates if we should use the player 1 configuration
    /// for p2 as well.
    BooleanObject& useP1ForBoth();

    /// The interpolation curve to use for player one.
    InterpolationCurveObject& p1Interpolation();

    /// The minimum brightness value.
    IntegerObject& p1MinBrightness();

    /// The maximum brightness value.
    IntegerObject& p1MaxBrightness();

    /// The color to use for player one.
    ColorObject& p1Color();

    /// The interpolation curve to use for player one.
    InterpolationCurveObject& p2Interpolation();

    /// The minimum brightness value.
    IntegerObject& p2MinBrightness();

    /// The maximum brightness value.
    IntegerObject& p2MaxBrightness();

    /// The color to use for player one.
    ColorObject& p2Color();

public slots:
    void loadSettings(QSettings *settings);
private:
    QSettings *m_settings;
    // Global configuration.
    IntegerObject m_duration;
    BooleanObject m_useP1ForBoth;

    // P1 configurations
    InterpolationCurveObject m_p1Interpolation;
    IntegerObject m_p1MinBrightness;
    IntegerObject m_p1MaxBrightness;
    ColorObject m_p1Color;

    // P2 configurations
    InterpolationCurveObject m_p2Interpolation;
    IntegerObject m_p2MinBrightness;
    IntegerObject m_p2MaxBrightness;
    ColorObject m_p2Color;
};

#endif // LEDIDLECONFIGURATION_H
