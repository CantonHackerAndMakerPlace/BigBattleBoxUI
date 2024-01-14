#include "solidcolorpage.h"
#include "ui_solidcolorpage.h"

SolidColorPage::SolidColorPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SolidColorPage)
{
    ui->setupUi(this);
    connect(ui->cancelButton, &QPushButton::clicked,
            this, &SolidColorPage::restorePreviousValue);
    connect(ui->saveButton, &QPushButton::clicked,
            this, &SolidColorPage::save);
    connect(ui->defaultButton, &QPushButton::clicked,
            this, &SolidColorPage::restoreDefaultValue);
}

SolidColorPage::~SolidColorPage()
{
    delete ui;
}

bool SolidColorPage::hasChanges() const {
    return ui->solidColor->hasChanges();
}

QString SolidColorPage::title() const {
    return ui->titleWidget->text();
}

void SolidColorPage::init(SolidColorConfig *config) {
    ui->solidColor->init(config);
}

void SolidColorPage::restorePreviousValue() {
    ui->solidColor->restorePreviousValue();
}

void SolidColorPage::restoreDefaultValue() {
    ui->solidColor->restoreDefaultValue();
}

void SolidColorPage::save() {
    ui->solidColor->save();
}

void SolidColorPage::setTitle(QString value) {
    if (ui->titleWidget->text() != value) {
        ui->titleWidget->setText(value);
        emit titleChanged(value);
    }
}
