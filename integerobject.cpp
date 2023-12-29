#include "integerobject.h"

IntegerObject::IntegerObject(int valueAndDefault, QString const& settingsKey, QObject *parent)
    : QObject{parent}
    , m_value(valueAndDefault)
    , m_default(valueAndDefault)
    , m_settingsKey(settingsKey)
{

}

int IntegerObject::value() const {
    return m_value;
}

QString const& IntegerObject::settingsKey() const {
    return m_settingsKey;
}

int IntegerObject::defaultValue() const {
    return m_default;
}

void IntegerObject::setValue(int value) {
    if (m_value != value) {
        m_value = value;
        emit valueChanged(m_value);
    }
}

void IntegerObject::attachSettings(QSettings *settings) {
    assert(settings);
    for(auto &x:settings->childKeys()) {
        qDebug() << "" << x.data();
    }
    auto loadedSetting = settings->value(m_settingsKey, m_default).value<int>();
    assert(this);
    connect(this, &IntegerObject::valueChanged,
        [=](int newValue) {
            qDebug() << "Updating " << m_settingsKey << ": " << newValue;
            settings->setValue(m_settingsKey, newValue);
            settings->sync();
        });

    // Updating local values
    setValue(loadedSetting);
    // Always write the setting back.
    settings->setValue(m_settingsKey, m_value);
}
