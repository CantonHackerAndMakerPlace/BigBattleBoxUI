#include "countdownconfigwidget.h"
#include "ui_countdownconfigwidget.h"

CountDownConfigWidget::CountDownConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CountDownConfigWidget)
{
    ui->setupUi(this);
}

CountDownConfigWidget::~CountDownConfigWidget()
{
    delete ui;
}
