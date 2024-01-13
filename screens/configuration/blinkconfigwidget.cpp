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

    UNIFIED_CB_CONNECT(BlinkConfigWidget, unification, unificationDefaultChanged, changesWereMade)
    DR_SPIN_BOX_CONNECT(BlinkConfigWidget, onDuration, onDurationDefaultChanged, changesWereMade)
    DR_SPIN_BOX_CONNECT(BlinkConfigWidget, offDuration, offDurationDefaultChanged, changesWereMade)
    DR_SPIN_BOX_CONNECT(BlinkConfigWidget, numberOfBlinks, numberOfBlinksDefaultChanged, changesWereMade)

    DR_SPIN_BOX_CONNECT(BlinkConfigWidget, p1OnBrightness, p1OnBrightnessDefaultChanged, changesWereMade)
    COLOR_SELECT_CONNECT(BlinkConfigWidget, p1OnColor, p1OnColorDefaultChanged, changesWereMade)
    DR_SPIN_BOX_CONNECT(BlinkConfigWidget, p1OffBrightness, p1OffBrightnessDefaultChanged, changesWereMade)
    COLOR_SELECT_CONNECT(BlinkConfigWidget, p1OffColor, p1OffColorDefaultChanged, changesWereMade)

    DR_SPIN_BOX_CONNECT(BlinkConfigWidget, p2OnBrightness, p2OnBrightnessDefaultChanged, changesWereMade)
    COLOR_SELECT_CONNECT(BlinkConfigWidget, p2OnColor, p2OnColorDefaultChanged, changesWereMade)
    DR_SPIN_BOX_CONNECT(BlinkConfigWidget, p2OffBrightness, p2OffBrightnessDefaultChanged, changesWereMade)
    COLOR_SELECT_CONNECT(BlinkConfigWidget, p2OffColor, p1OffColorDefaultChanged, changesWereMade)
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

UNIFIED_CB_DEFAULT_VALUE_DEF(BlinkConfigWidget, unification, unificationDefault, setUnificationDefault)
DR_SPIN_BOX_DEFAULT_VALUE_DEF(BlinkConfigWidget, onDuration, onDurationDefault, setOnDurationDefault)
DR_SPIN_BOX_DEFAULT_VALUE_DEF(BlinkConfigWidget, offDuration, offDurationDefault, setOffDurationDefault)
DR_SPIN_BOX_DEFAULT_VALUE_DEF(BlinkConfigWidget, numberOfBlinks, numberOfBlinksDefault, setNumberOfBlinksDefault)

DR_SPIN_BOX_DEFAULT_VALUE_DEF(BlinkConfigWidget, p1OnBrightness, p1OnBrightnessDefault, setP1OnBrightnessDefault)
COLOR_SELECT_DEFAULT_VALUE_DEF(BlinkConfigWidget, p1OnColor, p1OnColorDefault, setP1OnColorDefault)
DR_SPIN_BOX_DEFAULT_VALUE_DEF(BlinkConfigWidget, p1OffBrightness, p1OffBrightnessDefault, setP1OffBrightnessDefault)
COLOR_SELECT_DEFAULT_VALUE_DEF(BlinkConfigWidget, p1OffColor, p1OffColorDefault, setP1OffColorDefault)

DR_SPIN_BOX_DEFAULT_VALUE_DEF(BlinkConfigWidget, p2OnBrightness, p2OnBrightnessDefault, setP2OnBrightnessDefault)
COLOR_SELECT_DEFAULT_VALUE_DEF(BlinkConfigWidget, p2OnColor, p2OnColorDefault, setP2OnColorDefault)
DR_SPIN_BOX_DEFAULT_VALUE_DEF(BlinkConfigWidget, p2OffBrightness, p2OffBrightnessDefault, setP2OffBrightnessDefault)
COLOR_SELECT_DEFAULT_VALUE_DEF(BlinkConfigWidget, p2OffColor, p2OffColorDefault, setP2OffColorDefault)
