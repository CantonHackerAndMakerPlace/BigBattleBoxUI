#ifndef COUNTDOWNFILLCONFIG_H
#define COUNTDOWNFILLCONFIG_H

#include <QObject>
#include "integerobject.h"
#include "booleanobject.h"
#include "interpolationcurveobject.h"
#include "colorobject.h"
#include "qrealobject.h"
#include "unificationkindobject.h"

#include "physical_state/ledcontroller.h"

class CountDownFillConfig : public QObject
{
    Q_OBJECT
public:
    explicit CountDownFillConfig(QString const& keyPrefix, QObject *parent = nullptr);
    IntegerObject &duration();
    UnificationKindObject &unificationKind();
    BooleanObject &loop();
    IntegerObject &timeBetweenCycles();

    IntegerObject &p1Brightness();
    InterpolationCurveObject &p1Curve();
    QRealObject &p1CurveAmplitude();

    ColorObject &p1ConsumingColor();
    ColorObject &p1InitialColor();
    ColorObject &p1FinalColor();
    IntegerObject &p1FinalColorBrightness();


    InterpolationCurveObject &p2Curve();
    QRealObject &p2CurveAmplitude();
    IntegerObject &p2Brightness();
    ColorObject &p2ConsumingColor();
    ColorObject &p2InitialColor();
    ColorObject &p2FinalColor();
    IntegerObject &p2FinalColorBrightness();
public slots:
    void init(QSettings *settings);
    void setLEDController(LEDController *controller);
private:
    QString m_settingsPrefix;
    IntegerObject m_duration;
    UnificationKindObject m_unificationKind;
    BooleanObject m_loop;
    IntegerObject m_timeBetweenCycles;


    IntegerObject m_p1Brightness;
    InterpolationCurveObject m_p1Curve;
    QRealObject m_p1CurveAmplitude;

    ColorObject m_p1ConsumedColor;
    ColorObject m_p1CountColor;
    ColorObject m_p1FinalColor;
    IntegerObject m_p1FinalColorBrightness;


    InterpolationCurveObject m_p2Curve;
    QRealObject m_p2CurveAmplitude;
    IntegerObject m_p2Brightness;
    ColorObject m_p2ConsumedColor;
    ColorObject m_p2CountColor;
    ColorObject m_p2FinalColor;
    IntegerObject m_p2FinalColorBrightness;
};

#endif // COUNTDOWNFILLCONFIG_H
