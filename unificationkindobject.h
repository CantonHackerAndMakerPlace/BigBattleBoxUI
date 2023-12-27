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

    enum class Style {
        BothSame,
        Separate,
        SuperStrip,
    };

    static const char* getName(Style s);
    static std::optional<Style> fromName(QString const& s);
    static const char* getDisplayName(Style s);
    static Style fromDisplayName(QString const& s);

    explicit UnificationKindObject(Style valueAndDefault, QString const& settingsKey, QObject *parent = nullptr);

    /// Returns the integer value.
    Style value() const;

    /// Returns the associated settings key.
    QString const& settingsKey() const;

    /// Returns the default value associated with the
    /// current instance.
    Style defaultValue() const;

    /// Implicit conversion operator.
    inline operator Style() const {
        return this->value();
    }
public slots:
    /// Sets the current value.
    void setValue(Style value);

    /// Registers the settings to the changed value setting so
    /// it's updated when the value changes.
    void attachSettings(QSettings *settings);

signals:
    void valueChanged(Style newValue);
private:
    Style m_value;
    Style m_default;
    QString m_settingsKey;
signals:

};

#endif // UNIFICATIONKINDOBJECT_H
