#ifndef SOLIDCOLORCONFIG_H
#define SOLIDCOLORCONFIG_H

#include <QObject>
#include "integerobject.h"
#include "colorobject.h"
#include "booleanobject.h"

#include "physical_state/ledcontroller.h"

class SolidColorConfig : public QObject
{
    Q_OBJECT
public:
    explicit SolidColorConfig(QString const& keyPrefix, QObject *parent = nullptr);

    ColorObject &p1Color();
    IntegerObject &p1Brightness();
    ColorObject &p2Color();
    IntegerObject &p2Brightness();
    BooleanObject &unified();
public slots:
    void init(QSettings *settings);
    void setLEDController(LEDController *controller);
private:
    QString m_keyPrefix;
    ColorObject m_p1Color;
    IntegerObject m_p1brightness;
    ColorObject m_p2Color;
    IntegerObject m_p2brightness;
    BooleanObject m_unified;
};

#endif // SOLIDCOLORCONFIG_H
