#ifndef UNIFICATIONKINDOBJECT_H
#define UNIFICATIONKINDOBJECT_H

#include <QObject>
#include <QSettings>
#include <optional>

class UnificationKindObject : public QObject
{
    Q_OBJECT
    Q_ENUMS(Style)
public:

    enum class Kind {
        BothSame,
        Separate,
        SuperStrip,
    };

    static const char* getName(Kind s);
    static std::optional<Kind> fromName(QString const& s);
    static const char* getDisplayName(Kind s);
    static Kind fromDisplayName(QString const& s);

    explicit UnificationKindObject(Kind valueAndDefault, QString const& settingsKey, QObject *parent = nullptr);

    /// Returns the integer value.
    Kind value() const;

    /// Returns the associated settings key.
    QString const& settingsKey() const;

    /// Returns the default value associated with the
    /// current instance.
    Kind defaultValue() const;

    /// Implicit conversion operator.
    inline operator Kind() const {
        return this->value();
    }
public slots:
    /// Sets the current value.
    void setValue(Kind value);

    /// Registers the settings to the changed value setting so
    /// it's updated when the value changes.
    void attachSettings(QSettings *settings);

signals:
    void valueChanged(Kind newValue);
private:
    Kind m_value;
    Kind m_default;
    QString m_settingsKey;
signals:

};

#endif // UNIFICATIONKINDOBJECT_H
