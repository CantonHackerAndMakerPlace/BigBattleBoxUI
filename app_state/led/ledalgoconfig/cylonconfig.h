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

    IntegerObject &startIndex();
    IntegerObject &stopIndex();
    IntegerObject &eyeLength();
    IntegerObject &cycleDuration();
    IntegerObject &p1Brightness();
    IntegerObject &p2Brightness();
    InterpolationCurveObject &curve();
    QRealObject &curveAmplitude();
    ColorObject &p1foregroundColor();
    ColorObject &p1backgroundColor();
    ColorObject &p2foregroundColor();
    ColorObject &p2backgroundColor();
    UnificationKindObject &unificationKind();

public slots:
    void init(QSettings *settings);
    void setLEDController(LEDController *controller);
private:
    QString m_settingsPrefix;
    IntegerObject m_startIndex;
    IntegerObject m_stopIndex;
    IntegerObject m_eyeLength;
    IntegerObject m_cycleDuration;
    IntegerObject m_p1Brightness;
    IntegerObject m_p2Brightness;
    InterpolationCurveObject m_curve;
    QRealObject m_curveAmplitude;
    ColorObject m_p1foregroundColor;
    ColorObject m_p1backgroundColor;
    ColorObject m_p2foregroundColor;
    ColorObject m_p2backgroundColor;
    UnificationKindObject m_unificationKind;

};

#endif // CYLONCONFIG_H
