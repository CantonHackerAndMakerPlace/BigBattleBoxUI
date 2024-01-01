#include "unificationkindobject.h"

static constexpr const char* BOTHSAME_NAME = "bothsame";
static constexpr const char* SEPARATE_NAME = "separate";
static constexpr const char* SUPERSTRIP_NAME = "superstrip";

const char* UnificationKindObject::getName(Kind s) {
    switch(s) {
    case Kind::BothSame:
        return BOTHSAME_NAME;
    case Kind::Separate:
        return SEPARATE_NAME;
    case Kind::SuperStrip:
        return SUPERSTRIP_NAME;
    }
    return BOTHSAME_NAME;
}

auto UnificationKindObject::fromName(QString const& s) -> std::optional<Kind> {
    auto name = s.toLower();
    if (name == BOTHSAME_NAME) {
        return Kind::BothSame;
    }
    if (name == SEPARATE_NAME) {
        return Kind::Separate;
    }
    if (name == SUPERSTRIP_NAME) {
        return Kind::SuperStrip;
    }
    return std::optional<Kind>();
}

static constexpr const char* BOTHSAME_DISPLAY_NAME = "Both LED strips are the same";
static constexpr const char* SEPARATE_DISPLAY_NAME = "Using individual settings";
static constexpr const char* SUPERSTRIP_DISPLAY_NAME = "Treat as one large strip";

const char* UnificationKindObject::getDisplayName(Kind s) {
    switch(s) {
        
    case Kind::BothSame:
        return BOTHSAME_DISPLAY_NAME;
    case Kind::Separate:
        return SEPARATE_DISPLAY_NAME;
    case Kind::SuperStrip:
        return SUPERSTRIP_DISPLAY_NAME;
    }
    return BOTHSAME_DISPLAY_NAME;
}

auto UnificationKindObject::fromDisplayName(QString const& s) -> Kind {
    if(s == BOTHSAME_DISPLAY_NAME) {
        return Kind::BothSame;
    }
    if(s == SEPARATE_DISPLAY_NAME) {
        return Kind::Separate;
    }
    if(s == SUPERSTRIP_DISPLAY_NAME) {
        return Kind::SuperStrip;
    }
    // Default behavior in the event that we don't recognize the display name.
    return Kind::SuperStrip;
}

UnificationKindObject::UnificationKindObject(Kind valueAndDefault, QString const& settingsKey, QObject *parent)
    : QObject{parent}
    , m_value(valueAndDefault)
    , m_default(valueAndDefault)
    , m_settingsKey(settingsKey)
{

}

auto UnificationKindObject::value() const -> Kind {
    return m_value;
}

QString const& UnificationKindObject::settingsKey() const {
    return m_settingsKey;
}

auto UnificationKindObject::defaultValue() const -> Kind {
    return m_default;
}

void UnificationKindObject::setValue(Kind value) {
    if (m_value != value) {
        m_value = value;
        emit valueChanged(m_value);
    }
}

void UnificationKindObject::attachSettings(QSettings *settings) {
    auto defaultValueName = getName(m_default);
    auto loadedSetting = settings->value(m_settingsKey, defaultValueName).value<QString>();
    auto loadedCurve = fromName(loadedSetting);
    Kind style;
    if(!loadedCurve.has_value()) {
        qDebug() << "Failed to load value from file for:"
                 << m_settingsKey << "using default value"
                 << getName(m_default)
                 << "instead";
        style = m_default;
    } else {
        style = loadedCurve.value();
    }
    connect(this, &UnificationKindObject::valueChanged,
            [=](Kind newValue) {
                qDebug() << "Updating " << m_settingsKey << ": " << getName(newValue);
                settings->setValue(m_settingsKey, getName(newValue));
                settings->sync();
            });

    // Updating local values
    setValue(style);
    // Always write the setting back.
    settings->setValue(m_settingsKey, getName(m_value));
}
