#include "deathmatchcompletewidget.h"
#include "ui_deathmatchcompletewidget.h"

DeathMatchCompleteWidget::DeathMatchCompleteWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeathMatchCompleteWidget)
{
    ui->setupUi(this);
}

DeathMatchCompleteWidget::~DeathMatchCompleteWidget()
{
    delete ui;
}
