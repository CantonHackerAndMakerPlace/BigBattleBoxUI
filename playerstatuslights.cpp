#include "playerstatuslights.h"
#include "ui_playerstatuslights.h"

PlayerStatusLights::PlayerStatusLights(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerStatusLights)
{
    ui->setupUi(this);
}

PlayerStatusLights::~PlayerStatusLights()
{
    delete ui;
}

StateIndicatorWidget *PlayerStatusLights::readyState() const {
    return ui->readyIndicator;
}
StateIndicatorWidget *PlayerStatusLights::readyState() {
    return ui->readyIndicator;
}

StateIndicatorWidget *PlayerStatusLights::doorState() const {
    return ui->doorIndicator;
}
StateIndicatorWidget *PlayerStatusLights::doorState() {
    return ui->doorIndicator;
}

StateIndicatorWidget *PlayerStatusLights::trapDoorState() const {
    return ui->trapDoorIndicator;
}
StateIndicatorWidget *PlayerStatusLights::trapDoorState() {
    return ui->trapDoorIndicator;
}

StateIndicatorWidget *PlayerStatusLights::conceedState() const {
    return ui->conceedIndicator;
}
StateIndicatorWidget *PlayerStatusLights::conceedState() {
    return ui->conceedIndicator;
}
