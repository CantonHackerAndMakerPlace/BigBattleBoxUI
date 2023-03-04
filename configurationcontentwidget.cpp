#include "configurationcontentwidget.h"
#include "ui_configurationcontentwidget.h"

ConfigurationContentWidget::ConfigurationContentWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigurationContentWidget)
{
    ui->setupUi(this);
}

ConfigurationContentWidget::~ConfigurationContentWidget()
{
    delete ui;
}
