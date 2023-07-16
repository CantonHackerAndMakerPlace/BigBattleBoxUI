#include "soccerconfig.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

SoccerConfig::SoccerConfig(QObject *parent)
    :QObject(parent)
{

}

SoccerConfig::~SoccerConfig() { }

constexpr char const *TYPE_JSON_NAME = "type";
constexpr char const *TYPE_JSON_VALUE = "SoccerConfig";
constexpr char const *TEAM_ONE_JSON_NAME = "teamOneName";
constexpr char const *TEAM_TWO_JSON_NAME = "teamTwoName";
constexpr char const *MATCH_DURATION_JSON_NAME = "matchDuration";
constexpr char const *MAX_SCORE_JSON_NAME = "maxScore";

void SoccerConfig::saveToFile(QString path) {

    QJsonObject content;
    content[TYPE_JSON_NAME] = TYPE_JSON_VALUE;
    content[TEAM_ONE_JSON_NAME] = this->teamOneName();
    content[TEAM_TWO_JSON_NAME] = this->teamTwoName();
    content[MATCH_DURATION_JSON_NAME] = this->matchDuration();
    content[MAX_SCORE_JSON_NAME] = this->maxScore();
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

void SoccerConfig::loadFromFile(QString path) {
    QString val;
    QFile file;
    file.setFileName(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject root = doc.object();
    auto opt_type = getJsonString(path, root, TYPE_JSON_NAME);
    if (!opt_type.has_value()) {
        return;
    }
    auto type = opt_type.value();
    if(type != TYPE_JSON_VALUE) {
        emit error(QString("error loading file: invalid value for 'type' field. Expected value: 'SoccerConfig', received value: '%1' Path '%2'").arg(type, path));
        return;
    }

    auto optT1 = getJsonString(path, root, TEAM_ONE_JSON_NAME);
    if (!optT1.has_value()) {
        return;
    }

    auto optT2 = getJsonString(path, root, TEAM_TWO_JSON_NAME);
    if (!optT2.has_value()) {
        return;
    }

    auto optMaxScore = getJsonInt(path, root, MAX_SCORE_JSON_NAME);
    if (!optMaxScore.has_value()) {
        return;
    }

    auto optMatchDuration = getJsonInt(path, root, MATCH_DURATION_JSON_NAME);
    if (!optMatchDuration.has_value()) {
        return;
    }


    // Setting everything after read is completed need to verify a
    // few things before this
    this->setTeamOneName(optT1.value());
    this->setTeamTwoName(optT2.value());
    this->setMatchDuration(optMatchDuration.value());
    this->setMaxScore(optMaxScore.value());
}

std::optional<QString> SoccerConfig::getJsonString(QString path, QJsonObject &obj, QString name) {
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

std::optional<int> SoccerConfig::getJsonInt(QString path, QJsonObject &obj, QString name) {
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
