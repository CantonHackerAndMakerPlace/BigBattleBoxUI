#ifndef RAMPUPCONFIG_H
#define RAMPUPCONFIG_H

#include <QObject>

#include "integerobject.h"
#include "interpolationcurveobject.h"
#include "colorobject.h"
#include "booleanobject.h"
#include "qrealobject.h"

#include "physical_state/ledcontroller.h"

class RampUpConfig : public QObject
{
    Q_OBJECT
public:
    explicit RampUpConfig(QString const& keyPrefix, QObject *parent = nullptr);

    IntegerObject &cycleDuration();
    InterpolationCurveObject &p1Curve();
    QRealObject &p1Amplitude();
    ColorObject &p1Color();
    IntegerObject &p1MinBrightness();
    IntegerObject &p1MaxBrightness();
    InterpolationCurveObject &p2Curve();
    QRealObject &p2Amplitude();
    ColorObject &p2Color();
    IntegerObject &p2MinBrightness();
    IntegerObject &p2MaxBrightness();
    BooleanObject &unified();
    BooleanObject &loop();
public slots:
    void init(QSettings *settings);
    void setLEDController(LEDController *controller);
private:
    QString m_keyPrefix;
    IntegerObject m_cycleDuration;
    InterpolationCurveObject m_p1Curve;
    QRealObject m_p1Amplitude;
    ColorObject m_p1Color;
    IntegerObject m_p1MinBrightness;
    IntegerObject m_p1MaxBrightness;
    InterpolationCurveObject m_p2Curve;
    QRealObject m_p2Amplitude;
    ColorObject m_p2Color;
    IntegerObject m_p2MinBrightness;
    IntegerObject m_p2MaxBrightness;
    BooleanObject m_unified;
    BooleanObject m_loop;
};

#endif // RAMPUPCONFIG_H
