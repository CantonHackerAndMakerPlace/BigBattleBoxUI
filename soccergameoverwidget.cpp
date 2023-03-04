#include "soccergameoverwidget.h"
#include "ui_soccergameoverwidget.h"

SoccerGameOverWidget::SoccerGameOverWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoccerGameOverWidget)
{
    ui->setupUi(this);
}

SoccerGameOverWidget::~SoccerGameOverWidget()
{
    delete ui;
}
