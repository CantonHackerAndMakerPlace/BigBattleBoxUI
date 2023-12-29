#include "unifiedcheckbox.h"
#include "ui_unifiedcheckbox.h"

UnifiedCheckBox::UnifiedCheckBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UnifiedCheckBox)
    , m_link(true)
{
    ui->setupUi(this);

    connect(&m_link, &DefaultRestorableBool::valueChanged,
            ui->unificationCheckBox, &QCheckBox::setChecked);
    connect(ui->unificationCheckBox, &QCheckBox::stateChanged,
            &m_link, &DefaultRestorableBool::setValue);
    connect(&m_link, &DefaultRestorableBool::valueChanged,
            this, &UnifiedCheckBox::valueChanged);
    ui->unificationCheckBox->setCheckState(Qt::Checked);
}

UnifiedCheckBox::~UnifiedCheckBox() {
    delete ui;
}

bool UnifiedCheckBox::hasChanges() const {
    return m_link.hasChange();
}

bool UnifiedCheckBox::getValue() const {
    return m_link.value();
}

void UnifiedCheckBox::init(BooleanObject *settingObject) {
    assert(!m_settingObj && "don't initialize twice");
    m_settingObj = settingObject;
    connect(m_settingObj, &BooleanObject::valueChanged,
            &m_link, &DefaultRestorableBool::setCurrentAndPreviousValue);
    m_link = *m_settingObj;
}

void UnifiedCheckBox::restorePreviousValue() {
    m_link.restorePreviousValue();
}

void UnifiedCheckBox::restoreDefaultValue() {
    m_link.restoreDefaultValue();
}

void UnifiedCheckBox::save() {
    if(!m_settingObj) {
        return;
    }
    m_settingObj->setValue(m_link.value());
}
