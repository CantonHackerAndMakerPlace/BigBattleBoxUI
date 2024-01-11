#include "deathmatchconfigledconfigwidget.h"
#include "ui_deathmatchconfigledconfigwidget.h"

DeathMatchConfigLEDConfigWidget::DeathMatchConfigLEDConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeathMatchConfigLEDConfigWidget)
{
    ui->setupUi(this);
}

DeathMatchConfigLEDConfigWidget::~DeathMatchConfigLEDConfigWidget()
{
    delete ui;
}
