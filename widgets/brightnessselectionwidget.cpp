#include "brightnessselectionwidget.h"
#include "ui_brightnessselectionwidget.h"
#include <widgets/brightnessrangeslider.h>

BrightnessSelectionWidget::BrightnessSelectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BrightnessSelectionWidget)
{
    ui->setupUi(this);
    m_slider = new BrightnessRangeSlider(this);
    m_slider->setOrientation(Qt::Horizontal);
    m_slider->setRange(0, 255);
    ui->mainGrid->addWidget(m_slider, 2, 0, 1, 3);


    // Chaining signals together.
    connect(m_slider, &BrightnessRangeSlider::maximumPositionChanged,
            this, &BrightnessSelectionWidget::maxValueChanged);
    connect(m_slider, &BrightnessRangeSlider::minimumPositionChanged,
            this, &BrightnessSelectionWidget::minValueChanged);

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

    // Updating the spin box's values
    ui->maxValueSpinBox->setValue(m_slider->maximumValue());
    ui->minValueSpinBox->setValue(m_slider->minimumValue());

}

BrightnessSelectionWidget::~BrightnessSelectionWidget() {
    delete ui;
}

void BrightnessSelectionWidget::setMinValue(int value) {
    m_slider->setMinimumPosition(value);
}

void BrightnessSelectionWidget::setMaxValue(int value) {
    m_slider->setMaximumPosition(value);
}
