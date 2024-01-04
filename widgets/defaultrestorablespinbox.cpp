#include "defaultrestorablespinbox.h"
#include "ui_defaultrestorablespinbox.h"

DefaultRestorableSpinBox::DefaultRestorableSpinBox(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DefaultRestorableSpinBox)
    , m_value(3000)
{
    ui->setupUi(this);

    connect(ui->spinBox, &QSpinBox::valueChanged,
            &m_value, &DefaultRestorableInt::setValue);

    connect(&m_value, &DefaultRestorableInt::valueChanged,
            ui->spinBox, &QSpinBox::setValue);

    connect(&m_value, &DefaultRestorableInt::defaultValueChanged,
            this, &DefaultRestorableSpinBox::defaultValueChanged);

    ui->spinBox->setValue(m_value.value());
}

DefaultRestorableSpinBox::~DefaultRestorableSpinBox() {
    delete ui;
}

DefaultRestorableInt const& DefaultRestorableSpinBox::value() const {
    return m_value;
}

QString DefaultRestorableSpinBox::title() const {
    return ui->label->text();
}

int DefaultRestorableSpinBox::minimum() const {
    return ui->spinBox->minimum();
}

int DefaultRestorableSpinBox::maximum() const {
    return ui->spinBox->maximum();
}

int DefaultRestorableSpinBox::defaultValue() const {
    return m_value.defaultValue();
}

bool DefaultRestorableSpinBox::hasChanges() const {
    return m_value.hasChange();
}

void DefaultRestorableSpinBox::init(IntegerObject *settingConfig) {
    assert(!m_settingObject && "Cannot initialize settings twice");
    m_settingObject = settingConfig;
    connect(m_settingObject, &IntegerObject::valueChanged,
            &m_value, &DefaultRestorableInt::setCurrentAndPreviousValue);
    m_value = *m_settingObject;
}

void DefaultRestorableSpinBox::restorePreviousValue() {
    m_value.restorePreviousValue();
}

void DefaultRestorableSpinBox::restoreDefaultValue() {
    m_value.restoreDefaultValue();
}

void DefaultRestorableSpinBox::save() {
    if(!m_settingObject) {
        return;
    }
    m_settingObject->setValue(m_value.value());
}

void DefaultRestorableSpinBox::setTitle(QString value) {
    ui->label->setText(value);
}

void DefaultRestorableSpinBox::setValue(int value) {
    ui->spinBox->setValue(value);
}

void DefaultRestorableSpinBox::setMinimum(int value) {
    ui->spinBox->setMinimum(value);
}

void DefaultRestorableSpinBox::setMaximum(int value) {
    ui->spinBox->setMaximum(value);
}

void DefaultRestorableSpinBox::setDefaultValue(int value) {
    m_value.setDefaultValue(value);
}
