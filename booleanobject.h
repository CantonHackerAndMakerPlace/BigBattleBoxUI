#ifndef BOOLEANOBJECT_H
#define BOOLEANOBJECT_H
#include <QObject>
#include <QSettings>

class BooleanObject : public QObject
{
    Q_OBJECT
public:
    explicit BooleanObject(bool valueAndDefault, QString const& settingsKey, QObject *parent = nullptr);

    /// Returns the bool value.
    bool value() const;

    /// Returns the associated settings key.
    QString const& settingsKey() const;

    /// Returns the default value associated with the
    /// current instance.
    bool defaultValue() const;
public slots:
    /// Sets the current value.
    void setValue(bool value);

    /// Registers the settings to the changed value setting so
    /// it's updated when the value changes.
    void attachSettings(QSettings *settings);

signals:
    void valueChanged(bool newValue);
private:
    bool m_value;
    bool m_default;
    QString m_settingsKey;
};

#endif // BOOLEANOBJECT_H
