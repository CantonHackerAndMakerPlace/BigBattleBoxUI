#ifndef INTEGEROBJECT_H
#define INTEGEROBJECT_H
#include <QObject>
#include <QSettings>

/// This is a integer wrapping class that provides the signals and slots
/// and some additional metadata like the default value of the instance
/// and the settings key.
class IntegerObject : public QObject
{
    Q_OBJECT
public:
    /// The valueAndDefault sets the default value and the
    /// current value to the same value because the other value
    /// is set after construction
    explicit IntegerObject(int valueAndDefault, QString const& settingsKey, QObject *parent = nullptr);

    /// Returns the integer value.
    int value() const;

    /// Returns the associated settings key.
    QString const& settingsKey() const;

    /// Returns the default value associated with the
    /// current instance.
    int defaultValue() const;
public slots:
    /// Sets the current value.
    void setValue(int value);

    /// Registers the settings to the changed value setting so
    /// it's updated when the value changes.
    void attachSettings(QSettings *settings);

signals:
    void valueChanged(int newValue);
private:
    int m_value;
    int m_default;
    QString m_settingsKey;
};

#endif // INTEGEROBJECT_H
