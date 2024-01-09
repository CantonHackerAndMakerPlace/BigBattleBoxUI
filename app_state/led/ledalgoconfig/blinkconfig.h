#ifndef BLINKCONFIG_H
#define BLINKCONFIG_H

#include <QObject>
#include "integerobject.h"
#include "colorobject.h"
#include "booleanobject.h"
class LEDController;

class BlinkConfig : public QObject
{
    Q_OBJECT
public:
    explicit BlinkConfig(QString const& settingKeyPrefix, QObject *parent = nullptr);

    IntegerObject &numberOfBlinks();
    IntegerObject &onDuration();
    IntegerObject &offDuration();
    BooleanObject &unified();

    ColorObject &p1OnColor();
    IntegerObject &p1OnBrightness();

    ColorObject &p1OffColor();
    IntegerObject &p1OffBrightness();


    ColorObject &p2OnColor();
    IntegerObject &p2OnBrightness();

    ColorObject &p2OffColor();
    IntegerObject &p2OffBrightness();
public slots:
    void init(QSettings* settings);
    void setLEDController(LEDController* controller);
private:

    IntegerObject m_numberOfBlinks;
    IntegerObject m_onDuration;
    IntegerObject m_offDuration;
    BooleanObject m_unified;

    ColorObject m_p1OnColor;
    IntegerObject m_p1OnBrightness;

    ColorObject m_p1OffColor;
    IntegerObject m_p1OffBrightness;

    ColorObject m_p2OnColor;
    IntegerObject m_p2OnBrightness;

    ColorObject m_p2OffColor;
    IntegerObject m_p2OffBrightness;
};

#endif // BLINKCONFIG_H

