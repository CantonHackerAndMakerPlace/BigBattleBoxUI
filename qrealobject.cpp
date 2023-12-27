#include "qrealobject.h"

QRealObject::QRealObject(qreal valueAndDefault, QString const& settingsKey, QObject *parent)
    : QObject{parent}
    , m_value(valueAndDefault)
    , m_default(valueAndDefault)
    , m_settingsKey(settingsKey)
{ }


qreal QRealObject::value() const {
    return m_value;
}

QString const& QRealObject::settingsKey() const {
    return m_settingsKey;
}

qreal QRealObject::defaultValue() const {
    return m_default;
}

void QRealObject::setValue(qreal value) {
    if (m_value != value) {
        m_value = value;
        emit valueChanged(m_value);
    }
}

void QRealObject::attachSettings(QSettings *settings) {
    auto loadedSetting = settings->value(m_settingsKey, m_default).value<qreal>();
    connect(this, &QRealObject::valueChanged,
            [=](qreal newValue) {
                qDebug() << "Updating " << m_settingsKey << ": " << newValue;
                settings->setValue(m_settingsKey, newValue);
                settings->sync();
            });

    // Updating local values
    setValue(loadedSetting);
    // Always write the setting back.
    settings->setValue(m_settingsKey, m_value);
}
