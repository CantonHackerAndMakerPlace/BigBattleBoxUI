#ifndef COLOROBJECT_H
#define COLOROBJECT_H
#include <QObject>
#include <QSettings>
#include <QColor>

class ColorObject : public QObject
{
    Q_OBJECT
public:
    explicit ColorObject(QColor valueAndDefault,
                         QString const& settingsKey,
                         QObject *parent = nullptr);
    ~ColorObject() = default;

    /// Returns the color value.
    QColor value() const;

    /// Returns the associated settings key.
    QString const& settingsKey() const;

    /// Returns the default value associated with the
    /// current instance.
    QColor defaultValue() const;

    /// Implicit conversion operator.
    inline operator QColor() const {
        return this->value();
    }
public slots:
    /// Sets the current value.
    void setValue(QColor value);

    /// Registers the settings to the changed value setting so
    /// it's updated when the value changes.
    void attachSettings(QSettings *settings);

signals:
    void valueChanged(QColor newValue);
private:
    QColor m_value;
    QColor m_default;
    QString m_settingsKey;
signals:

};

#endif // COLOROBJECT_H
