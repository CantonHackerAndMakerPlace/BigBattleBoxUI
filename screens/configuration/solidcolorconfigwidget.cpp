#include "solidcolorconfigwidget.h"
#include "ui_solidcolorconfigwidget.h"

SolidColorConfigWidget::SolidColorConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SolidColorConfigWidget)
{
    ui->setupUi(this);
    connect(ui->unification, &UnifiedCheckBox::valueChanged,
            [&](bool value) {
                ui->p2Brightness->setDisabled(value);
                ui->p2Color->setDisabled(value);
            });
}

SolidColorConfigWidget::~SolidColorConfigWidget() {
    delete ui;
}

bool SolidColorConfigWidget::hasChanges() const {
    return ui->unification->hasChanges() ||
           ui->p1Color->hasChanges() ||
           ui->p1Brightness->hasChanges() ||
           ui->p2Color->hasChanges() ||
           ui->p2Brightness->hasChanges();
}

void SolidColorConfigWidget::init(SolidColorConfig *config) {
    assert(!m_config && "Cannot be initialized twice");
    m_config = config;
    ui->unification->init(&m_config->unified());
    ui->p1Color->init(&m_config->p1Color());
    ui->p1Brightness->init(&m_config->p1Brightness());
    ui->p2Color->init(&m_config->p2Color());
    ui->p2Brightness->init(&m_config->p2Brightness());
}

void SolidColorConfigWidget::restorePreviousValue() {
    ui->unification->restorePreviousValue();
    ui->p1Color->restorePreviousValue();
    ui->p1Brightness->restorePreviousValue();
    ui->p2Color->restorePreviousValue();
    ui->p2Brightness->restorePreviousValue();

}

void SolidColorConfigWidget::restoreDefaultValue() {
    ui->unification->restoreDefaultValue();
    ui->p1Color->restoreDefaultValue();
    ui->p1Brightness->restoreDefaultValue();
    ui->p2Color->restoreDefaultValue();
    ui->p2Brightness->restoreDefaultValue();
}

void SolidColorConfigWidget::save() {
    ui->unification->save();
    ui->p1Color->save();
    ui->p1Brightness->save();
    ui->p2Color->save();
    ui->p2Brightness->save();
}
