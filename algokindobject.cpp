#include "algokindobject.h"

static constexpr const char* BLINK_ALGO_NAME  = "blink";
static constexpr const char* BREATH_ALGO_NAME = "breath";
static constexpr const char* CONTDOWN_ALGO_NAME = "countdown";
static constexpr const char* CYLON_ALGO_NAME = "cylon";
static constexpr const char* OFF_ALGO_NAME = "off";
static constexpr const char* RAMPUP_ALGO_NAME = "rampup";
static constexpr const char* SOLID_ALGO_NAME = "solid";

const char* AlgoKindObject::getName(AlgoKind algo) {
    switch(algo) {
    case AlgoKind::Blink:
        return BLINK_ALGO_NAME;
    case AlgoKind::Breath:
        return BREATH_ALGO_NAME;
    case AlgoKind::CountDown:
        return CONTDOWN_ALGO_NAME;
    case AlgoKind::Cylon:
        return CYLON_ALGO_NAME;
    case AlgoKind::Off:
        return OFF_ALGO_NAME;
    case AlgoKind::RampUp:
        return RAMPUP_ALGO_NAME;
    case AlgoKind::Solid:
        return SOLID_ALGO_NAME;
    }
    return OFF_ALGO_NAME;
}

auto AlgoKindObject::fromName(QString const& name) -> std::optional<AlgoKind> {
    auto lcaseName = name.toLower();
    if(lcaseName == BLINK_ALGO_NAME) {
        return AlgoKind::Blink;
    }
    if(lcaseName == BREATH_ALGO_NAME) {
        return AlgoKind::Breath;
    }
    if(lcaseName == CONTDOWN_ALGO_NAME) {
        return AlgoKind::CountDown;
    }
    if(lcaseName == CYLON_ALGO_NAME) {
        return AlgoKind::Cylon;
    }
    if(lcaseName == OFF_ALGO_NAME) {
        return AlgoKind::Off;
    }
    if(lcaseName == RAMPUP_ALGO_NAME) {
        return AlgoKind::RampUp;
    }
    if(lcaseName == SOLID_ALGO_NAME) {
        return AlgoKind::Solid;
    }
    return std::optional<AlgoKind>();
}


static constexpr const char* BLINK_DISPLAY_NAME  = "Blink";
static constexpr const char* BREATH_DISPLAY_NAME = "Breath";
static constexpr const char* CONTDOWN_DISPLAY_NAME = "Count Down";
static constexpr const char* CYLON_DISPLAY_NAME = "Cylon";
static constexpr const char* OFF_DISPLAY_NAME = "Off";
static constexpr const char* RAMPUP_DISPLAY_NAME = "Ramp Up";
static constexpr const char* SOLID_DISPLAY_NAME = "Solid";

const char* AlgoKindObject::getDisplayName(AlgoKind algo) {
    switch(algo) {

    case AlgoKind::Off:
        return OFF_DISPLAY_NAME;
    case AlgoKind::Blink:
        return BLINK_DISPLAY_NAME;
    case AlgoKind::Breath:
        return BREATH_DISPLAY_NAME;
    case AlgoKind::CountDown:
        return CONTDOWN_DISPLAY_NAME;
    case AlgoKind::Cylon:
        return CYLON_DISPLAY_NAME;
    case AlgoKind::RampUp:
        return RAMPUP_DISPLAY_NAME;
    case AlgoKind::Solid:
        return SOLID_DISPLAY_NAME;
    }
    return BLINK_DISPLAY_NAME;
}

auto AlgoKindObject::fromDisplayName(QString const& name) -> AlgoKind {
    if (name == BLINK_DISPLAY_NAME) {
        return AlgoKind::Blink;
    }
    if (name == BREATH_DISPLAY_NAME) {
        return AlgoKind::Breath;
    }
    if (name == CONTDOWN_DISPLAY_NAME) {
        return AlgoKind::CountDown;
    }
    if (name == CYLON_DISPLAY_NAME) {
        return AlgoKind::Cylon;
    }
    if (name == OFF_DISPLAY_NAME) {
        return AlgoKind::Off;
    }
    if (name == RAMPUP_DISPLAY_NAME) {
        return AlgoKind::RampUp;
    }
    if (name == SOLID_DISPLAY_NAME) {
        return AlgoKind::Solid;
    }
    return AlgoKind::Off;
}

AlgoKindObject::AlgoKindObject(AlgoKind valueAndDefault, QString const& settingsKey, QObject *parent)
    : QObject{parent}
    , m_value(valueAndDefault)
    , m_default(valueAndDefault)
    , m_settingsKey(settingsKey)
{

}


auto AlgoKindObject::value() const -> AlgoKind{
    return m_value;
}

QString const& AlgoKindObject::settingsKey() const {
    return m_settingsKey;
}

auto AlgoKindObject::defaultValue() const -> AlgoKind {
    return m_default;
}

void AlgoKindObject::setValue(AlgoKind value) {
    if (m_value != value) {
        m_value = value;
        emit valueChanged(m_value);
    }
}

void AlgoKindObject::attachSettings(QSettings *settings) {
    auto defaultValueName = getName(m_default);
    auto loadedSetting = settings->value(m_settingsKey, defaultValueName).value<QString>();
    auto loadedAlgoKind = fromName(loadedSetting);
    AlgoKind curve;
    if(!loadedAlgoKind.has_value()) {
        qDebug() << "Failed to load value from file for:"
                 << m_settingsKey << "using default value"
                 << getName(m_default)
                 << "instead";
        curve = m_default;
    } else {
        curve = loadedAlgoKind.value();
    }
    connect(this, &AlgoKindObject::valueChanged,
            [=](AlgoKind newValue) {
                qDebug() << "Updating " << m_settingsKey << ": " << getName(newValue);
                settings->setValue(m_settingsKey, getName(newValue));
                settings->sync();
            });

    // Updating local values
    setValue(curve);
    // Always write the setting back.
    settings->setValue(m_settingsKey, getName(m_value));
}
