#include "durationwidget.h"
#include "ui_durationwidget.h"
#include <QSpinBox>

DurationWidget::DurationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DurationWidget)
{
    ui->setupUi(this);
    connect(ui->duration, &QSpinBox::valueChanged,
            this, &DurationWidget::durationChanged);
}

DurationWidget::~DurationWidget()
{
    delete ui;
}

int DurationWidget::duration() const {
    return this->ui->duration->value();
}

void DurationWidget::setDuration(int i) {
    if (duration() != i) {
        this->ui->duration->setValue(i);
        emit durationChanged(duration());
    }
}

void DurationWidget::on_plus1MinButton_clicked()
{
    setDuration(duration() + 60);
}

void DurationWidget::on_minus1minButton_clicked()
{
    setDuration(duration() - 60);
}

void DurationWidget::on_plus30SecondButton_clicked()
{
    setDuration(duration() + 30);
}

void DurationWidget::on_minus30SecondsButton_clicked()
{
    setDuration(duration() - 30);
}

void DurationWidget::on_plus1SecondButton_clicked()
{
    setDuration(duration() + 1);
}

void DurationWidget::on_minus1SecondButton_clicked()
{
    setDuration(duration() - 1);
}
