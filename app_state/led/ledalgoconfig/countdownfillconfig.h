#ifndef COUNTDOWNFILLCONFIG_H
#define COUNTDOWNFILLCONFIG_H

#include <QObject>
#include "integerobject.h"
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

    IntegerObject &p1Brightness();
    InterpolationCurveObject &curve();
    QRealObject &curveAmplitude();

    ColorObject &p1ConsumedColor();
    ColorObject &p1CountColor();
    ColorObject &p1FinalColor();
    IntegerObject &p1FinalColorBrightness();

    IntegerObject &p2Brightness();

    ColorObject &p2ConsumedColor();
    ColorObject &p2CountColor();
    ColorObject &p2FinalColor();
    IntegerObject &p2FinalColorBrightness();
public slots:
    void init(QSettings *settings);
    void setLEDController(LEDController *controller);
private:
    QString m_settingsPrefix;
    IntegerObject m_duration;
    UnificationKindObject m_unificationKind;

    IntegerObject m_p1Brightness;
    InterpolationCurveObject m_curve;
    QRealObject m_curveAmplitude;

    ColorObject m_p1ConsumedColor;
    ColorObject m_p1CountColor;
    ColorObject m_p1FinalColor;
    IntegerObject m_p1FinalColorBrightness;

    IntegerObject m_p2Brightness;
    ColorObject m_p2ConsumedColor;
    ColorObject m_p2CountColor;
    ColorObject m_p2FinalColor;
    IntegerObject m_p2FinalColorBrightness;
};

#endif // COUNTDOWNFILLCONFIG_H
