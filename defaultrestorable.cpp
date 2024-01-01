#include "defaultrestorable.h"


// DefaultRestorableInt
DefaultRestorableInt::DefaultRestorableInt(int defaultValue, QObject *parent)
    : m_defaultValue(defaultValue)
    , m_cur(defaultValue)
    , m_prev(defaultValue)
{ }

int DefaultRestorableInt::value() const {
    return m_cur;
}

int DefaultRestorableInt::previousValue() const {
    return m_prev;
}

int DefaultRestorableInt::defaultValue() const {
    return m_defaultValue;
}

bool DefaultRestorableInt::hasChange() const {
    return m_cur != m_prev;
}

void DefaultRestorableInt::saveValue() {
    m_prev = m_cur;
}

void DefaultRestorableInt::setPreviousValue(int previousValue) {
    m_prev = previousValue;
}

void DefaultRestorableInt::setCurrentAndPreviousValue(int value) {
    setPreviousValue(value);
    setValue(value);
}

void DefaultRestorableInt::restorePreviousValue() {
    if (m_prev != m_cur) {
        m_cur = m_prev;
        emit valueChanged(m_cur);
    }
}

void DefaultRestorableInt::restoreDefaultValue() {
    if (m_cur != m_defaultValue) {
        m_cur = m_defaultValue;
        emit valueChanged(m_cur);
    }
}

void DefaultRestorableInt::setValue(int value) {
    if (m_cur != value) {
        m_cur = value;
        emit valueChanged(m_cur);
    }
}

void DefaultRestorableInt::setDefaultValue(int value) {
    if (m_defaultValue != value) {
        m_defaultValue = value;
        emit defaultValueChanged(m_defaultValue);
    }
}

DefaultRestorableInt& DefaultRestorableInt::operator=(IntegerObject const& other) {
    setCurrentAndPreviousValue(other.value());
    return *this;
}


// DefaultRestorableCurve
DefaultRestorableCurve::DefaultRestorableCurve(Interpolation::Curve defaultValue, QObject *parent)
    : m_defaultValue(defaultValue)
    , m_cur(defaultValue)
    , m_prev(defaultValue)
{ }

Interpolation::Curve DefaultRestorableCurve::value() const {
    return m_cur;
}

Interpolation::Curve DefaultRestorableCurve::previousValue() const {
    return m_prev;
}

Interpolation::Curve DefaultRestorableCurve::defaultValue() const {
    return m_defaultValue;
}

bool DefaultRestorableCurve::hasChange() const {
    return m_cur != m_prev;
}

void DefaultRestorableCurve::saveValue() {
    m_prev = m_cur;
}

void DefaultRestorableCurve::setPreviousValue(Interpolation::Curve previousValue) {
    m_prev = previousValue;
}

void DefaultRestorableCurve::setCurrentAndPreviousValue(Interpolation::Curve value) {
    setPreviousValue(value);
    setValue(value);
}

void DefaultRestorableCurve::restorePreviousValue() {
    if (m_prev != m_cur) {
        m_cur = m_prev;
        emit valueChanged(m_cur);
    }
}

void DefaultRestorableCurve::restoreDefaultValue() {
    if (m_cur != m_defaultValue) {
        m_cur = m_defaultValue;
        emit valueChanged(m_cur);
    }
}

void DefaultRestorableCurve::setValue(Interpolation::Curve value) {
    if (m_cur != value) {
        m_cur = value;
        emit valueChanged(m_cur);
    }
}

void DefaultRestorableCurve::setDefaultValue(Interpolation::Curve value) {
    if (m_defaultValue != value) {
        m_defaultValue = value;
        emit defaultValueChanged(m_defaultValue);
    }
}

DefaultRestorableCurve& DefaultRestorableCurve::operator=(InterpolationCurveObject const& other) {
    setCurrentAndPreviousValue(other.value());
    return *this;
}

// DefaultRestorableBool
DefaultRestorableBool::DefaultRestorableBool(bool defaultValue, QObject *parent)
    : m_defaultValue(defaultValue)
    , m_cur(defaultValue)
    , m_prev(defaultValue)
{ }

bool DefaultRestorableBool::value() const {
    return m_cur;
}

bool DefaultRestorableBool::previousValue() const {
    return m_prev;
}

bool DefaultRestorableBool::defaultValue() const {
    return m_defaultValue;
}

bool DefaultRestorableBool::hasChange() const {
    return m_cur != m_prev;
}

void DefaultRestorableBool::saveValue() {
    m_prev = m_cur;
}

void DefaultRestorableBool::setPreviousValue(bool previousValue) {
    m_prev = previousValue;
}

void DefaultRestorableBool::setCurrentAndPreviousValue(bool value) {
    setPreviousValue(value);
    setValue(value);
}

void DefaultRestorableBool::restorePreviousValue() {
    if (m_prev != m_cur) {
        m_cur = m_prev;
        emit valueChanged(m_cur);
    }
}

