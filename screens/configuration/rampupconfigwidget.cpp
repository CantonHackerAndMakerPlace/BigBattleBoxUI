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

    DR_SPIN_BOX_CONNECT(RampUpConfigWidget, duration, durationDefaultChanged, changesWereMade)
    UNIFIED_CB_CONNECT(RampUpConfigWidget, unification, unificationDefaultChanged, changesWereMade)
    DF_CB_CONNECT(RampUpConfigWidget, loop, loopDefaultChanged, changesWereMade)

    BRIGHTNESS_SLIDER_CONNECT(RampUpConfigWidget, p1BrightnessSlider, p1MinBrightnessDefaultChanged, p1MaxBrightnessDefaultChanged, changesWereMade)
    INTERPOLATION_CONNECT(RampUpConfigWidget, p1Curve, p1CurveDefaultChanged, changesWereMade)
    COLOR_SELECT_CONNECT(RampUpConfigWidget, p1Color, p1ColorDefaultChanged, changesWereMade)

    BRIGHTNESS_SLIDER_CONNECT(RampUpConfigWidget, p2BrightnessSlider, p2MinBrightnessDefaultChanged, p2MaxBrightnessDefaultChanged, changesWereMade)
    INTERPOLATION_CONNECT(RampUpConfigWidget, p2Curve, p2CurveDefaultChanged, changesWereMade)
    COLOR_SELECT_CONNECT(RampUpConfigWidget, p2Color, p2ColorDefaultChanged, changesWereMade)
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

DR_SPIN_BOX_DEFAULT_VALUE_DEF(RampUpConfigWidget, duration, durationDefault, setDurationDefault)
UNIFIED_CB_DEFAULT_VALUE_DEF(RampUpConfigWidget, unification, unificationDefault, setUnificationDefault)
UNIFIED_CB_DEFAULT_VALUE_DEF(RampUpConfigWidget, loop, loopDefault, setLoopDefault)

INTERPOLATION_DEFAULT_VALUE_DEF(RampUpConfigWidget, p1Curve, p1CurveDefault, setP1CurveDefault)
BRIGHTNESS_SLIDER_DEFAULT_VALUE_DEF(RampUpConfigWidget, p1BrightnessSlider, p1MinBrightnessDefault, setP1MinBrightnessDefault, p1MaxBrightnessDefault, setP1MaxBrightnessDefault)
COLOR_SELECT_DEFAULT_VALUE_DEF(RampUpConfigWidget, p1Color, p1ColorDefault, setP1ColorDefault)

INTERPOLATION_DEFAULT_VALUE_DEF(RampUpConfigWidget, p2Curve, p2CurveDefault, setP2CurveDefault)
BRIGHTNESS_SLIDER_DEFAULT_VALUE_DEF(RampUpConfigWidget, p2BrightnessSlider, p2MinBrightnessDefault, setP2MinBrightnessDefault, p2MaxBrightnessDefault, setP2MaxBrightnessDefault)
COLOR_SELECT_DEFAULT_VALUE_DEF(RampUpConfigWidget, p2Color, p2ColorDefault, setP2ColorDefault)
