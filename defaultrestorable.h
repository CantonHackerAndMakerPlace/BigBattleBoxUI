#ifndef DEFAULTRESTORABLE_H
#define DEFAULTRESTORABLE_H

#include <QObject>
#include <QColor>
#include "app_state/led/interpolation.h"
#include "integerobject.h"
#include "colorobject.h"
#include "qrealobject.h"
#include "booleanobject.h"
#include "interpolationcurveobject.h"
#include "unificationkindobject.h"
#include "algokindobject.h"

class DefaultRestorableInt : public QObject
{
    Q_OBJECT

public:
    /// Sets the current and previous value to initialValue.
    explicit DefaultRestorableInt(int defaultValue, QObject *parent = nullptr);

    /// Returns the current value.
    int value() const;

    /// Returns the previous value that the value can be
    /// restored to.
    int previousValue() const;

    /// Returns the default value.
    int defaultValue() const;

    /// Returns true if the previous and current value are different.
    bool hasChange() const;

    DefaultRestorableInt& operator=(IntegerObject const& other);

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

    /// Sets the default value asscoiated with this object.
    void setDefaultValue(int value);

    /// Save the current value into previous and set the current
    /// value to the provided.
    void setValue(int value);
signals:
    void valueChanged(int value);
    void defaultValueChanged(int value);
private:
    int m_defaultValue;
    int m_cur;
    int m_prev;
};

class DefaultRestorableCurve: public QObject
{
    Q_OBJECT

public:
    /// Sets the current and previous value to initialValue.
    explicit DefaultRestorableCurve(Interpolation::Curve defaultValue, QObject *parent = nullptr);

    /// Returns the current value.
    Interpolation::Curve value() const;

    /// Returns the previous value that the value can be
    /// restored to.
    Interpolation::Curve previousValue() const;

    /// Returns the default value.
    Interpolation::Curve defaultValue() const;

    /// Returns true if the previous and current value are different.
    bool hasChange() const;

    DefaultRestorableCurve& operator=(InterpolationCurveObject const& other);


public slots:

    /// Save the current value and saves it as the previous value.
    void saveValue();

    /// Set the previous value.
    void setPreviousValue(Interpolation::Curve previousValue);

    /// Sets current and previous value.
    void setCurrentAndPreviousValue(Interpolation::Curve value);

    /// Restores value to the previous value
    void restorePreviousValue();

    /// Sets the current value to the previous and the current to the
    /// default value.
    void restoreDefaultValue();

    /// Save the current value into previous and set the current
    /// value to the provided.
    void setValue(Interpolation::Curve value);

    /// Sets the default value asscoiated with this object.
    void setDefaultValue(Interpolation::Curve value);

signals:
    void valueChanged(Interpolation::Curve value);
    void defaultValueChanged(Interpolation::Curve value);
private:
    Interpolation::Curve m_defaultValue;
    Interpolation::Curve m_cur;
    Interpolation::Curve m_prev;
};


class DefaultRestorableBool: public QObject
{
    Q_OBJECT

public:
    /// Sets the current and previous value to initialValue.
    explicit DefaultRestorableBool(bool defaultValue, QObject *parent = nullptr);

    /// Returns the current value.
    bool value() const;

    /// Returns the previous value that the value can be
    /// restored to.
    bool previousValue() const;

    /// Returns the default value.
    bool defaultValue() const;

    /// Returns true if the previous and current value are different.
    bool hasChange() const;

    DefaultRestorableBool& operator=(BooleanObject const& other);


public slots:

    /// Save the current value and saves it as the previous value.
    void saveValue();

    /// Set the previous value.
    void setPreviousValue(bool previousValue);

    /// Sets current and previous value.
    void setCurrentAndPreviousValue(bool value);

    /// Restores value to the previous value
    void restorePreviousValue();

    /// Sets the current value to the previous and the current to the
    /// default value.
    void restoreDefaultValue();

    /// Save the current value into previous and set the current
    /// value to the provided.
    void setValue(bool value);

    /// Sets the default value asscoiated with this object.
    void setDefaultValue(bool value);
signals:
    void valueChanged(bool value);
    void defaultValueChanged(bool value);
private:
    bool m_defaultValue;
    bool m_cur;
    bool m_prev;
};

class DefaultRestorableString: public QObject
{
    Q_OBJECT

public:
    /// Sets the current and previous value to initialValue.
    explicit DefaultRestorableString(QString const& defaultValue, QObject *parent = nullptr);

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

