#include "rampupconfigwidget.h"
#include "ui_rampupconfigwidget.h"

RampUpConfigWidget::RampUpConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RampUpConfigWidget)
{
    ui->setupUi(this);
    connect(ui->unification, &UnifiedCheckBox::valueChanged,
            ui->p2Color, &ColorSelectionWidget::setDisabled);
    connect(ui->unification, &UnifiedCheckBox::valueChanged,
            ui->p2Curve, &InterpolationSelectorWidget::setDisabled);
    connect(ui->unification, &UnifiedCheckBox::valueChanged,
            ui->p2BrightnessSlider, &BrightnessSelectionWidget::setDisabled);
    ui->unification->setValue(true);
    ui->unification->setValue(false);
}

RampUpConfigWidget::~RampUpConfigWidget() {
    delete ui;
}

bool RampUpConfigWidget::disableDuration() const {
    return !ui->duration->isEnabled();
}

bool RampUpConfigWidget::hasChanges() const {
    return false;
}

void RampUpConfigWidget::init(RampUpConfig *config) {
    assert(!m_config && "Cannot initialize twice");
    m_config = config;
    ui->duration->init(&m_config->cycleDuration());
    ui->unification->init(&m_config->unified());
    ui->loop->init(&m_config->loop());
    ui->p1Color->init(&m_config->p1Color());
    ui->p1Curve->init(&m_config->p1Curve(), &m_config->p1Amplitude());
    ui->p1BrightnessSlider->init(&m_config->p1MinBrightness(), &m_config->p1MaxBrightness());
    ui->p2Color->init(&m_config->p2Color());
    ui->p2Curve->init(&m_config->p2Curve(), &m_config->p2Amplitude());
    ui->p2BrightnessSlider->init(&m_config->p2MinBrightness(), &m_config->p2MaxBrightness());
}

void RampUpConfigWidget::restorePreviousValue() {
    ui->duration->restorePreviousValue();
    ui->unification->restorePreviousValue();
    ui->loop->restorePreviousValue();
    ui->p1Color->restorePreviousValue();
    ui->p1Curve->restorePreviousValue();
    ui->p1BrightnessSlider->restorePreviousValue();
    ui->p2Color->restorePreviousValue();
    ui->p2Curve->restorePreviousValue();
    ui->p2BrightnessSlider->restorePreviousValue();
}

void RampUpConfigWidget::restoreDefaultValue() {
    ui->duration->restoreDefaultValue();
    ui->unification->restoreDefaultValue();
    ui->loop->restoreDefaultValue();
    ui->p1Color->restoreDefaultValue();
    ui->p1Curve->restoreDefaultValue();
    ui->p1BrightnessSlider->restoreDefaultValue();
    ui->p2Color->restoreDefaultValue();
    ui->p2Curve->restoreDefaultValue();
    ui->p2BrightnessSlider->restoreDefaultValue();
}

void RampUpConfigWidget::save() {
    ui->duration->save();
    ui->unification->save();
    ui->loop->save();
    ui->p1Color->save();
    ui->p1Curve->save();
    ui->p1BrightnessSlider->save();
    ui->p2Color->save();
    ui->p2Curve->save();
    ui->p2BrightnessSlider->save();
}

void RampUpConfigWidget::setDisableDuration(bool value) {
    if (disableDuration() != value) {
        ui->duration->setDisabled(value);
        ui->loop->setDisabled(value);
        emit disableDurationChanged(value);
    }
}

