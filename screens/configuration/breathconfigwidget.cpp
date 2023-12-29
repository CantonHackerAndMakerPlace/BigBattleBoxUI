#include "breathconfigwidget.h"
#include "ui_breathconfigwidget.h"

BreathConfigWidget::BreathConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BreathConfigWidget)
{
    ui->setupUi(this);
}

BreathConfigWidget::~BreathConfigWidget()
{
    delete ui;
}
