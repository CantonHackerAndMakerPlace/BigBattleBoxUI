#include "rampuppage.h"
#include "ui_rampuppage.h"

RampUpPage::RampUpPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RampUpPage)
{
    ui->setupUi(this);
    connect(ui->cancelButton, &QPushButton::clicked,
            this, &RampUpPage::restorePreviousValue);
    connect(ui->saveButton, &QPushButton::clicked,
            this, &RampUpPage::save);
    connect(ui->defaultButton, &QPushButton::clicked,
            this, &RampUpPage::restoreDefaultValue);
}

RampUpPage::~RampUpPage()
{
    delete ui;
}

bool RampUpPage::hasChanges() const {
    return ui->rampUp->hasChanges();
}

QString RampUpPage::title() const {
    return ui->titleWidget->text();
}

void RampUpPage::init(RampUpConfig *config) {
    ui->rampUp->init(config);
}

void RampUpPage::restorePreviousValue() {
    ui->rampUp->restorePreviousValue();
}

void RampUpPage::restoreDefaultValue() {
    ui->rampUp->restoreDefaultValue();
}

void RampUpPage::save() {
    ui->rampUp->save();
}

void RampUpPage::setTitle(QString value) {
    if (ui->titleWidget->text() != value) {
        ui->titleWidget->setText(value);
        emit titleChanged(value);
    }
}
