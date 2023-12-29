#include "cylonconfigwidget.h"
#include "ui_cylonconfigwidget.h"

CylonConfigWidget::CylonConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CylonConfigWidget)
{
    ui->setupUi(this);
}

CylonConfigWidget::~CylonConfigWidget()
{
    delete ui;
}
