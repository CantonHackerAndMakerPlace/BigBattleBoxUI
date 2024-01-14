#include "countdownpage.h"
#include "ui_countdownpage.h"

CountDownPage::CountDownPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CountDownPage)
{
    ui->setupUi(this);

    connect(ui->cancelButton, &QPushButton::clicked,
            this, &CountDownPage::restorePreviousValue);
    connect(ui->saveButton, &QPushButton::clicked,
            this, &CountDownPage::save);
    connect(ui->defaultButton, &QPushButton::clicked,
            this, &CountDownPage::restoreDefaultValue);

    // TODO: Connect the changesWereMade signal to the enable/disable of
    // the buttons.
}

CountDownPage::~CountDownPage()
{
    delete ui;
}

bool CountDownPage::hasChanges() const {
    return ui->countDown->hasChanges();
}

QString CountDownPage::title() const {
    return ui->titleWidget->text();
}

void CountDownPage::init(CountDownFillConfig *config) {
    ui->countDown->init(config);
}

void CountDownPage::restorePreviousValue() {
    ui->countDown->restorePreviousValue();
}

void CountDownPage::restoreDefaultValue() {
    ui->countDown->restoreDefaultValue();
}

void CountDownPage::save() {
    ui->countDown->save();
}

void CountDownPage::setTitle(QString value) {
    if (ui->titleWidget->text() != value) {
        ui->titleWidget->setText(value);
        emit titleChanged(value);
    }
}
