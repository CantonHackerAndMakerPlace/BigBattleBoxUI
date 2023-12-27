#ifndef QREALOBJECT_H
#define QREALOBJECT_H
#include <QSettings>
#include <QObject>

class QRealObject : public QObject
{
    Q_OBJECT
public:
    explicit QRealObject(qreal valueAndDefault, QString const& settingsKey, QObject *parent = nullptr);

    /// Returns the bool value.
    qreal value() const;

    /// Returns the associated settings key.
    QString const& settingsKey() const;

    /// Returns the default value associated with the
    /// current instance.
    qreal defaultValue() const;

    /// Implicit conversion operator.
    inline operator qreal() const {
        return this->value();
    }
public slots:
    /// Sets the current value.
    void setValue(qreal value);

    /// Registers the settings to the changed value setting so
    /// it's updated when the value changes.
    void attachSettings(QSettings *settings);
signals:
    void valueChanged(bool newValue);
private:
    qreal m_value;
    qreal m_default;
    QString m_settingsKey;
signals:

};

#endif // QREALOBJECT_H
