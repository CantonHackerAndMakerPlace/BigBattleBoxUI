#ifndef INTERPOLATIONCURVEOBJECT_H
#define INTERPOLATIONCURVEOBJECT_H

#include <QObject>
#include <QSettings>
#include "app_state/led/interpolation.h"

class InterpolationCurveObject : public QObject
{
    Q_OBJECT
public:
    explicit InterpolationCurveObject(Interpolation::Curve valueAndDefault,
                                      QString const& settingsKey,
                                      QObject *parent = nullptr);
    ~InterpolationCurveObject() = default;

    /// Returns the integer value.
    Interpolation::Curve value() const;

    /// Returns the associated settings key.
    QString const& settingsKey() const;

    /// Returns the default value associated with the
    /// current instance.
    Interpolation::Curve defaultValue() const;

    /// Implicit conversion operator.
    inline operator Interpolation::Curve() const {
        return this->value();
    }
public slots:
    /// Sets the current value.
    void setValue(Interpolation::Curve value);

    /// Registers the settings to the changed value setting so
    /// it's updated when the value changes.
    void attachSettings(QSettings *settings);

signals:
    void valueChanged(Interpolation::Curve newValue);
private:
    Interpolation::Curve m_value;
    Interpolation::Curve m_default;
    QString m_settingsKey;
};

#endif // INTERPOLATIONCURVEOBJECT_H
