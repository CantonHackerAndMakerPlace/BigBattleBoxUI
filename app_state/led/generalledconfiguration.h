#ifndef GENERALLEDCONFIGURATION_H
#define GENERALLEDCONFIGURATION_H

#include <QObject>
#include "integerobject.h"
class QSettings;

class GeneralLEDConfiguration : public QObject
{
    Q_OBJECT
public:
    explicit GeneralLEDConfiguration(QObject *parent = nullptr);

    /// The arduino pin for player one's lights
    IntegerObject& playerOneLedPin();

    /// The number of addressable LED attached to player One.
    IntegerObject& playerOneLedCount();

    /// The direction we should associate with the player two's lights
    /// either forward(0) or backward(1).
    IntegerObject& playerOneLedDirection();

    /// The arduino pin for player two's lights
    IntegerObject& playerTwoLedPin();

    /// The number of addressable LED attached to player Two.
    IntegerObject& playerTwoLedCount();

    /// The direction we should associate with the player two's lights
    /// either forward(0) or backward(1).
    IntegerObject& playerTwoLedDirection();

    /// The ordering of the lights either 0 or 1 if 0 for player 1 and 1 for
    /// player two first.
    IntegerObject& lightOrder();
public slots:
    void loadSettings(QSettings *settings);
private:
    QSettings *m_settings;
    IntegerObject m_p1Pin;
    IntegerObject m_p1LedCount;
    IntegerObject m_p1Direction;

    IntegerObject m_p2Pin;
    IntegerObject m_p2LedCount;
    IntegerObject m_p2Direction;

    IntegerObject m_lightOrder;
};

#endif // GENERALLEDCONFIGURATION_H
