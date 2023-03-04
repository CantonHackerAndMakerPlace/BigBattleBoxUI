#include "buttonconfigwidget.h"
#include "ui_buttonconfigwidget.h"

ButtonConfigWidget::ButtonConfigWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ButtonConfigWidget)
    , m_kind(PhysicalButton::SwitchConfig::NormallyOpen)
{
    ui->setupUi(this);
    connect(ui->normallyClosedButton, &QRadioButton::clicked,
            [&](bool isChecked) {
        setSwitchKind(PhysicalButton::SwitchConfig::NormallyClosed);
    });

    connect(ui->normallyOpenButton, &QRadioButton::clicked,
            [&](bool isChecked) {
        setSwitchKind(PhysicalButton::SwitchConfig::NormallyOpen);
    });
    connect(this, &ButtonConfigWidget::switchKindChanged,
            [&](PhysicalButton::SwitchConfig kind){
        switch(kind) {
        case PhysicalButton::SwitchConfig::NormallyOpen:
            ui->normallyOpenButton->setChecked(true);
            ui->normallyClosedButton->setChecked(false);
            break;
        case PhysicalButton::SwitchConfig::NormallyClosed:
            ui->normallyOpenButton->setChecked(false);
            ui->normallyClosedButton->setChecked(true);
            break;
        }
    });
}

ButtonConfigWidget::~ButtonConfigWidget()
{
    delete ui;
}

PhysicalButton::SwitchConfig ButtonConfigWidget::switchKind() const {
    return m_kind;
}

void ButtonConfigWidget::setSwitchKind(PhysicalButton::SwitchConfig kind) {
    if (m_kind !=kind) {
        m_kind = kind;
        emit switchKindChanged(m_kind);
    }
}
