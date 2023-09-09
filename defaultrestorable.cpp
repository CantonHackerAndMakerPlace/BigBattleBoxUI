#include "defaultrestorable.h"


// DefaultRestorableInt
DefaultRestorableInt::DefaultRestorableInt(int initalValue, int defaultValue, QObject *parent)
    : m_defaultValue(defaultValue)
    , m_cur(initalValue)
    , m_prev(initalValue)
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

// DefaultRestorableString
DefaultRestorableString::DefaultRestorableString(QString const& initalValue, QString const& defaultValue, QObject *parent)
    : m_defaultValue(defaultValue)
    , m_cur(initalValue)
    , m_prev(initalValue)
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

// DefaultRestorableQReal

DefaultRestorableQReal::DefaultRestorableQReal(qreal initalValue, qreal defaultValue, QObject *parent)
    : m_defaultValue(defaultValue)
    , m_cur(initalValue)
    , m_prev(initalValue)
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


DefaultRestorableQColor::DefaultRestorableQColor(QColor initalValue, QColor defaultValue, QObject *parent)
    : m_defaultValue(defaultValue)
    , m_cur(initalValue)
    , m_prev(initalValue)
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
