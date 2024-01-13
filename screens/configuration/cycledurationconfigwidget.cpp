#include "cycledurationconfigwidget.h"
#include "ui_cycledurationconfigwidget.h"

CycleDurationConfigWidget::CycleDurationConfigWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CycleDurationConfigWidget)
    , m_duration(3000)
{
    ui->setupUi(this);
    connect(ui->durationSpinBox, &QSpinBox::valueChanged,
            &m_duration, &DefaultRestorableInt::setValue);

    connect(&m_duration, &DefaultRestorableInt::valueChanged,
            ui->durationSpinBox, &QSpinBox::setValue);

    ui->durationSpinBox->setValue(m_duration.value());
    connect(&m_duration, &DefaultRestorableInt::defaultValueChanged,
            this, &CycleDurationConfigWidget::defaultValueChanged);
    connect(&m_duration, &DefaultRestorableInt::valueChanged,
            this, &CycleDurationConfigWidget::valueChanged);
}

CycleDurationConfigWidget::~CycleDurationConfigWidget() {
    delete ui;
}

DefaultRestorableInt const& CycleDurationConfigWidget::getDuration() const {
    return m_duration;
}

bool CycleDurationConfigWidget::hasChanges() {
    return m_duration.hasChange();
}

int CycleDurationConfigWidget::defaultValue() const {
    return m_duration.defaultValue();
}

void CycleDurationConfigWidget::init(IntegerObject *settingConfig) {
    assert(!m_settingObject && "Cannot initialize settings twice");
    m_settingObject = settingConfig;
    connect(m_settingObject, &IntegerObject::valueChanged,
            &m_duration, &DefaultRestorableInt::setCurrentAndPreviousValue);
    m_duration = *m_settingObject;
}

void CycleDurationConfigWidget::restorePreviousValue() {
    m_duration.restorePreviousValue();
}

void CycleDurationConfigWidget::restoreDefaultValue() {
    m_duration.restoreDefaultValue();
}

void CycleDurationConfigWidget::save() {
    if(!m_settingObject) {
        return;
    }
    m_settingObject->setValue(m_duration.value());
}

void CycleDurationConfigWidget::setDefaultValue(int value) {
    m_duration.setDefaultValue(value);
}
