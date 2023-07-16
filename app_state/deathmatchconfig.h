#ifndef DEATHMATCHCONFIG_H
#define DEATHMATCHCONFIG_H

#include <QObject>
#include <QString>
#include <iostream>
class QSettings;

class DeathMatchConfig : public QObject
{
    Q_OBJECT
    Q_ENUMS(DoorDrop)
public:
    explicit DeathMatchConfig(QObject *parent = nullptr);

    enum class DoorDrop {
        Random,
        Both,
        Never,
        AlwaysOpen,
        PlayerOne,
        PlayerTwo
    };

    static constexpr int DEFAULT_MATCH_DURATION = 180;
    static constexpr int DEFAULT_DOOR_DROP_TIME = 60;
    static constexpr DoorDrop DEFAULT_DOOR_DROP_KIND = DoorDrop::Random;
private:

    // Members
    int m_matchDuration;
    int m_doorDropTime;
    QString m_playerOneName;
    QString m_playerTwoName;
    DoorDrop m_doorDropKind;


    // Properties
    Q_PROPERTY(int m_matchDuration READ matchDuration WRITE setMatchDuration RESET resetMatchDuration NOTIFY matchDurationChanged)
    Q_PROPERTY(int m_doorDropTime READ doorDropTime WRITE setDoorDropTime RESET resetDoorDropTime NOTIFY doorDropChanged)
    Q_PROPERTY(QString m_playerOneName READ playerOneName WRITE setPlayerOneName RESET resetPlayerOneName NOTIFY playerOneNameChanged)
    Q_PROPERTY(QString m_playerTwoName READ playerTwoName WRITE setPlayerTwoName RESET resetPlayerTwoName NOTIFY playerTwoNameChanged)
    Q_PROPERTY(DoorDrop m_doorDropKind READ doorDropKind WRITE setDoorDropKind RESET resetDoorDropKind NOTIFY doorDropKindChanged)


public:

    void initializeFromSettings(QSettings *settings);

    static DoorDrop fromInt(int val);
    int matchDuration() const {
        return m_matchDuration;
    }

    int doorDropTime() const {
        return m_doorDropTime;
    }

    QString const& playerOneName() const {
        return m_playerOneName;
    }

    QString const& playerTwoName() const {
        return m_playerOneName;
    }

    DoorDrop doorDropKind() const{
        return m_doorDropKind;
    }

    QString doorDropKindAsString() const;

public slots:
    void setPlayerOneName(QString const& new_name);
    void resetPlayerOneName();

    void setPlayerTwoName(QString const& new_name);
    void resetPlayerTwoName();

    void setMatchDuration(int value);
    void resetMatchDuration();

    void setDoorDropTime(int value);
    void resetDoorDropTime();

    void setDoorDropKind(DeathMatchConfig::DoorDrop value);
    void setDoorDropKindFromInt(int value);
    void resetDoorDropKind();

    void reset();

signals:
    void matchDurationChanged(int arg);
    void doorDropChanged(int arg);
    void playerOneNameChanged(QString arg);
    void playerTwoNameChanged(QString arg);
    void doorDropKindChanged(DeathMatchConfig::DoorDrop arg);
    void doorDropKindChangedInt(int arg);
    void error(QString message);

public:
    void saveToFile(QString path);
    void loadFromFile(QString path);
private:
    std::optional<QString> getJsonString(QString path, QJsonObject &obj, QString name);
    std::optional<int> getJsonInt(QString path, QJsonObject &obj, QString name);
};

constexpr const char* DD_RANDOM = "random";
constexpr const char* DD_BOTH = "both";
constexpr const char* DD_NEVER = "never";
constexpr const char* DD_ALWAYS_OPEN = "alwaysopen";
constexpr const char* DD_PLAYER_ONE = "playerone";
constexpr const char* DD_PLAYER_TWO = "playertwo";

inline std::optional<DeathMatchConfig::DoorDrop> settingsStringToDoorDrop(QAnyStringView name) {
    QString lowerCaseName = name.toString().toLower();
    if (lowerCaseName == DD_RANDOM) {
        return std::optional<DeathMatchConfig::DoorDrop>(DeathMatchConfig::DoorDrop::Random);
    } else if (lowerCaseName == DD_BOTH) {
        return std::optional<DeathMatchConfig::DoorDrop>(DeathMatchConfig::DoorDrop::Both);
    } else if (lowerCaseName == DD_NEVER) {
        return std::optional<DeathMatchConfig::DoorDrop>(DeathMatchConfig::DoorDrop::Never);
    } else if (lowerCaseName == DD_ALWAYS_OPEN) {
        return std::optional<DeathMatchConfig::DoorDrop>(DeathMatchConfig::DoorDrop::AlwaysOpen);
    } else if (lowerCaseName == DD_PLAYER_ONE) {
        return std::optional<DeathMatchConfig::DoorDrop>(DeathMatchConfig::DoorDrop::PlayerOne);
    } else if (lowerCaseName == DD_PLAYER_TWO) {
        return std::optional<DeathMatchConfig::DoorDrop>(DeathMatchConfig::DoorDrop::PlayerTwo);
    }else {
        return std::optional<DeathMatchConfig::DoorDrop>();
    }
}

inline constexpr const char* toSettingsString(DeathMatchConfig::DoorDrop dd) {
    switch(dd) {
    case DeathMatchConfig::DoorDrop::Random:
        return DD_RANDOM;
    case DeathMatchConfig::DoorDrop::Both:
        return DD_BOTH;
    case DeathMatchConfig::DoorDrop::Never:
        return DD_NEVER;
    case DeathMatchConfig::DoorDrop::AlwaysOpen:
        return DD_ALWAYS_OPEN;
    case DeathMatchConfig::DoorDrop::PlayerOne:
        return DD_PLAYER_ONE;
    case DeathMatchConfig::DoorDrop::PlayerTwo:
        return DD_PLAYER_TWO;
    }
}

#endif // DEATHMATCHCONFIG_H