void DefaultRestorableBool::restoreDefaultValue() {
    if (m_cur != m_defaultValue) {
        m_cur = m_defaultValue;
        emit valueChanged(m_cur);
    }
}

void DefaultRestorableBool::setValue(bool value) {
    if (m_cur != value) {
        m_cur = value;
        emit valueChanged(m_cur);
    }
}

void DefaultRestorableBool::setDefaultValue(bool value) {
    if (m_defaultValue != value) {
        m_defaultValue = value;
        emit defaultValueChanged(m_defaultValue);
    }
}

DefaultRestorableBool& DefaultRestorableBool::operator=(BooleanObject const& other) {
    setCurrentAndPreviousValue(other.value());
    return *this;
}

// DefaultRestorableString
DefaultRestorableString::DefaultRestorableString(QString const& defaultValue, QObject *parent)
    : m_defaultValue(defaultValue)
    , m_cur(defaultValue)
    , m_prev(defaultValue)
{ }

QString const& DefaultRestorableString::value() const {
    return m_cur;
}

QString const& DefaultRestorableString::previousValue() const {
    return m_prev;
}

QString const& DefaultRestorableString::defaultValue() const {
    return m_defaultValue;
}

bool DefaultRestorableString::hasChange() const {
    return m_cur != m_prev;
}

void DefaultRestorableString::saveValue() {
    m_prev = m_cur;
}

void DefaultRestorableString::setPreviousValue(QString const& previousValue) {
    m_prev = previousValue;
}

void DefaultRestorableString::setCurrentAndPreviousValue(QString const& value) {
    setPreviousValue(value);
    setValue(value);
}

void DefaultRestorableString::restorePreviousValue() {
    if (m_prev != m_cur) {
        m_cur = m_prev;
        emit valueChanged(m_cur);
    }
}

void DefaultRestorableString::restoreDefaultValue() {
    if (m_cur != m_defaultValue) {
        m_cur = m_defaultValue;
        emit valueChanged(m_cur);
    }
}

void DefaultRestorableString::setValue(QString const& value) {
    if (m_cur != value) {
        m_cur = value;
        emit valueChanged(m_cur);
    }
}

void DefaultRestorableString::setDefaultValue(QString const& value) {
    if (m_defaultValue != value) {
        m_defaultValue = value;
        emit defaultValueChanged(m_defaultValue);
    }
}

// DefaultRestorableQReal

DefaultRestorableQReal::DefaultRestorableQReal(qreal defaultValue, QObject *parent)
    : m_defaultValue(defaultValue)
    , m_cur(defaultValue)
    , m_prev(defaultValue)
{ }

qreal DefaultRestorableQReal::value() const {
    return m_cur;
}

qreal DefaultRestorableQReal::previousValue() const {
    return m_prev;
}

qreal DefaultRestorableQReal::defaultValue() const {
    return m_defaultValue;
}

bool DefaultRestorableQReal::hasChange() const {
    return m_cur != m_prev;
}

void DefaultRestorableQReal::setDefaultValue(qreal value) {
    if (m_defaultValue != value) {
        m_defaultValue = value;
        emit defaultValueChanged(m_defaultValue);
    }
}

DefaultRestorableQReal& DefaultRestorableQReal::operator=(QRealObject const& other) {
    setCurrentAndPreviousValue(other.value());
    return *this;
}

void DefaultRestorableQReal::saveValue() {
    m_prev = m_cur;
}

void DefaultRestorableQReal::setPreviousValue(qreal previousValue) {
    m_prev = previousValue;
}

void DefaultRestorableQReal::setCurrentAndPreviousValue(qreal value) {
    setPreviousValue(value);
    setValue(value);
}

void DefaultRestorableQReal::restorePreviousValue() {
    if (m_prev != m_cur) {
        m_cur = m_prev;
        emit valueChanged(m_cur);
    }
}

void DefaultRestorableQReal::restoreDefaultValue() {
    if (m_cur != m_defaultValue) {
        m_cur = m_defaultValue;
        emit valueChanged(m_cur);
    }
}

void DefaultRestorableQReal::setValue(qreal value) {
    if (m_cur != value) {
        m_cur = value;
        emit valueChanged(m_cur);
    }
}

// DefaultRestorableQColor
DefaultRestorableQColor::DefaultRestorableQColor(QColor defaultValue, QObject *parent)
    : m_defaultValue(defaultValue)
    , m_cur(defaultValue)
    , m_prev(defaultValue)
{ }

QColor const& DefaultRestorableQColor::value() const {
    return m_cur;
}

QColor const& DefaultRestorableQColor::previousValue() const {
    return m_prev;
}

QColor const& DefaultRestorableQColor::defaultValue() const {
    return m_defaultValue;
}

bool DefaultRestorableQColor::hasChange() const {
    return m_cur != m_prev;
}

void DefaultRestorableQColor::saveValue() {
    m_prev = m_cur;
}

void DefaultRestorableQColor::setPreviousValue(QColor previousValue) {
    m_prev = previousValue;
}

void DefaultRestorableQColor::setCurrentAndPreviousValue(QColor value) {
    setPreviousValue(value);
    setValue(value);
}

