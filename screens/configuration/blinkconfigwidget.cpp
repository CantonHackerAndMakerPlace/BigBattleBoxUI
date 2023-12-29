#include "blinkconfigwidget.h"
#include "ui_blinkconfigwidget.h"

BlinkConfigWidget::BlinkConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlinkConfigWidget)
{
    ui->setupUi(this);
}

BlinkConfigWidget::~BlinkConfigWidget()
{
    delete ui;
}
