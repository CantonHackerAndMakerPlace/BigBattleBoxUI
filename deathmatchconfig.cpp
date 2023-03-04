#include "deathmatchconfig.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

DeathMatchConfig::DeathMatchConfig(QObject *parent)
    : QObject{parent}
{
    reset();
}

void DeathMatchConfig::initializeFromSettings(QSettings *settings) {
    // Default door drop settings.
//    constexpr const char *dmddTime = "deathmatch_default/doorDropTime";
    //    if (m_data)
//    m_data->settings()->value(, DeathMatchConfig::DEFAULT_DOOR_DROP_TIME);
//    m_data->settings()->value("deathmatch_default/matchDuration", DeathMatchConfig::DEFAULT_MATCH_DURATION);
//    m_data->settings()->value("deathmatch_default/playerOneName", "");
//    m_data->settings()->value("deathmatch_default/playerTwoName", "");
//    m_data->settings()->value("deathmatch_default/doorDropKind", toSettingsString(DeathMatchConfig::DEFAULT_DOOR_DROP_KIND));
}

QString DeathMatchConfig::doorDropKindAsString() const {
    switch(m_doorDropKind) {
    case DoorDrop::Random:
        return "Random";
    case DoorDrop::Both:
        return "Both";
    case DoorDrop::Never:
        return "Never";
    case DoorDrop::AlwaysOpen:
        return "Always Open";
    case DoorDrop::PlayerOne:
        return "Player One";
    case DoorDrop::PlayerTwo:
        return "Player Two";
    default:
        qWarning() << "unknown door drop kind.";
        abort();
    }
}

void DeathMatchConfig::setPlayerOneName(QString const& new_name) {
    if (m_playerOneName != new_name) {
        m_playerOneName = new_name;
        emit playerOneNameChanged(m_playerOneName);
    }
}
void DeathMatchConfig::resetPlayerOneName() {
    setPlayerOneName("");
}

void DeathMatchConfig::setPlayerTwoName(QString const& new_name) {
    if (m_playerTwoName != new_name) {
        m_playerTwoName = new_name;
        emit playerTwoNameChanged(m_playerTwoName);
    }
}
void DeathMatchConfig::resetPlayerTwoName() {
    setPlayerTwoName("");
}

void DeathMatchConfig::setMatchDuration(int value) {
    if(m_matchDuration != value) {
        m_matchDuration = value;
        emit matchDurationChanged(m_matchDuration);
    }
}
void DeathMatchConfig::resetMatchDuration() {
    setMatchDuration(DEFAULT_MATCH_DURATION);
}

void DeathMatchConfig::setDoorDropTime(int value) {
    if(m_doorDropTime != value) {
        m_doorDropTime = value;
        emit doorDropChanged(m_doorDropTime);
    }

}
void DeathMatchConfig::resetDoorDropTime() {
    setDoorDropTime(DEFAULT_DOOR_DROP_TIME);
}

auto DeathMatchConfig::fromInt(int val) ->DoorDrop {
    switch(val) {
    case 0:
        return DoorDrop::Random;
    case 1:
        return DoorDrop::Both;
    case 2:
        return DoorDrop::Never;
    case 3:
        return DoorDrop::AlwaysOpen;
    case 4:
        return DoorDrop::PlayerOne;
    case 5:
        return DoorDrop::PlayerTwo;
    default:
        std::cout << "Invalid conversion" << std::endl;
        abort();
    }
}

void DeathMatchConfig::setDoorDropKind(DeathMatchConfig::DoorDrop value) {
    if(m_doorDropKind != value) {
        m_doorDropKind = value;
        emit doorDropKindChanged(m_doorDropKind);
        emit doorDropKindChangedInt((int)m_doorDropKind);
    }
}

void DeathMatchConfig::setDoorDropKindFromInt(int value) {
    if((int)m_doorDropKind != value) {
        m_doorDropKind = fromInt(value);
        emit doorDropKindChanged(m_doorDropKind);
        emit doorDropKindChangedInt((int)m_doorDropKind);
    }
}
void DeathMatchConfig::resetDoorDropKind() {
    setDoorDropKind(DoorDrop::Random);
}

