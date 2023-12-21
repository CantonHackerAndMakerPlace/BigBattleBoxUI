#include "idleledconfigurationwidget.h"
#include "ui_idleledconfigurationwidget.h"

IdleLedConfigurationWidget::IdleLedConfigurationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IdleLedConfigurationWidget)
{
    ui->setupUi(this);
}

IdleLedConfigurationWidget::~IdleLedConfigurationWidget()
{
    delete ui;
}
