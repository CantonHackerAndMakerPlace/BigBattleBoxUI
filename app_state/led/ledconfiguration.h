#ifndef LEDCONFIGURATION_H
#define LEDCONFIGURATION_H

#include <QObject>

class LEDConfiguration : public QObject
{
    Q_OBJECT
public:
    explicit LEDConfiguration(QObject *parent = nullptr);

signals:

};

#endif // LEDCONFIGURATION_H
