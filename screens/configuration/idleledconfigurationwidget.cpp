#include "idleledconfigurationwidget.h"
#include "ui_idleledconfigurationwidget.h"
#include "widgets/BrightnessRangeSlider.h"

IdleLedConfigurationWidget::IdleLedConfigurationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IdleLedConfigurationWidget)
{
    ui->setupUi(this);
//    ui->interpolationWidget->setMinimumSize(400, 400);
//    ui->interpolationWidget->setMaximumSize(400, 400);
//    m_brightness = new BrightnessRangeSlider(Qt::Horizontal, this);
//    m_brightness->setMinimum(0);
//    m_brightness->setMaximum(99);
//    m_brightness->setLowerValue(0);
//    m_brightness->setUpperValue(100);
//    m_brightness->setStyleSheet("width: 500px; height: 10px;");
//    m_brightness->setMinimumWidth(400);
//    ui->gridLayout->addWidget(m_brightness, 4, 0);

}

IdleLedConfigurationWidget::~IdleLedConfigurationWidget() {
    delete ui;
}

void IdleLedConfigurationWidget::init(ApplicationState *state) {
    assert(m_state && "Can't initialize twice");
    m_state = state;
    connect(ui->colorSelectorWidget, &ColorSelectionWidget::colorChanged,
            [&](QColor color) {
                qDebug() << "Spec of color: " << color.spec();

                m_state->arduinoClient()->p1SetColor(color);
            }
    );
}
