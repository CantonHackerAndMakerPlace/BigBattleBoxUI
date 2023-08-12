#ifndef GENERALLEDCONFIGURATION_H
#define GENERALLEDCONFIGURATION_H

#include <QObject>

class GeneralLEDConfiguration : public QObject
{
    Q_OBJECT
public:
    explicit GeneralLEDConfiguration(QObject *parent = nullptr);

signals:

};

#endif // GENERALLEDCONFIGURATION_H
