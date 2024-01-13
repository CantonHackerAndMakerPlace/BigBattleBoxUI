#include "idleledconfigurationwidget.h"
#include "ui_idleledconfigurationwidget.h"



IdleLedConfigurationWidget::IdleLedConfigurationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IdleLedConfigurationWidget)

{
    ui->setupUi(this);

    // Connecting buttons.
    connect(ui->saveButton, &QPushButton::clicked,
            this, &IdleLedConfigurationWidget::save);

    connectToControlButtons(ui->algorithmSelector);
    connectToControlButtons(ui->breathPage);
    connectToControlButtons(ui->countDownPage);
    connectToControlButtons(ui->cylonPage);
    connectToControlButtons(ui->solidColorPage);
    connectToControlButtons(ui->blinkPage);
    connectToControlButtons(ui->rampUpPage);


    connect(ui->defaultButton, &QPushButton::clicked,
            this, &IdleLedConfigurationWidget::revertToDefault);
    connect(ui->cancelButton, &QPushButton::clicked,
            this, &IdleLedConfigurationWidget::cancel);

    // Connecting changes in the the drop down to the changes
    // inside of the current dropdown
    connect(ui->algorithmSelector, &AlgorithmDropDown::algorithmChanged,
            this, &IdleLedConfigurationWidget::setCurrentConfigPage);

    // Setting the current page the the selected page.
    setCurrentConfigPage(ui->algorithmSelector->getCurrentAlgorithm().value());
}

template<typename T>
void IdleLedConfigurationWidget::connectToControlButtons(T *page) {
    connect(ui->cancelButton, &QPushButton::clicked, page, &T::restorePreviousValue);
    connect(ui->defaultButton, &QPushButton::clicked, page, &T::restoreDefaultValue);
    connect(ui->saveButton, &QPushButton::clicked, page, &T::save);
}

void IdleLedConfigurationWidget::setCurrentConfigPage(AlgoKindObject::AlgoKind kind) {
    switch(kind) {
    case AlgoKindObject::AlgoKind::Off:
        ui->configDisplayStack->setCurrentWidget(ui->offPage);
        break;
    case AlgoKindObject::AlgoKind::Blink:
        ui->configDisplayStack->setCurrentWidget(ui->blinkPage);
        break;
    case AlgoKindObject::AlgoKind::Breath:
        ui->configDisplayStack->setCurrentWidget(ui->breathPage);
        break;
    case AlgoKindObject::AlgoKind::CountDown:
        ui->configDisplayStack->setCurrentWidget(ui->countDownPage);
        break;
    case AlgoKindObject::AlgoKind::Cylon:
        ui->configDisplayStack->setCurrentWidget(ui->cylonPage);
        break;
    case AlgoKindObject::AlgoKind::RampUp:
        ui->configDisplayStack->setCurrentWidget(ui->rampUpPage);
        break;
    case AlgoKindObject::AlgoKind::Solid:
        ui->configDisplayStack->setCurrentWidget(ui->solidColorPage);
        break;
    default:
        qWarning() << "Received incorrect screen change";
    }
}

IdleLedConfigurationWidget::~IdleLedConfigurationWidget() {
    delete ui;
}

void IdleLedConfigurationWidget::init(LEDAlgoConfig *state) {
    assert(!m_config && "Can't initialize twice");
    m_config = state;
    ui->algorithmSelector->init(&m_config->getAlgoKind());
    ui->breathPage->init(m_config->getBreath());
    ui->countDownPage->init(m_config->getCountDownFill());
    ui->cylonPage->init(m_config->getCylonConfig());
    ui->solidColorPage->init(m_config->getSolidColorConfig());
    ui->blinkPage->init(m_config->getBlink());
    ui->rampUpPage->init(m_config->getRampUpConfig());
}

bool IdleLedConfigurationWidget::hasChanges() const {
    return ui->algorithmSelector->hasChanges()
           || ui->breathPage->hasChanges()
           || ui->countDownPage->hasChanges()
           || ui->cylonPage->hasChanges()
           || ui->solidColorPage->hasChanges();
}

QString IdleLedConfigurationWidget::title(){
    return ui->titleLabel->text();
}

void IdleLedConfigurationWidget::save() { }

void IdleLedConfigurationWidget::cancel() { }

void IdleLedConfigurationWidget::revertToDefault() { }

void IdleLedConfigurationWidget::setTitle(QString value) {
    if (ui->titleLabel->text() != value) {
        ui->titleLabel->setText(value);
        emit titleChanged(value);
    }
}
