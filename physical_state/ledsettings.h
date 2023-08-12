#ifndef LEDSETTINGS_H
#define LEDSETTINGS_H
#include <QObject>
#include <QJsonObject>

/// This class contains color related information for
/// one ore many of the particular available LED States.
///
/// This is for a single strand, and can be used to send
/// commands to the arduino to update the displayed
/// lights.
///
/// The main goal here is to ensure that the LIGHT are configured
/// properly and can be easily changed by the applications user.
///
/// Because of the nature of how the LED lights are handled by the
/// arduino, all of the necessary information about the LED Lights
/// are stored here, and used to initialzie the arduino on start up.
class LEDSettings : public QObject
{
    Q_OBJECT
public:
    LEDSettings(QString name, int pin, int numberOfLights, QObject *parent = nullptr);

    /// Used for saving A JSON object into a separate file.
    QJsonObject serialize();
    void deserialize(QJsonObject &obj);

    int pin() const;
    int numberOfLights() const;
    QString name() const;

public slots:
    void setName(QString new_name);
    void setPin(int pin);
    void setNumberOfLights(int count);

signals:
    void nameChanged(QString);
    void pinChanged(int);
    void numberOfLightsChanged(int);

private:
    QString m_name;
    int m_pin;
    int m_numberOfLights;
};

#endif // LEDSETTINGS_H
