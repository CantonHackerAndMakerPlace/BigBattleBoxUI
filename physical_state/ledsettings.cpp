#include "ledsettings.h"
#include <stdexcept>

LEDSettings::LEDSettings(QString name, int pin, int numberOfLights, QObject *parent )
    :QObject(parent),
    m_name(name),
    m_pin(pin),
    m_numberOfLights(numberOfLights)
{ }

/// Used for saving A JSON object into a separate file.
QJsonObject LEDSettings::serialize() {
    throw std::runtime_error("Not implemented yet");
}

void LEDSettings::deserialize(QJsonObject &obj){
    throw std::runtime_error("Not implemented yet");
}

int LEDSettings::pin() const {
    return m_pin;
}

int LEDSettings::numberOfLights() const {
    return m_numberOfLights;
}

QString LEDSettings::name() const {
    return m_name;
}

void LEDSettings::setName(QString name) {
    if (m_name != name) {
        m_name = name;
        emit nameChanged(m_name);
    }
}

void LEDSettings::setPin(int pin) {
    if (m_pin != pin) {
        m_pin = pin;
        emit pinChanged(m_pin);
    }
}

void LEDSettings::setNumberOfLights(int count) {
    if (m_numberOfLights != count) {
        m_numberOfLights = count;
        emit numberOfLightsChanged(m_numberOfLights);
    }

}

//void DeathMatchConfig::saveToFile(QString path) {

//    QJsonObject content;
//    content["type"] = "DeathMatchConfig";
//    content["playerOneName"] = this->playerOneName();
//    content["playerTwoName"] = this->playerTwoName();
//    content["doorDropKind"] = (int)this->doorDropKind();
//    content["matchDuration"] = this->matchDuration();
//    content["doorDropTime"] = this->doorDropTime();
//    QJsonDocument document;
//    document.setObject( content );
//    QByteArray bytes = document.toJson( QJsonDocument::Indented );
//    QFile file( path );
//    if( file.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ) )
//    {
//        QTextStream iStream( &file );
//        iStream.setEncoding(QStringConverter::Utf8);
//        iStream << bytes;
//        file.close();
//    }
//    else
//    {
//        emit error(QString("error saving file: Path '%1'").arg(path));
//    }
//}

