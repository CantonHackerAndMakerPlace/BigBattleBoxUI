#include "generalledconfigurationwidget.h"
#include "ui_generalledconfigurationwidget.h"
#include <app_state/applicationstate.h>
#include <QButtonGroup>

GeneralLEDConfigurationWidget::GeneralLEDConfigurationWidget(QWidget *parent)
    :QWidget(parent)
    , ui(new Ui::GeneralLEDConfigurationWidget)
    , m_p1Direction(new QButtonGroup(this))
    , m_p2Direction(new QButtonGroup(this))
    , m_ledOrderGroup(new QButtonGroup(this))
    , m_state(nullptr)
    , m_generalConfig(nullptr)
    , m_p1Pin(12)
    , m_p1LEDCount(100)
    , m_p1DirSelection(0)
    , m_p2Pin(13)
    , m_p2LEDCount(100)
    , m_p2DirSelection(1)
    , m_order(0)
{
    ui->setupUi(this);

    // Player One direction radio button group
    m_p1Direction->addButton(ui->p1ForwardRadioButton, 0);
    m_p1Direction->addButton(ui->p1BackwardRadioButton, 1);
    m_p1Direction->setExclusive(true);

    // Player Two buttons
    m_p2Direction->addButton(ui->p2ForwardRadioButton, 0);
    m_p2Direction->addButton(ui->p2BackwardRadioButton, 1);
    m_p2Direction->setExclusive(true);

    // Configuring the LED Ordering either player one first or player two first.
    m_ledOrderGroup->addButton(ui->startingSidePlayerOneRadioButton, 0);
    m_ledOrderGroup->addButton(ui->startingSidePlayerTwoRadioButton, 1);
    m_ledOrderGroup->setExclusive(true);

    attachButtonGroup(&m_order, m_ledOrderGroup);

    // General buttons connections.
    connect(ui->saveButton, &QPushButton::clicked,
            this, &GeneralLEDConfigurationWidget::save);
    connect(ui->revertToDefaultButton, &QPushButton::clicked,
            this, &GeneralLEDConfigurationWidget::revertToDefault);
    connect(ui->cancelButton, &QPushButton::clicked,
            this, &GeneralLEDConfigurationWidget::cancel);

    // Attaching player values
    attachPlayerOne();
    attachPlayerTwo();

}

GeneralLEDConfigurationWidget::~GeneralLEDConfigurationWidget() {
    delete ui;
}

bool GeneralLEDConfigurationWidget::hasChanges() const {
    return m_p1Pin.hasChange() || m_p1LEDCount.hasChange() ||
        m_p1DirSelection.hasChange() || m_p2Pin.hasChange() ||
        m_p2LEDCount.hasChange() || m_p2DirSelection.hasChange() ||
        m_order.hasChange();
}

void GeneralLEDConfigurationWidget::attachPlayerOneAppState() {
    connectAppState(&m_p1Pin, &m_generalConfig->playerOneLedPin());
    connectAppState(&m_p1LEDCount, &m_generalConfig->playerOneLedCount());
    connectAppState(&m_p1DirSelection, &m_generalConfig->playerOneLedDirection());
}


void GeneralLEDConfigurationWidget::attachPlayerTwoAppState() {
    connectAppState(&m_p2Pin, &m_generalConfig->playerTwoLedPin());
    connectAppState(&m_p2LEDCount, &m_generalConfig->playerTwoLedCount());
    connectAppState(&m_p2DirSelection, &m_generalConfig->playerTwoLedDirection());
}

void GeneralLEDConfigurationWidget::connectAppState(DefaultRestorableInt *localValue, IntegerObject* configuredValue) {
    connect(configuredValue, &IntegerObject::valueChanged,
            localValue, &DefaultRestorableInt::setCurrentAndPreviousValue);
    localValue->setCurrentAndPreviousValue(configuredValue->value());
}

