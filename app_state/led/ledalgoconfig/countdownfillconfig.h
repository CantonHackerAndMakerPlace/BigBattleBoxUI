#ifndef COUNTDOWNFILLCONFIG_H
#define COUNTDOWNFILLCONFIG_H

#include <QObject>
#include "integerobject.h"
#include "interpolationcurveobject.h"
#include "colorobject.h"
#include "booleanobject.h"
#include "qrealobject.h"

class CountDownFillConfig : public QObject
{
    Q_OBJECT
public:
    explicit CountDownFillConfig(QObject *parent = nullptr);
    IntegerObject &duration();
    IntegerObject &p1Brightness();
    InterpolationCurveObject &p1Curve();
    QRealObject &p1CurveAmplitude();

    ColorObject &p1ConsumedColor();
    ColorObject &p1CountColor();
    ColorObject &p1FinalColor();
    IntegerObject &p1FinalColorBrightness();

//    int duration,
//    int p1brightness,
//    QEasingCurve easingCurve,
//    QColor p1ConsumedColor,
//    QColor p1CountColor,
//    QColor p1FinalColor,
//    int p1FinalColorBrightness,
//    int p2brightness,
//    QColor p2ConsumedColor,
//    QColor p2CountColor,
//    QColor p2FinalColor,
//    int p2FinalColorBrightness,
//    bool unifiedLedStrips
private:
};

#endif // COUNTDOWNFILLCONFIG_H
