#ifndef DEFAULTRESTORABLE_H
#define DEFAULTRESTORABLE_H

#include <QObject>

template<typename T>
class DefaultRestorable : public QObject
{
    Q_OBJECT

public:
    /// Sets the current and previous value to initialValue.
    explicit DefaultRestorable(T const& initalValue, T const& defaultValue, QObject *parent = nullptr);

    /// Returns the current value.
    T const& value();

    /// Returns the previous value that the value can be
    /// restored to.
    T const& previousValue();

    /// Returns the default value.
    T const& defaultValue();
public slots:

    /// Restores value to the previous value
    void restorePreviousValue();

    /// Sets the current value to the previous and the current to the
    /// default value.
    void restoreDefaultValue();

    /// Save the current value into previous and set the current
    /// value to the provided.
    void setValue(T const& value);
signals:
    void valueChanged(T value);
private:
    T m_defaultValue;
    T m_cur;
    T m_prev;
};

#endif // DEFAULTRESTORABLE_H
