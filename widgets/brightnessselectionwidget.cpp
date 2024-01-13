#include "brightnessselectionwidget.h"
#include "ui_brightnessselectionwidget.h"
#include <widgets/brightnessrangeslider.h>

BrightnessSelectionWidget::BrightnessSelectionWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BrightnessSelectionWidget)
    , m_min(10)
    , m_max(100)
{
    ui->setupUi(this);
    m_slider = new BrightnessRangeSlider(this);
    m_slider->setOrientation(Qt::Horizontal);
    m_slider->setRange(0, 255);
    ui->mainGrid->addWidget(m_slider, 2, 0, 1, 3);

    connect(&m_min, &DefaultRestorableInt::defaultValueChanged,
              this, &BrightnessSelectionWidget::defaultMinimumChanged);
    connect(&m_max, &DefaultRestorableInt::defaultValueChanged,
            this, &BrightnessSelectionWidget::defaultMaximumChanged);

    // Chaining signals together.
    connect(m_slider, &BrightnessRangeSlider::maximumPositionChanged,
            &m_max, &DefaultRestorableInt::setValue);
    connect(m_slider, &BrightnessRangeSlider::minimumPositionChanged,
            &m_min, &DefaultRestorableInt::setValue);

    // Constantly updating the max value on the spin box.
    connect(m_slider, &BrightnessRangeSlider::maximumPositionChanged,
             [&](int value) {
                ui->minValueSpinBox->setMaximum(value - 1);
        });

    // Updating the sider position when values change.
    connect(ui->minValueSpinBox, &QSpinBox::valueChanged,
            m_slider, &BrightnessRangeSlider::setMinimumValue);
    connect(ui->maxValueSpinBox, &QSpinBox::valueChanged,
            m_slider, &BrightnessRangeSlider::setMaximumValue);

    // Updating spinboxes from slider modifications.
    connect(m_slider, &BrightnessRangeSlider::minimumPositionChanged,
            ui->minValueSpinBox, &QSpinBox::setValue);

    connect(m_slider, &BrightnessRangeSlider::maximumPositionChanged,
            ui->maxValueSpinBox, &QSpinBox::setValue);

    // Connecting default restorables.
    connect(&m_max, &DefaultRestorableInt::valueChanged,
            this, &BrightnessSelectionWidget::setMaxValue);
    connect(this, &BrightnessSelectionWidget::maxValueChanged,
            &m_max, &DefaultRestorableInt::setValue);

    connect(&m_min, &DefaultRestorableInt::valueChanged,
            this, &BrightnessSelectionWidget::setMinValue);
    connect(this, &BrightnessSelectionWidget::minValueChanged,
            &m_min, &DefaultRestorableInt::setValue);

    // Updating the spin box's values
    m_slider->setMaximumValue(m_max.value());
    m_slider->setMinimumValue(m_min.value());
    ui->maxValueSpinBox->setValue(m_slider->maximumValue());
    ui->minValueSpinBox->setValue(m_slider->minimumValue());
}

BrightnessSelectionWidget::~BrightnessSelectionWidget() {
    delete ui;
}

DefaultRestorableInt const& BrightnessSelectionWidget::minBrightness() const {
    return m_min;
}

DefaultRestorableInt const& BrightnessSelectionWidget::maxBrightness() const {
    return m_max;
}

int BrightnessSelectionWidget::defaultMinimum() const {
    return m_min.defaultValue();
}

int BrightnessSelectionWidget::defaultMaximum() const {
    return m_max.defaultValue();
}

bool BrightnessSelectionWidget::hasChanges() const {
    return m_min.hasChange() || m_max.hasChange();
}

void BrightnessSelectionWidget::init(IntegerObject *minSetting, IntegerObject *maxSetting) {
    assert(!m_minSetting && !m_maxSetting && "Cannot be initialized twice");
    m_minSetting = minSetting;
    m_maxSetting = maxSetting;

    connect(m_minSetting , &IntegerObject::valueChanged,
            &m_min, &DefaultRestorableInt::setCurrentAndPreviousValue);

    connect(m_maxSetting, &IntegerObject::valueChanged,
            &m_max, &DefaultRestorableInt::setCurrentAndPreviousValue);
    m_min = *m_minSetting;
    m_max = *m_maxSetting;
}

void BrightnessSelectionWidget::restorePreviousValue() {
    m_min.restorePreviousValue();
    m_max.restorePreviousValue();
}

void BrightnessSelectionWidget::restoreDefaultValue() {
    m_min.restoreDefaultValue();
    m_max.restoreDefaultValue();
}

void BrightnessSelectionWidget::save() {
    if(!m_minSetting || !m_maxSetting) {
        return;
    }
    m_minSetting->setValue(m_min.value());
    m_maxSetting->setValue(m_max.value());
}

void BrightnessSelectionWidget::setMinValue(int value) {
    m_min.setValue(value);
}

void BrightnessSelectionWidget::setMaxValue(int value) {
    m_max.setValue(value);
}

void BrightnessSelectionWidget::setDefaultMinimum(int value) {
    m_min.setValue(value);
    m_min.setDefaultValue(value);
}

void BrightnessSelectionWidget::setDefaultMaximum(int value) {
    m_max.setValue(value);
    m_max.setDefaultValue(value);
}
