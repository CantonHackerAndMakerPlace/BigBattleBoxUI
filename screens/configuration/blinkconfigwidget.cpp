#include "blinkconfigwidget.h"
#include "ui_blinkconfigwidget.h"

BlinkConfigWidget::BlinkConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlinkConfigWidget)
{
    ui->setupUi(this);

    connect(ui->unification, &UnifiedCheckBox::valueChanged,
            ui->p2OffBrightness, &DefaultRestorableSpinBox::setDisabled);
    connect(ui->unification, &UnifiedCheckBox::valueChanged,
            ui->p2OnBrightness, &DefaultRestorableSpinBox::setDisabled);
    connect(ui->unification, &UnifiedCheckBox::valueChanged,
            ui->p2OnColor, &ColorSelectionWidget::setDisabled);
    connect(ui->unification, &UnifiedCheckBox::valueChanged,
            ui->p2OffColor, &ColorSelectionWidget::setDisabled);
    ui->unification->setValue(true);
    ui->unification->setValue(false);
}

BlinkConfigWidget::~BlinkConfigWidget() {
    delete ui;
}

bool BlinkConfigWidget::hasChanges() const {
    return false;
}

void BlinkConfigWidget::init(BlinkConfig *config) {
    assert(!m_config && "Cannot be initialzied twice");
    m_config = config;
    // Widget names
    ui->unification->init(&m_config->unified());
    ui->numberOfBlinks->init(&m_config->numberOfBlinks());
    ui->onDuration->init(&m_config->onDuration());
    ui->offDuration->init(&m_config->offDuration());

    ui->p1OffBrightness->init(&m_config->p1OffBrightness());
    ui->p1OnColor->init(&m_config->p1OnColor());
    ui->p1OffColor->init(&m_config->p1OffColor());
    ui->p1OnBrightness->init(&m_config->p1OnBrightness());

    ui->p2OffBrightness->init(&m_config->p2OffBrightness());
    ui->p2OnBrightness->init(&m_config->p2OnBrightness());
    ui->p2OnColor->init(&m_config->p2OnColor());
    ui->p2OffColor->init(&m_config->p2OffColor());
}

void BlinkConfigWidget::restorePreviousValue() {
    ui->unification->restorePreviousValue();
    ui->p1OffBrightness->restorePreviousValue();
    ui->p1OnColor->restorePreviousValue();
    ui->p2OnColor->restorePreviousValue();
    ui->p2OnBrightness->restorePreviousValue();
    ui->offDuration->restorePreviousValue();
    ui->p2OffBrightness->restorePreviousValue();
    ui->p1OnBrightness->restorePreviousValue();
    ui->numberOfBlinks->restorePreviousValue();
    ui->onDuration->restorePreviousValue();
    ui->p1OffColor->restorePreviousValue();
    ui->p2OffColor->restorePreviousValue();
}

void BlinkConfigWidget::restoreDefaultValue() {
    ui->unification->restoreDefaultValue();
    ui->p1OffBrightness->restoreDefaultValue();
    ui->p1OnColor->restoreDefaultValue();
    ui->p2OnColor->restoreDefaultValue();
    ui->p2OnBrightness->restoreDefaultValue();
    ui->offDuration->restoreDefaultValue();
    ui->p2OffBrightness->restoreDefaultValue();
    ui->p1OnBrightness->restoreDefaultValue();
    ui->numberOfBlinks->restoreDefaultValue();
    ui->onDuration->restoreDefaultValue();
    ui->p1OffColor->restoreDefaultValue();
    ui->p2OffColor->restoreDefaultValue();
}

void BlinkConfigWidget::save() {
    ui->unification->save();
    ui->p1OffBrightness->save();
    ui->p1OnColor->save();
    ui->p2OnColor->save();
    ui->p2OnBrightness->save();
    ui->offDuration->save();
    ui->p2OffBrightness->save();
    ui->p1OnBrightness->save();
    ui->numberOfBlinks->save();
    ui->onDuration->save();
    ui->p1OffColor->save();
    ui->p2OffColor->save();
}

