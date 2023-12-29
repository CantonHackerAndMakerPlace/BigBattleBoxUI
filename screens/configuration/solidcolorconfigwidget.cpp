#include "solidcolorconfigwidget.h"
#include "ui_solidcolorconfigwidget.h"

SolidColorConfigWidget::SolidColorConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SolidColorConfigWidget)
{
    ui->setupUi(this);
}

SolidColorConfigWidget::~SolidColorConfigWidget()
{
    delete ui;
}
