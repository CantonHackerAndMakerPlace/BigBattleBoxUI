#include "booleanobject.h"

BooleanObject::BooleanObject(bool valueAndDefault, QString const& settingsKey, QObject *parent)
    : QObject{parent}
    , m_value(valueAndDefault)
    , m_default(valueAndDefault)
    , m_settingsKey(settingsKey)
{ }


bool BooleanObject::value() const {
    return m_value;
}

QString const& BooleanObject::settingsKey() const {
    return m_settingsKey;
}

bool BooleanObject::defaultValue() const {
    return m_default;
}

void BooleanObject::setValue(bool value) {
    if (m_value != value) {
        m_value = value;
        emit valueChanged(m_value);
    }
}

void BooleanObject::attachSettings(QSettings *settings) {
    auto loadedSetting = settings->value(m_settingsKey, m_default).value<bool>();
    connect(this, &BooleanObject::valueChanged,
            [=](bool newValue) {
                qDebug() << "Updating " << m_settingsKey << ": " << newValue;
                settings->setValue(m_settingsKey, newValue);
                settings->sync();
            });

    // Updating local values
    setValue(loadedSetting);
    // Always write the setting back.
    settings->setValue(m_settingsKey, m_value);
}
