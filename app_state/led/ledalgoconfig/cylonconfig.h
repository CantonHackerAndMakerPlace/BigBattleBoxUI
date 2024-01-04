#ifndef CYLONCONFIG_H
#define CYLONCONFIG_H

#include <QObject>

#include "integerobject.h"
#include "interpolationcurveobject.h"
#include "colorobject.h"
#include "qrealobject.h"
#include "unificationkindobject.h"

#include "physical_state/ledcontroller.h"

class CylonConfig : public QObject
{
    Q_OBJECT
public:
    explicit CylonConfig(QString const& keyPrefix, QObject *parent = nullptr);
    IntegerObject &eyeLength();
    IntegerObject &cycleDuration();

    IntegerObject &p1Brightness();
    InterpolationCurveObject &p1Curve();
    QRealObject &p1CurveAmplitude();
    ColorObject &p1ForegroundColor();
    ColorObject &p1BackgroundColor();



    IntegerObject &p2Brightness();
    InterpolationCurveObject &p2Curve();
    QRealObject &p2CurveAmplitude();
    ColorObject &p2ForegroundColor();
    ColorObject &p2BackgroundColor();

    UnificationKindObject &unificationKind();

public slots:
    void init(QSettings *settings);
    void setLEDController(LEDController *controller);
private:
    QString m_settingsPrefix;
    IntegerObject m_eyeLength;
    IntegerObject m_cycleDuration;
    IntegerObject m_p1Brightness;
    IntegerObject m_p2Brightness;
    InterpolationCurveObject m_p1Curve;
    QRealObject m_p1CurveAmplitude;
    ColorObject m_p1foregroundColor;
    ColorObject m_p1backgroundColor;
    ColorObject m_p2foregroundColor;
    ColorObject m_p2backgroundColor;
    InterpolationCurveObject m_p2Curve;
    QRealObject m_p2CurveAmplitude;
    UnificationKindObject m_unificationKind;

};

#endif // CYLONCONFIG_H
