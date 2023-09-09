#ifndef DEFAULTRESTORABLE_H
#define DEFAULTRESTORABLE_H

#include <QObject>
#include <QColor>

class DefaultRestorableInt : public QObject
{
    Q_OBJECT

public:
    /// Sets the current and previous value to initialValue.
    explicit DefaultRestorableInt(int initalValue, int defaultValue, QObject *parent = nullptr);

    /// Returns the current value.
    int value() const;

    /// Returns the previous value that the value can be
    /// restored to.
    int previousValue() const;

    /// Returns the default value.
    int defaultValue() const;

    /// Returns true if the previous and current value are different.
    bool hasChange() const;

public slots:

    /// Save the current value and saves it as the previous value.
    void saveValue();

    /// Set the previous value.
    void setPreviousValue(int previousValue);

    /// Sets current and previous value.
    void setCurrentAndPreviousValue(int value);

    /// Restores value to the previous value
    void restorePreviousValue();

    /// Sets the current value to the previous and the current to the
    /// default value.
    void restoreDefaultValue();

    /// Save the current value into previous and set the current
    /// value to the provided.
    void setValue(int value);
signals:
    void valueChanged(int value);
private:
    int m_defaultValue;
    int m_cur;
    int m_prev;
};


class DefaultRestorableString: public QObject
{
    Q_OBJECT

public:
    /// Sets the current and previous value to initialValue.
    explicit DefaultRestorableString(QString const& initalValue, QString const& defaultValue, QObject *parent = nullptr);

    /// Returns the current value.
    QString const& value() const;

    /// Returns the previous value that the value can be
    /// restored to.
    QString const& previousValue() const;

    /// Returns the default value.
    QString const& defaultValue() const;

    /// Returns true if the previous and current value are different.
    bool hasChange() const;
public slots:
    /// Save the current value and saves it as the previous value.
    void saveValue();

    /// Set the previous value.
    void setPreviousValue(QString const& previousValue);

    /// Sets current and previous value.
    void setCurrentAndPreviousValue(QString const& value);

    /// Restores value to the previous value
    void restorePreviousValue();

    /// Sets the current value to the previous and the current to the
    /// default value.
    void restoreDefaultValue();

    /// Save the current value into previous and set the current
    /// value to the provided.
    void setValue(QString const& value);
signals:
    void valueChanged(QString const& value);
private:
    QString m_defaultValue;
    QString m_cur;
    QString m_prev;
};


class DefaultRestorableQReal: public QObject
{
    Q_OBJECT

public:
    /// Sets the current and previous value to initialValue.
    explicit DefaultRestorableQReal(qreal initalValue, qreal defaultValue, QObject *parent = nullptr);

    /// Returns the current value.
    qreal value() const;

    /// Returns the previous value that the value can be
    /// restored to.
    qreal previousValue() const;

    /// Returns the default value.
    qreal defaultValue() const;

    /// Returns true if the previous and current value are different.
    bool hasChange() const;
public slots:
    /// Save the current value and saves it as the previous value.
    void saveValue();

    /// Set the previous value.
    void setPreviousValue(qreal previousValue);

    /// Sets current and previous value.
    void setCurrentAndPreviousValue(qreal value);

    /// Restores value to the previous value
    void restorePreviousValue();

    /// Sets the current value to the previous and the current to the
    /// default value.
    void restoreDefaultValue();

    /// Save the current value into previous and set the current
    /// value to the provided.
    void setValue(qreal value);
signals:
    void valueChanged(qreal value);
private:
    qreal m_defaultValue;
    qreal m_cur;
    qreal m_prev;
};


class DefaultRestorableQColor: public QObject
{
    Q_OBJECT

public:
    /// Sets the current and previous value to initialValue.
    explicit DefaultRestorableQColor(QColor initalValue, QColor defaultValue, QObject *parent = nullptr);

    /// Returns the current value.
    QColor const& value() const;

    /// Returns the previous value that the value can be
    /// restored to.
    QColor const& previousValue() const;

    /// Returns the default value.
    QColor const& defaultValue() const;

    /// Returns true if the previous and current value are different.
    bool hasChange() const;
public slots:
    /// Save the current value and saves it as the previous value.
    void saveValue();

    /// Set the previous value.
    void setPreviousValue(QColor previousValue);

    /// Sets current and previous value.
    void setCurrentAndPreviousValue(QColor value);

    /// Restores value to the previous value
    void restorePreviousValue();

    /// Sets the current value to the previous and the current to the
    /// default value.
    void restoreDefaultValue();

    /// Save the current value into previous and set the current
    /// value to the provided.
    void setValue(QColor const& value);
signals:
    void valueChanged(QColor const& value);
private:
    QColor m_defaultValue;
    QColor m_cur;
    QColor m_prev;
};

#endif // DEFAULTRESTORABLE_H