    /// Sets the default value asscoiated with this object.
    void setDefaultValue(QString const& value);
signals:
    void valueChanged(QString const& value);
    void defaultValueChanged(QString const& value);
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
    explicit DefaultRestorableQReal(qreal defaultValue, QObject *parent = nullptr);

    /// Returns the current value.
    qreal value() const;

    /// Returns the previous value that the value can be
    /// restored to.
    qreal previousValue() const;

    /// Returns the default value.
    qreal defaultValue() const;

    /// Returns true if the previous and current value are different.
    bool hasChange() const;

    DefaultRestorableQReal& operator=(QRealObject const& other);
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

    /// Sets the default value asscoiated with this object.
    void setDefaultValue(qreal value);
signals:
    void valueChanged(qreal value);
    void defaultValueChanged(qreal value);
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
    explicit DefaultRestorableQColor(QColor defaultValue, QObject *parent = nullptr);

    /// Returns the current value.
    QColor const& value() const;

    /// Returns the previous value that the value can be
    /// restored to.
    QColor const& previousValue() const;

    /// Returns the default value.
    QColor const& defaultValue() const;

    /// Returns true if the previous and current value are different.
    bool hasChange() const;

    DefaultRestorableQColor& operator=(ColorObject const& other);
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

    /// Sets the default value asscoiated with this object.
    void setDefaultValue(QColor value);
signals:
    void valueChanged(QColor const& value);
    void defaultValueChanged(QColor const &value);
private:
    QColor m_defaultValue;
    QColor m_cur;
    QColor m_prev;
};

class DefaultRestorableUnificationKind : public QObject
{
    Q_OBJECT

public:
    using Kind = UnificationKindObject::Kind;

    /// Sets the current and previous value to initialValue.
    explicit DefaultRestorableUnificationKind(Kind defaultValue, QObject *parent = nullptr);

    /// Returns the current value.
    Kind value() const;

    /// Returns the previous value that the value can be
    /// restored to.
    Kind previousValue() const;

    /// Returns the default value.
    Kind defaultValue() const;

    /// Returns true if the previous and current value are different.
    bool hasChange() const;

    DefaultRestorableUnificationKind& operator=(UnificationKindObject const& other);
public slots:
    /// Save the current value and saves it as the previous value.
    void saveValue();

    /// Set the previous value.
    void setPreviousValue(Kind previousValue);

    /// Sets current and previous value.
    void setCurrentAndPreviousValue(Kind value);

    /// Restores value to the previous value
    void restorePreviousValue();

    /// Sets the current value to the previous and the current to the
    /// default value.
    void restoreDefaultValue();

    /// Save the current value into previous and set the current
    /// value to the provided.
    void setValue(Kind value);

    /// Sets the default value asscoiated with this object.
    void setDefaultValue(Kind value);
signals:
    void valueChanged(Kind value);
    void defaultValueChanged(Kind value);
private:
    Kind m_defaultValue;
    Kind m_cur;
    Kind m_prev;
};


class DefaultRestorableAlgoKind : public QObject
{
    Q_OBJECT

public:
    using AlgoKind = AlgoKindObject::AlgoKind;

    /// Sets the current and previous value to initialValue.
    explicit DefaultRestorableAlgoKind(AlgoKind defaultValue, QObject *parent = nullptr);

    /// Returns the current value.
    AlgoKind value() const;

    /// Returns the previous value that the value can be
    /// restored to.
    AlgoKind previousValue() const;

    /// Returns the default value.
    AlgoKind defaultValue() const;

    /// Returns true if the previous and current value are different.
    bool hasChange() const;

    DefaultRestorableAlgoKind& operator=(AlgoKindObject const& other);
public slots:
    /// Save the current value and saves it as the previous value.
    void saveValue();

    /// Set the previous value.
    void setPreviousValue(AlgoKind previousValue);

    /// Sets current and previous value.
    void setCurrentAndPreviousValue(AlgoKind value);

    /// Restores value to the previous value
    void restorePreviousValue();

    /// Sets the current value to the previous and the current to the
    /// default value.
    void restoreDefaultValue();

    /// Save the current value into previous and set the current
    /// value to the provided.
    void setValue(AlgoKind value);

    /// Sets the default value asscoiated with this object.
    void setDefaultValue(AlgoKind value);
signals:
    void valueChanged(AlgoKind value);
    void defaultValueChanged(AlgoKind value);
private:
    AlgoKind m_defaultValue;
    AlgoKind m_cur;
    AlgoKind m_prev;
};

#endif // DEFAULTRESTORABLE_H
