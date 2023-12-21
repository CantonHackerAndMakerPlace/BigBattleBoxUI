#include "idleledconfigurationwidget.h"
#include "ui_idleledconfigurationwidget.h"

IdleLedConfigurationWidget::IdleLedConfigurationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IdleLedConfigurationWidget)
{
    ui->setupUi(this);
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
