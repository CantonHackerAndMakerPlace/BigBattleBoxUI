#ifndef LEDIDLECONFIGURATION_H
#define LEDIDLECONFIGURATION_H
#include <QObject>

class LEDIdleConfiguration: public QObject
{
    Q_OBJECT
public:
    explicit LEDIdleConfiguration(QObject *parent = nullptr);
};

#endif // LEDIDLECONFIGURATION_H
