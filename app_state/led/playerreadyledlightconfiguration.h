#ifndef PLAYERREADYLEDLIGHTCONFIGURATION_H
#define PLAYERREADYLEDLIGHTCONFIGURATION_H

#include <QObject>
#include "integerobject.h"
#include "colorobject.h"
#include "booleanobject.h"


class PlayerReadyLEDLightConfiguration : public QObject
{
    Q_OBJECT
public:
    explicit PlayerReadyLEDLightConfiguration(QString const& keyPrefix, QObject *parent = nullptr);

    // Global settings.
    BooleanObject &blinkOnCancel();
    IntegerObject &numberOfBlinks();
    IntegerObject &onDuration();
    IntegerObject &offDuration();


    // Player one stuff.
    ColorObject &p1NotReadyColor();
    IntegerObject &p1NotReadyBrightness();

    ColorObject &p1ReadyColor();
    IntegerObject &p1ReadyBrightness();

    ColorObject &p1BlinkOnColor();
    IntegerObject &p1BlinkOnBrightness();

    ColorObject &p1BlinkOffColor();
    IntegerObject &p1BlinkOffBrightness();



    // Player two stuff.
    ColorObject &p2NotReadyColor();
    IntegerObject &p2NotReadyBrightness();

    ColorObject &p2ReadyColor();
    IntegerObject &p2ReadyBrightness();

    ColorObject &p2BlinkOnColor();
    IntegerObject &p2BlinkOnBrightness();

    ColorObject &p2BlinkOffColor();
    IntegerObject &p2BlinkOffBrightness();
public slots:
    void init(QSettings *settings);
private:
    QString m_keyPrefix;
    BooleanObject m_blinkOnCancel;
    IntegerObject m_numberOfBlinks;
    IntegerObject m_onDuration;
    IntegerObject m_offDuration;

    // Player one stuff.
    ColorObject m_p1ColorNotReady;
    IntegerObject m_p1NotReadyBrightness;

    ColorObject m_p1ColorReadyColor;
    IntegerObject m_p1ReadyBrightness;

    ColorObject m_p1BlinkOnColor;
    IntegerObject m_p1BlinkOnBrightness;

    ColorObject m_p1BlinkOffColor;
    IntegerObject m_p1BlinkOffBrightness;



    // Player two stuff.
    ColorObject m_p2ColorNotReady;
    IntegerObject m_p2NotReadyBrightness;

    ColorObject m_p2ColorReadyColor;
    IntegerObject m_p2ReadyBrightness;

    ColorObject m_p2BlinkOnColor;
    IntegerObject m_p2BlinkOnBrightness;

    ColorObject m_p2BlinkOffColor;
    IntegerObject m_p2BlinkOffBrightness;
//signals:

};

#endif // PLAYERREADYLEDLIGHTCONFIGURATION_H
