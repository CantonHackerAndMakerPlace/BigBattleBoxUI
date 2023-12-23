#include "colorobject.h"

ColorObject::ColorObject(QColor valueAndDefault,
                         QString const& settingsKey,
                         QObject *parent)
    : QObject{parent}
    , m_value(valueAndDefault)
    , m_default(valueAndDefault)
    , m_settingsKey(settingsKey)
{ }

QColor ColorObject::value() const{
    return m_value;
}

QString const& ColorObject::settingsKey() const {
    return m_settingsKey;
}

QColor ColorObject::defaultValue() const {
    return m_default;
}

void ColorObject::setValue(QColor value) {
    if (m_value != value) {
        m_value = value;
        emit valueChanged(m_value);
    }
}

void ColorObject::attachSettings(QSettings *settings) {
    auto loadedSetting = settings->value(m_settingsKey, m_default).value<QColor>();
    connect(this, &ColorObject::valueChanged,
            [=](QColor newValue) {
                qDebug() << "Updating " << m_settingsKey << ": " << newValue;
                settings->setValue(m_settingsKey, newValue);
                settings->sync();
            });

    // Updating local values
    setValue(loadedSetting);
    // Always write the setting back.
    settings->setValue(m_settingsKey, m_value);
}
