#include "interpolationselectorwidget.h"
#include "ui_interpolationselectorwidget.h"

InterpolationSelectorWidget::InterpolationSelectorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InterpolationSelectorWidget)
{
    ui->setupUi(this);
}

InterpolationSelectorWidget::~InterpolationSelectorWidget()
{
    delete ui;
}