void DefaultRestorableQColor::restorePreviousValue() {
    if (m_prev != m_cur) {
        m_cur = m_prev;
        emit valueChanged(m_cur);
    }
}

void DefaultRestorableQColor::restoreDefaultValue() {
    if (m_cur != m_defaultValue) {
        m_cur = m_defaultValue;
        emit valueChanged(m_cur);
    }
}

void DefaultRestorableQColor::setValue(QColor const& value) {
    if (m_cur != value) {
        m_cur = value;
        emit valueChanged(m_cur);
    }
}

void DefaultRestorableQColor::setDefaultValue(QColor value) {
    if (m_defaultValue != value) {
        m_defaultValue = value;
        emit defaultValueChanged(m_defaultValue);
    }
}

DefaultRestorableQColor& DefaultRestorableQColor::operator=(ColorObject const& other) {
    setCurrentAndPreviousValue(other.value());
    return *this;
}

// DefaultRestorableUnificationKind
DefaultRestorableUnificationKind::DefaultRestorableUnificationKind(Kind defaultValue, QObject *parent)
    : m_defaultValue(defaultValue)
    , m_cur(defaultValue)
    , m_prev(defaultValue)
{ }

auto DefaultRestorableUnificationKind::value() const -> Kind {
    return m_cur;
}

auto DefaultRestorableUnificationKind::previousValue() const -> Kind {
    return m_prev;
}

auto DefaultRestorableUnificationKind::defaultValue() const -> Kind {
    return m_defaultValue;
}

bool DefaultRestorableUnificationKind::hasChange() const {
    return m_cur != m_prev;
}

void DefaultRestorableUnificationKind::saveValue() {
    m_prev = m_cur;
}

void DefaultRestorableUnificationKind::setPreviousValue(Kind previousValue) {
    m_prev = previousValue;
}

void DefaultRestorableUnificationKind::setCurrentAndPreviousValue(Kind value) {
    setPreviousValue(value);
    setValue(value);
}

void DefaultRestorableUnificationKind::setDefaultValue(Kind value) {
    if (m_defaultValue != value) {
        m_defaultValue = value;
        emit defaultValueChanged(m_defaultValue);
    }
}

void DefaultRestorableUnificationKind::restorePreviousValue() {
    if (m_prev != m_cur) {
        m_cur = m_prev;
        emit valueChanged(m_cur);
    }
}

void DefaultRestorableUnificationKind::restoreDefaultValue() {
    if (m_cur != m_defaultValue) {
        m_cur = m_defaultValue;
        emit valueChanged(m_cur);
    }
}

void DefaultRestorableUnificationKind::setValue(Kind value) {
    if (m_cur != value) {
        m_cur = value;
        emit valueChanged(m_cur);
    }
}

DefaultRestorableUnificationKind& DefaultRestorableUnificationKind::operator=(UnificationKindObject const& other) {
    setCurrentAndPreviousValue(other.value());
    return *this;
}




// DefaultRestorableAlgoKind
DefaultRestorableAlgoKind::DefaultRestorableAlgoKind(AlgoKind defaultValue, QObject *parent)
    : m_defaultValue(defaultValue)
    , m_cur(defaultValue)
    , m_prev(defaultValue)
{ }

auto DefaultRestorableAlgoKind::value() const -> AlgoKind {
    return m_cur;
}

auto DefaultRestorableAlgoKind::previousValue() const -> AlgoKind {
    return m_prev;
}

auto DefaultRestorableAlgoKind::defaultValue() const -> AlgoKind {
    return m_defaultValue;
}

bool DefaultRestorableAlgoKind::hasChange() const {
    return m_cur != m_prev;
}

void DefaultRestorableAlgoKind::saveValue() {
    m_prev = m_cur;
}

void DefaultRestorableAlgoKind::setPreviousValue(AlgoKind previousValue) {
    m_prev = previousValue;
}

void DefaultRestorableAlgoKind::setCurrentAndPreviousValue(AlgoKind value) {
    setPreviousValue(value);
    setValue(value);
}

void DefaultRestorableAlgoKind::restorePreviousValue() {
    if (m_prev != m_cur) {
        m_cur = m_prev;
        emit valueChanged(m_cur);
    }
}

void DefaultRestorableAlgoKind::restoreDefaultValue() {
    if (m_cur != m_defaultValue) {
        m_cur = m_defaultValue;
        emit valueChanged(m_cur);
    }
}

void DefaultRestorableAlgoKind::setValue(AlgoKind value) {
    if (m_cur != value) {
        m_cur = value;
        emit valueChanged(m_cur);
    }
}

void DefaultRestorableAlgoKind::setDefaultValue(AlgoKind value) {
    if (m_defaultValue != value) {
        m_defaultValue = value;
        emit defaultValueChanged(m_defaultValue);
    }
}

DefaultRestorableAlgoKind& DefaultRestorableAlgoKind::operator=(AlgoKindObject const& other) {
    setCurrentAndPreviousValue(other.value());
    return *this;
}
