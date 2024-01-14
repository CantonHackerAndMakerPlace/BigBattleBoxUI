#include "playersreadywidget.h"
#include "ui_playersreadywidget.h"

template<typename T>
void PlayersReadyWidget::listenForChanges(T* uiElement) {
    // Connecting to the changes were made signal.
    connect(uiElement, &T::valueChanged,
            this, &PlayersReadyWidget::changesWereMade);
    // Connecting to value operations.
    connect(this, &PlayersReadyWidget::restorePreviousValue,
            uiElement, &T::restorePreviousValue);
    connect(this, &PlayersReadyWidget::restoreDefaultValue,
            uiElement, &T::restoreDefaultValue);
    connect(this, &PlayersReadyWidget::save,
            uiElement, &T::save);
}

PlayersReadyWidget::PlayersReadyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayersReadyWidget)
{
    ui->setupUi(this);
    connect(ui->blinkOnNoLongerReady, &DefaultRestorableCheckBox::valueChanged,
            ui->groupBox, &QGroupBox::setEnabled);
    ui->blinkOnNoLongerReady->setValue(false);
    ui->blinkOnNoLongerReady->setValue(true);

    // Connecting buttons.
    connect(ui->cancelButton, &QPushButton::clicked,
            this, &PlayersReadyWidget::restorePreviousValue);
    connect(ui->saveButton, &QPushButton::clicked,
            this, &PlayersReadyWidget::save);
    connect(ui->defaultButton, &QPushButton::clicked,
            this, &PlayersReadyWidget::restoreDefaultValue);

    listenForChanges(ui->p1ReadyColor);
    listenForChanges(ui->p1ReadyBrightness);
    listenForChanges(ui->p1NotReadyColor);
    listenForChanges(ui->p1NotReadyBrightness);
    listenForChanges(ui->p2ReadyColor);
    listenForChanges(ui->p2ReadyBrightness);
    listenForChanges(ui->p2NotReadyColor);
    listenForChanges(ui->p2NotReadyBrightness);
    listenForChanges(ui->blinkOnNoLongerReady);
    listenForChanges(ui->numberOfBlinks);
    listenForChanges(ui->onDuration);
    listenForChanges(ui->offDuration);
    listenForChanges(ui->p1OnColor);
    listenForChanges(ui->p1OnBrightness);
    listenForChanges(ui->p1OffColor);
    listenForChanges(ui->p1OffBrightness);
    listenForChanges(ui->p2OnColor);
    listenForChanges(ui->p2OnBrightness);
    listenForChanges(ui->p2OffColor);
    listenForChanges(ui->p2OffBrightness);
}

PlayersReadyWidget::~PlayersReadyWidget() {
    delete ui;
}

bool PlayersReadyWidget::hasChanges() const {
    return ui->p1ReadyColor->hasChanges() ||
           ui->p1ReadyBrightness->hasChanges() ||
           ui->p1NotReadyColor->hasChanges() ||
           ui->p1NotReadyBrightness->hasChanges() ||

           ui->p2ReadyColor->hasChanges() ||
           ui->p2ReadyBrightness->hasChanges() ||
           ui->p2NotReadyColor->hasChanges() ||
           ui->p2NotReadyBrightness->hasChanges() ||

           ui->blinkOnNoLongerReady->hasChanges() ||
           ui->numberOfBlinks->hasChanges() ||
           ui->onDuration->hasChanges() ||
           ui->offDuration->hasChanges() ||

           ui->p1OnColor->hasChanges() ||
           ui->p1OnBrightness->hasChanges() ||
           ui->p1OffColor->hasChanges() ||
           ui->p1OffBrightness->hasChanges() ||

           ui->p2OnColor->hasChanges() ||
           ui->p2OnBrightness->hasChanges() ||
           ui->p2OffColor->hasChanges() ||
           ui->p2OffBrightness->hasChanges();

}

QString PlayersReadyWidget::title() const {
    return ui->titleWidget->text();
}

void PlayersReadyWidget::init(PlayerReadyLEDLightConfiguration *config) {
    assert(!m_config && "cannot be initialzied twice");
    m_config = config;
    ui->blinkOnNoLongerReady->init(&m_config->blinkOnCancel());
    ui->numberOfBlinks->init(&m_config->numberOfBlinks());
    ui->onDuration->init(&m_config->onDuration());
    ui->offDuration->init(&m_config->offDuration());

    ui->p1ReadyColor->init(&m_config->p1ReadyColor());
    ui->p1ReadyBrightness->init(&m_config->p1ReadyBrightness());
    ui->p1NotReadyColor->init(&m_config->p1NotReadyColor());
    ui->p1NotReadyBrightness->init(&m_config->p1NotReadyBrightness());

    ui->p1OnColor->init(&m_config->p1BlinkOnColor());
    ui->p1OnBrightness->init(&m_config->p1BlinkOnBrightness());
    ui->p1OffColor->init(&m_config->p1BlinkOffColor());
    ui->p1OffBrightness->init(&m_config->p1BlinkOffBrightness());

    ui->p2ReadyColor->init(&m_config->p2ReadyColor());
    ui->p2ReadyBrightness->init(&m_config->p2ReadyBrightness());
    ui->p2NotReadyColor->init(&m_config->p2NotReadyColor());
    ui->p2NotReadyBrightness->init(&m_config->p2NotReadyBrightness());

    ui->p2OnColor->init(&m_config->p2BlinkOnColor());
    ui->p2OnBrightness->init(&m_config->p2BlinkOnBrightness());
    ui->p2OffColor->init(&m_config->p2BlinkOffColor());
    ui->p2OffBrightness->init(&m_config->p2BlinkOffBrightness());
}


void PlayersReadyWidget::setTitle(QString value) {
    if (ui->titleWidget->text() != value) {
        ui->titleWidget->setText(value);
        emit titleChanged(value);
    }
}
