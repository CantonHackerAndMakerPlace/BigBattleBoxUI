#ifndef LEDIDLECONFIGURATION_H
#define LEDIDLECONFIGURATION_H
#include <QObject>


class QSettings;

class LEDIdleConfiguration: public QObject
{
    Q_OBJECT
public:
    explicit LEDIdleConfiguration(QObject *parent = nullptr);


public slots:
    void loadSettings(QSettings *settings);

};

#endif // LEDIDLECONFIGURATION_H
