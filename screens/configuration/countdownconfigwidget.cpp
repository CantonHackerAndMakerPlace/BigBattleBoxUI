#include "countdownconfigwidget.h"
#include "ui_countdownconfigwidget.h"

CountDownConfigWidget::CountDownConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CountDownConfigWidget)
{
    ui->setupUi(this);
    connect(ui->unification, &UnificationDropDownWidget::unificationKindChanged,
            [&](UnificationKindObject::Kind kind) {
                switch(kind) {
                case UnificationKindObject::Kind::BothSame:
                    ui->p2Brightness->setDisabled(true);
                    ui->p2InitialColor->setDisabled(true);
                    ui->p2ConsumingColor->setDisabled(true);
                    ui->p2FinalColor->setDisabled(true);
                    ui->p2FinalBrightness->setDisabled(true);
                    ui->p2Interpolation->setDisabled(true);
                    break;
                case UnificationKindObject::Kind::Separate:
                    ui->p2Brightness->setDisabled(false);
                    ui->p2InitialColor->setDisabled(false);
                    ui->p2ConsumingColor->setDisabled(false);
                    ui->p2FinalColor->setDisabled(false);
                    ui->p2FinalBrightness->setDisabled(false);
                    ui->p2Interpolation->setDisabled(false);
                    break;
                case UnificationKindObject::Kind::SuperStrip:
                    ui->p2Brightness->setDisabled(true);
                    ui->p2InitialColor->setDisabled(true);
                    ui->p2ConsumingColor->setDisabled(true);
                    ui->p2FinalColor->setDisabled(true);
                    ui->p2FinalBrightness->setDisabled(true);
                    ui->p2Interpolation->setDisabled(true);
                    break;
                }
            });
    // Using the default setting for BothSame.
    ui->p2Brightness->setDisabled(true);
    ui->p2InitialColor->setDisabled(true);
    ui->p2ConsumingColor->setDisabled(true);
    ui->p2FinalColor->setDisabled(true);
    ui->p2FinalBrightness->setDisabled(true);
    ui->p2Interpolation->setDisabled(true);

    // Connecting the loop checkbox with the loop off cycle time.
    connect(ui->loop, &DefaultRestorableCheckBox::valueChanged,
            ui->timeBetweenCycle, &DefaultRestorableSpinBox::setEnabled);
    ui->loop->setEnabled(true);
}

CountDownConfigWidget::~CountDownConfigWidget() {
    delete ui;
}

bool CountDownConfigWidget::hasChanges() const {
    return ui->duration->hasChanges() ||
        ui->loop->hasChanges() ||
        ui->unification->hasChanges() ||
        ui->timeBetweenCycle->hasChanges() ||
        ui->p1Brightness->hasChanges() ||
        ui->p1InitialColor->hasChanges() ||
        ui->p1ConsumingColor->hasChanges() ||
        ui->p1FinalColor->hasChanges() ||
        ui->p1FinalBrightness->hasChanges() ||
        ui->p1Interpolation->hasChanges() ||
        ui->p2Brightness->hasChanges() ||
        ui->p2InitialColor->hasChanges() ||
        ui->p2ConsumingColor->hasChanges() ||
        ui->p2FinalColor->hasChanges() ||
        ui->p2FinalBrightness->hasChanges() ||
        ui->p2Interpolation->hasChanges();
}

void CountDownConfigWidget::init(CountDownFillConfig *config) {
    assert(!m_config && "Cannot be initialized twice");
    m_config = config;
    // non player specific widgets
    ui->duration->init(&m_config->duration());
    ui->loop->init(&m_config->loop());
    ui->unification->init(&m_config->unificationKind());
    ui->timeBetweenCycle->init(&m_config->timeBetweenCycles());

    // Player 1 specific widgets.
    ui->p1Brightness->init(&m_config->p1Brightness());
    ui->p1InitialColor->init(&m_config->p1InitialColor());
    ui->p1ConsumingColor->init(&m_config->p1ConsumingColor());
    ui->p1FinalColor->init(&m_config->p1FinalColor());
    ui->p1FinalBrightness->init(&m_config->p1FinalColorBrightness());
    ui->p1Interpolation->init(&m_config->p1Curve(), &m_config->p1CurveAmplitude());

    // Player 2 specific widgets.

    ui->p2Brightness->init(&m_config->p2Brightness());
    ui->p2InitialColor->init(&m_config->p2InitialColor());
    ui->p2ConsumingColor->init(&m_config->p2ConsumingColor());
    ui->p2FinalColor->init(&m_config->p2FinalColor());
    ui->p2FinalBrightness->init(&m_config->p2FinalColorBrightness());
    ui->p2Interpolation->init(&m_config->p2Curve(), &m_config->p2CurveAmplitude());
}

void CountDownConfigWidget::restorePreviousValue() {
    // non player specific widgets
    ui->duration->restorePreviousValue();
    ui->loop->restorePreviousValue();
    ui->unification->restorePreviousValue();
    ui->timeBetweenCycle->restorePreviousValue();

    // Player 1 specific widgets.
    ui->p1Brightness->restorePreviousValue();
    ui->p1InitialColor->restorePreviousValue();
    ui->p1ConsumingColor->restorePreviousValue();
    ui->p1FinalColor->restorePreviousValue();
    ui->p1FinalBrightness->restorePreviousValue();
    ui->p1Interpolation->restorePreviousValue();

    // Player 2 specific widgets.

    ui->p2Brightness->restorePreviousValue();
    ui->p2InitialColor->restorePreviousValue();
    ui->p2ConsumingColor->restorePreviousValue();
    ui->p2FinalColor->restorePreviousValue();
    ui->p2FinalBrightness->restorePreviousValue();
    ui->p2Interpolation->restorePreviousValue();
}

void CountDownConfigWidget::restoreDefaultValue() {
    // non player specific widgets
    ui->duration->restoreDefaultValue();
    ui->loop->restoreDefaultValue();
    ui->unification->restoreDefaultValue();
    ui->timeBetweenCycle->restoreDefaultValue();

    // Player 1 specific widgets.
    ui->p1Brightness->restoreDefaultValue();
    ui->p1InitialColor->restoreDefaultValue();
    ui->p1ConsumingColor->restoreDefaultValue();
    ui->p1FinalColor->restoreDefaultValue();
    ui->p1FinalBrightness->restoreDefaultValue();
    ui->p1Interpolation->restoreDefaultValue();

    // Player 2 specific widgets.

    ui->p2Brightness->restoreDefaultValue();
    ui->p2InitialColor->restoreDefaultValue();
    ui->p2ConsumingColor->restoreDefaultValue();
    ui->p2FinalColor->restoreDefaultValue();
    ui->p2FinalBrightness->restoreDefaultValue();
    ui->p2Interpolation->restoreDefaultValue();
}

void CountDownConfigWidget::save() {
    // non player specific widgets
    ui->duration->save();
    ui->loop->save();
    ui->unification->save();
    ui->timeBetweenCycle->save();

    // Player 1 specific widgets.
    ui->p1Brightness->save();
    ui->p1InitialColor->save();
    ui->p1ConsumingColor->save();
    ui->p1FinalColor->save();
    ui->p1FinalBrightness->save();
    ui->p1Interpolation->save();

    // Player 2 specific widgets.

    ui->p2Brightness->save();
    ui->p2InitialColor->save();
    ui->p2ConsumingColor->save();
    ui->p2FinalColor->save();
    ui->p2FinalBrightness->save();
    ui->p2Interpolation->save();
}
