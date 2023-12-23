#include "interpolationcurveobject.h"

InterpolationCurveObject::InterpolationCurveObject(Interpolation::Curve valueAndDefault,
                                                   QString const& settingsKey,
                                                   QObject *parent)
    : QObject{parent}
    , m_value(valueAndDefault)
    , m_default(valueAndDefault)
    , m_settingsKey(settingsKey)
{ }

Interpolation::Curve InterpolationCurveObject::value() const {
    return m_value;
}

QString const& InterpolationCurveObject::settingsKey() const {
    return m_settingsKey;
}

Interpolation::Curve InterpolationCurveObject::defaultValue() const {
    return m_default;
}

void InterpolationCurveObject::setValue(Interpolation::Curve value) {
    if (m_value != value) {
        m_value = value;
        emit valueChanged(m_value);
    }
}

void InterpolationCurveObject::attachSettings(QSettings *settings) {
    auto defaultValueName = Interpolation::getName(m_default);
    auto loadedSetting = settings->value(m_settingsKey, defaultValueName).value<QString>();
    auto loadedCurve = Interpolation::getByName(loadedSetting);
    Interpolation::Curve curve;
    if(!loadedCurve.has_value()) {
        qDebug() << "Failed to load value from file for:"
                 << m_settingsKey << "using default value"
                 << Interpolation::getName(m_default)
                 << "instead";
        curve = m_default;
    } else {
        curve = loadedCurve.value();
    }
    connect(this, &InterpolationCurveObject::valueChanged,
            [=](Interpolation::Curve newValue) {
                qDebug() << "Updating " << m_settingsKey << ": " << Interpolation::getName(newValue);
                settings->setValue(m_settingsKey, Interpolation::getName(newValue));
                settings->sync();
            });

    // Updating local values
    setValue(curve);
    // Always write the setting back.
    settings->setValue(m_settingsKey, Interpolation::getName(m_value));
}

