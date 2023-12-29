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

}

BreathConfigWidget::~BreathConfigWidget() {
    delete ui;
}

bool BreathConfigWidget::hasChanges() const {
    return ui->durationWidget->hasChanges()
        || ui->p1ColorSelectorWidget->hasChanges()
        || ui->p2ColorSelectorWidget->hasChanges()
        || ui->p1InterpolationWidget->hasChanges()
        || ui->p2InterpolationWidget->hasChanges();
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
    ui->p1ColorSelectorWidget->restorePreviousValue();
    ui->p2ColorSelectorWidget->restorePreviousValue();
    ui->p1InterpolationWidget->restorePreviousValue();
    ui->p2InterpolationWidget->restorePreviousValue();
    ui->p1BrightnessSelector->restorePreviousValue();
    ui->p2BrightnessSelector->restorePreviousValue();
}

void BreathConfigWidget::restoreDefaultValue() {
    ui->durationWidget->restoreDefaultValue();
    ui->p1ColorSelectorWidget->restoreDefaultValue();
    ui->p2ColorSelectorWidget->restoreDefaultValue();
    ui->p1InterpolationWidget->restoreDefaultValue();
    ui->p2InterpolationWidget->restoreDefaultValue();
    ui->p1BrightnessSelector->restoreDefaultValue();
    ui->p2BrightnessSelector->restoreDefaultValue();
}

void BreathConfigWidget::save() {
    ui->durationWidget->save();
    ui->p1ColorSelectorWidget->save();
    ui->p2ColorSelectorWidget->save();
    ui->p1InterpolationWidget->save();
    ui->p2InterpolationWidget->save();
    ui->p1BrightnessSelector->save();
    ui->p2BrightnessSelector->save();
}