void DeathMatchConfig::reset() {
    resetMatchDuration();
    resetDoorDropKind();
    resetDoorDropTime();
    resetPlayerOneName();
    resetPlayerTwoName();
}

void DeathMatchConfig::saveToFile(QString path) {

    QJsonObject content;
    content["type"] = "DeathMatchConfig";
    content["playerOneName"] = this->playerOneName();
    content["playerTwoName"] = this->playerTwoName();
    content["doorDropKind"] = (int)this->doorDropKind();
    content["matchDuration"] = this->matchDuration();
    content["doorDropTime"] = this->doorDropTime();
    QJsonDocument document;
    document.setObject( content );
    QByteArray bytes = document.toJson( QJsonDocument::Indented );
    QFile file( path );
    if( file.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ) )
    {
        QTextStream iStream( &file );
        iStream.setEncoding(QStringConverter::Utf8);
        iStream << bytes;
        file.close();
    }
    else
    {
        emit error(QString("error saving file: Path '%1'").arg(path));
    }

}

void DeathMatchConfig::loadFromFile(QString path) {
    QString val;
    QFile file;
    file.setFileName(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject root = doc.object();
    auto opt_type = getJsonString(path, root, "type");
    if (!opt_type.has_value()) {
        return;
    }
    auto type = opt_type.value();
    if(type != "DeathMatchConfig") {
        emit error(QString("error loading file: invalid value for 'type' field. Expected value: 'DeathMatchConfig', received value: '%1' Path '%2'").arg(type, path));
        return;
    }

    auto optP1 = getJsonString(path, root, "playerOneName");
    if (!optP1.has_value()) {
        return;
    }

    auto optP2 = getJsonString(path, root, "playerTwoName");
    if (!optP2.has_value()) {
        return;
    }

    auto optDoorDropKind = getJsonInt(path, root, "doorDropKind");
    if (!optDoorDropKind.has_value()) {
        return;
    }

    // Validating door drop kind.
    if(optDoorDropKind.value() > 6 || optDoorDropKind.value() < 0) {
        emit error(QString("error loading file: invalid valid for 'doorDropKind' field. Value outside of valid range. Value: '%1'. Path '%2'").arg(
                    QString::number(optDoorDropKind.value()), path));
        return;
    }

    auto optMatchDuration = getJsonInt(path, root, "matchDuration");
    if (!optMatchDuration.has_value()) {
        return;
    }

    auto optDoorDropTime = getJsonInt(path, root, "doorDropTime");
    if (!optDoorDropTime.has_value()) {
        return;
    }

    // Setting everything after read is completed need to verify a
    // few things before this
    this->setPlayerOneName(optP1.value());
    this->setPlayerTwoName(optP2.value());
    this->setMatchDuration(optMatchDuration.value());
    this->setDoorDropKindFromInt(optDoorDropKind.value());
    this->setDoorDropTime(optDoorDropTime.value());

}

std::optional<QString> DeathMatchConfig::getJsonString(QString path, QJsonObject &obj, QString name) {
    auto iter = obj.find(name);
    if (iter == obj.end()) {
        emit error(QString("error loading file: failed to locate '%1' field. Path '%2'").arg(name, path));
        return std::nullopt;
    }
    if (!iter->isString()) {
        emit error(QString("error loading file: invalid value for '%1' field. Path '%2'").arg(name, path));
        return std::nullopt;
    }
    return std::optional<QString>(iter->toString());
}

std::optional<int> DeathMatchConfig::getJsonInt(QString path, QJsonObject &obj, QString name) {
    auto iter = obj.find(name);
    if (iter == obj.end()) {
        emit error(QString("error loading file: failed to locate '%1' field. Path '%2'").arg(name, path));
        return std::nullopt;
    }
    if (!iter->isDouble()) {
        emit error(QString("error loading file: invalid value for '%1' field. Path '%2'").arg(name, path));
        return std::nullopt;
    }
    auto i = iter->toInt(INT_MAX);
    if(i == INT_MAX) {
        emit error(QString("error loading file: invalid value for '%1' field. Path '%2'").arg(name, path));
        return std::nullopt;
    }
    return std::optional<int>(i);
}
