#include "playerwinswidget.h"
#include "ui_playerwinswidget.h"

PlayerWinsWidget::PlayerWinsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerWinsWidget)
{
    ui->setupUi(this);
}

PlayerWinsWidget::~PlayerWinsWidget()
{
    delete ui;
}
