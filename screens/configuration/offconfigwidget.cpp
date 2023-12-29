#include "offconfigwidget.h"
#include "ui_offconfigwidget.h"

OffConfigWidget::OffConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OffConfigWidget)
{
    ui->setupUi(this);
}

OffConfigWidget::~OffConfigWidget()
{
    delete ui;
}
