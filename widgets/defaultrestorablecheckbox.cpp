#include "defaultrestorablecheckbox.h"
#include "ui_defaultrestorablecheckbox.h"

DefaultRestorableCheckBox::DefaultRestorableCheckBox(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DefaultRestorableCheckBox)
    , m_value(false)
{
    ui->setupUi(this);

    connect(&m_value, &DefaultRestorableBool::valueChanged,
            ui->checkBox, &QCheckBox::setChecked);
    connect(ui->checkBox, &QCheckBox::stateChanged,
            &m_value, &DefaultRestorableBool::setValue);
    connect(&m_value, &DefaultRestorableBool::valueChanged,
            this, &DefaultRestorableCheckBox::valueChanged);
    ui->checkBox->setCheckState(Qt::Checked);
}

DefaultRestorableCheckBox::~DefaultRestorableCheckBox()
{
    delete ui;
}

QString DefaultRestorableCheckBox::title() const {
    return ui->checkBox->text();
}


bool DefaultRestorableCheckBox::hasChanges() const {
    return m_value.hasChange();
}

bool DefaultRestorableCheckBox::isChecked() const {
    return m_value.value();
}

void DefaultRestorableCheckBox::init(BooleanObject *settingConfig) {
    assert(!m_settingConfig && "Cannot be initialized twice");
    m_settingConfig = settingConfig;
    connect(m_settingConfig, &BooleanObject::valueChanged,
            &m_value, &DefaultRestorableBool::setCurrentAndPreviousValue);
    m_value = *m_settingConfig;
}

void DefaultRestorableCheckBox::restorePreviousValue() {
    m_value.restorePreviousValue();
}

void DefaultRestorableCheckBox::restoreDefaultValue() {
    m_value.restoreDefaultValue();
}

void DefaultRestorableCheckBox::save() {
    if(!m_settingConfig) {
        return;
    }
    m_settingConfig->setValue(m_value.value());
}

void DefaultRestorableCheckBox::setTitle(QString value) {
    auto currentTitle = ui->checkBox->text();
    if (value != currentTitle) {
        ui->checkBox->setText(value);
        emit titleChanged(currentTitle);
    }
}
