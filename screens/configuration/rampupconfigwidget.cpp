#include "rampupconfigwidget.h"
#include "ui_rampupconfigwidget.h"

RampUpConfigWidget::RampUpConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RampUpConfigWidget)
{
    ui->setupUi(this);
}

RampUpConfigWidget::~RampUpConfigWidget()
{
    delete ui;
}
