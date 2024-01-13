#include "breathconfigwidget.h"
#include "ui_breathconfigwidget.h"

BreathConfigWidget::BreathConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BreathConfigWidget)
{
    ui->setupUi(this);

    connect(ui->unificationCheckBoxWidget, &UnifiedCheckBox::valueChanged,
            ui->p2ColorSelectorWidget, &QWidget::setDisabled);
    ui->p2ColorSelectorWidget->setDisabled(ui->unificationCheckBoxWidget->getValue());

    connect(ui->unificationCheckBoxWidget, &UnifiedCheckBox::valueChanged,
            ui->p2InterpolationWidget, &QWidget::setDisabled);
    ui->p2InterpolationWidget->setDisabled(ui->unificationCheckBoxWidget->getValue());

    connect(ui->unificationCheckBoxWidget, &UnifiedCheckBox::valueChanged,
            ui->p2BrightnessSelector, &QWidget::setDisabled);
    ui->p2BrightnessSelector->setDisabled(ui->unificationCheckBoxWidget->getValue());

    CYCLE_DURATION_CONNECT(BreathConfigWidget, durationWidget, durationDefaultChanged, changesWereMade)
    UNIFIED_CB_CONNECT(BreathConfigWidget, unificationCheckBoxWidget, unificationDefaultChanged, changesWereMade)

    BRIGHTNESS_SLIDER_CONNECT(BreathConfigWidget, p1BrightnessSelector, p1MinBrightnessDefaultChanged, p1MaxBrightnessDefaultChanged, changesWereMade)
    INTERPOLATION_CONNECT(BreathConfigWidget, p1InterpolationWidget, p1CurveDefaultChanged, changesWereMade)
    COLOR_SELECT_CONNECT(BreathConfigWidget, p1ColorSelectorWidget, p1ColorDefaultChanged, changesWereMade)

    BRIGHTNESS_SLIDER_CONNECT(BreathConfigWidget, p2BrightnessSelector, p2MinBrightnessDefaultChanged, p2MaxBrightnessDefaultChanged, changesWereMade)
    INTERPOLATION_CONNECT(BreathConfigWidget, p2InterpolationWidget, p2CurveDefaultChanged, changesWereMade)
    COLOR_SELECT_CONNECT(BreathConfigWidget, p2ColorSelectorWidget, p2ColorDefaultChanged, changesWereMade)
}

BreathConfigWidget::~BreathConfigWidget() {
    delete ui;
}

bool BreathConfigWidget::hasChanges() const {
    return ui->durationWidget->hasChanges()
        || ui->unificationCheckBoxWidget->hasChanges()
        || ui->p1ColorSelectorWidget->hasChanges()
        || ui->p2ColorSelectorWidget->hasChanges()
        || ui->p1InterpolationWidget->hasChanges()
        || ui->p2InterpolationWidget->hasChanges()
        || ui->p1BrightnessSelector->hasChanges()
        || ui->p2BrightnessSelector->hasChanges();
}

void BreathConfigWidget::init(BreathConfig *config) {
    assert(!m_config && "cannot initialize twice");
    m_config = config;
    ui->durationWidget->init(&m_config->cycleDuration());
    ui->unificationCheckBoxWidget->init(&m_config->unified());

    ui->p1ColorSelectorWidget->init(&m_config->p1Color());
    ui->p1InterpolationWidget->init(&m_config->p1Interpolation(), &m_config->p1CurveAmpliatude());
    ui->p1BrightnessSelector->init(&m_config->p1MinBrightness(), &m_config->p1MaxBrightness());

    ui->p2ColorSelectorWidget->init(&m_config->p2Color());
    ui->p2InterpolationWidget->init(&m_config->p2Interpolation(), &m_config->p2CurveAmpliatude());
    ui->p2BrightnessSelector->init(&m_config->p2MinBrightness(), &m_config->p2MaxBrightness());

}

void BreathConfigWidget::restorePreviousValue() {
    ui->durationWidget->restorePreviousValue();
    ui->unificationCheckBoxWidget->restorePreviousValue();
    ui->p1ColorSelectorWidget->restorePreviousValue();
    ui->p2ColorSelectorWidget->restorePreviousValue();
    ui->p1InterpolationWidget->restorePreviousValue();
    ui->p2InterpolationWidget->restorePreviousValue();
    ui->p1BrightnessSelector->restorePreviousValue();
    ui->p2BrightnessSelector->restorePreviousValue();
}

void BreathConfigWidget::restoreDefaultValue() {
    ui->durationWidget->restoreDefaultValue();
    ui->unificationCheckBoxWidget->restoreDefaultValue();
    ui->p1ColorSelectorWidget->restoreDefaultValue();
    ui->p2ColorSelectorWidget->restoreDefaultValue();
    ui->p1InterpolationWidget->restoreDefaultValue();
    ui->p2InterpolationWidget->restoreDefaultValue();
    ui->p1BrightnessSelector->restoreDefaultValue();
    ui->p2BrightnessSelector->restoreDefaultValue();
}

void BreathConfigWidget::save() {
    ui->durationWidget->save();
    ui->unificationCheckBoxWidget->save();
    ui->p1ColorSelectorWidget->save();
    ui->p2ColorSelectorWidget->save();
    ui->p1InterpolationWidget->save();
    ui->p2InterpolationWidget->save();
    ui->p1BrightnessSelector->save();
    ui->p2BrightnessSelector->save();
}

DR_SPIN_BOX_DEFAULT_VALUE_DEF(BreathConfigWidget, durationWidget, durationDefault, setDurationDefault)
UNIFIED_CB_DEFAULT_VALUE_DEF(BreathConfigWidget, unificationCheckBoxWidget, unificationDefault, setUnificationDefault)

INTERPOLATION_DEFAULT_VALUE_DEF(BreathConfigWidget, p1InterpolationWidget, p1CurveDefault, setP1CurveDefault)
BRIGHTNESS_SLIDER_DEFAULT_VALUE_DEF(BreathConfigWidget, p1BrightnessSelector, p1MinBrightnessDefault, setP1MinBrightnessDefault, p1MaxBrightnessDefault, setP1MaxBrightnessDefault)
COLOR_SELECT_DEFAULT_VALUE_DEF(BreathConfigWidget, p1ColorSelectorWidget, p1ColorDefault, setP1ColorDefault)

INTERPOLATION_DEFAULT_VALUE_DEF(BreathConfigWidget, p2InterpolationWidget, p2CurveDefault, setP2CurveDefault)
BRIGHTNESS_SLIDER_DEFAULT_VALUE_DEF(BreathConfigWidget, p2BrightnessSelector, p2MinBrightnessDefault, setP2MinBrightnessDefault, p2MaxBrightnessDefault, setP2MaxBrightnessDefault)
COLOR_SELECT_DEFAULT_VALUE_DEF(BreathConfigWidget, p2ColorSelectorWidget, p2ColorDefault, setP2ColorDefault)