void GeneralLEDConfigurationWidget::init(ApplicationState *state) {
    // TODO: Make sure to load/save default values into the state so we can
    // keep them around.
    assert(!m_state && !m_generalConfig);
    m_state = state;
    m_generalConfig = m_state->ledConfig()->generalLEDConfiguration();

    // Connecting players with internal application state.
    attachPlayerOneAppState();
    attachPlayerTwoAppState();

    // Connecting LED order with internal state.
    connectAppState(&m_order, &m_generalConfig->lightOrder());
}

void GeneralLEDConfigurationWidget::save() {
    // Saving all values into the configuration
    m_generalConfig->playerOneLedPin().setValue(m_p1Pin.value());
    m_generalConfig->playerOneLedCount().setValue(m_p1LEDCount.value());
    m_generalConfig->playerOneLedDirection().setValue(m_p1DirSelection.value());
    m_generalConfig->playerTwoLedPin().setValue(m_p2Pin.value());
    m_generalConfig->playerTwoLedCount().setValue(m_p2LEDCount.value());
    m_generalConfig->playerTwoLedDirection().setValue(m_p2DirSelection.value());
    m_generalConfig->lightOrder().setValue(m_order.value());
}

void GeneralLEDConfigurationWidget::cancel() {
    m_p1Pin.restorePreviousValue();
    m_p1LEDCount.restorePreviousValue();
    m_p1DirSelection.restorePreviousValue();
    m_p2Pin.restorePreviousValue();
    m_p2LEDCount.restorePreviousValue();
    m_p2DirSelection.restorePreviousValue();
    m_order.restorePreviousValue();
}

void GeneralLEDConfigurationWidget::revertToDefault() {
    m_p1Pin.restoreDefaultValue();
    m_p1LEDCount.restoreDefaultValue();
    m_p1DirSelection.restoreDefaultValue();
    m_p2Pin.restoreDefaultValue();
    m_p2LEDCount.restoreDefaultValue();
    m_p2DirSelection.restoreDefaultValue();
    m_order.restoreDefaultValue();
}

void GeneralLEDConfigurationWidget::attachSpinBox(DefaultRestorableInt *localValue, QSpinBox *sb) {
    connect(sb, &QSpinBox::valueChanged,
           localValue, &DefaultRestorableInt::setValue);
    connect(localValue, &DefaultRestorableInt::valueChanged,
            sb, &QSpinBox::setValue);
    sb->setValue(localValue->value());
}

void toggleRadioButtonInGroup(QButtonGroup *bg, int id) {
    auto button = bg->button(id);
    if (!button) {
        qDebug() << "Failed to locate button with id:" << id;
        return;
    }
    // Activate the radio button.
    auto radio_button = qobject_cast<QRadioButton*>(button);
    radio_button->setChecked(true);
}

void GeneralLEDConfigurationWidget::attachButtonGroup(DefaultRestorableInt *localValue, QButtonGroup *bg) {
    connect(bg, &QButtonGroup::idToggled,
            [=](int id, bool selected) {
                if (selected) {
                    localValue->setValue(id);
                }
            });
    connect(localValue, &DefaultRestorableInt::valueChanged,
            [=](int id) {
                toggleRadioButtonInGroup(bg, id);
            }
        );
    toggleRadioButtonInGroup(bg, localValue->value());
}

void GeneralLEDConfigurationWidget::attachPlayerOne() {
    // Setting up a bidirectional connection for the spinbox.
    attachSpinBox(&m_p1Pin, ui->p1ArduinoPinSpinBox);
    attachSpinBox(&m_p1LEDCount, ui->p1LEDCountInput);
    attachButtonGroup(&m_p1DirSelection, m_p1Direction);
}

void GeneralLEDConfigurationWidget::attachPlayerTwo() {
    attachSpinBox(&m_p2Pin, ui->p2ArduinoPinSpinBox);
    attachSpinBox(&m_p2LEDCount, ui->p2LEDCountInput);
    attachButtonGroup(&m_p2DirSelection, m_p2Direction);
}
