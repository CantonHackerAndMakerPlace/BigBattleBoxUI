#ifndef ALGOKINDOBJECT_H
#define ALGOKINDOBJECT_H

#include <QObject>
#include <QSettings>
#include <optional>

class AlgoKindObject : public QObject
{
    Q_OBJECT
    Q_ENUMS(AlgoKind)

public:
    // This type is associated with a specific kind of
    enum class AlgoKind {
        Off,
        Blink,
        Breath,
        CountDown,
        Cylon,
        RampUp,
        Solid,
    };

    static const char* getName(AlgoKind aglo);
    static std::optional<AlgoKind> fromName(QString const& name);

    static const char* getDisplayName(AlgoKind algo);
    static AlgoKind fromDisplayName(QString const& name);

    explicit AlgoKindObject(AlgoKind valueAndDefault, QString const& settingsKey, QObject *parent = nullptr);

    /// Returns the current selected algorithm value.
    AlgoKind value() const;

    /// Returns the associated settings key.
    QString const& settingsKey() const;

    /// Returns the default value associated with the
    /// current instance.
    AlgoKind defaultValue() const;

    /// Implicit conversion operator.
    inline operator AlgoKind() const {
        return this->value();
    }
public slots:
    /// Sets the current value.
    void setValue(AlgoKind value);

    /// Registers the settings to the changed value setting so
    /// it's updated when the value changes.
    void attachSettings(QSettings *settings);

signals:
    void valueChanged(AlgoKind newValue);
private:
    AlgoKind m_value;
    AlgoKind m_default;
    QString m_settingsKey;

};

#endif // ALGOKINDOBJECT_H
