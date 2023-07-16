#include "configurationwidget.h"
#include "ui_configurationwidget.h"
#include "stateindicatorwidget.h"
#include <QDebug>
#include <QDateTime>
#include "mediadialog.h"

ConfigurationWidget::ConfigurationWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ConfigurationWidget)
    , m_settings(nullptr)
    , m_state(nullptr)
    , m_media(nullptr)
{
    ui->setupUi(this);

    // Connecting the back button the so we can emit a
    // signal to leave the configuration screen.
    connect(ui->backButton, &QPushButton::clicked,
            this, &ConfigurationWidget::clickedBack);
}

ConfigurationWidget::~ConfigurationWidget() {
    delete ui;
}

void ConfigurationWidget::init(QSettings *settings, BattleBoxPhysicalState *physicalState, MediaDialog *media) {
    // Loading all of the current configuratation
    assert(!m_settings && "Cannot call init twice");
    assert(!m_state && "Cannot call init twice");
    assert(!m_media && "Cannot initialize media dialog reference twice");

    m_settings = settings;
    m_state = physicalState;
    m_media = media;

    // Connecting all of the signals and for each sub-menu.
    initPlayerOneConfig();
    initPlayerTwoConfig();
    initLedConfig();
    initSpotLightConfig();
    initArduinoConfig();
    initMediaDialog();
}


void ConfigurationWidget::initPlayerOneConfig() {
    connectButtonState(m_state->playerOne()->readyButton(),
        ui->p1StatusIndicator->readyState());

    connectButtonState(m_state->playerOne()->doorButton(),
        ui->p1StatusIndicator->doorState());

    connectButtonState(m_state->playerOne()->trapDoorButton(),
        ui->p1StatusIndicator->trapDoorState());

    connectButtonState(m_state->playerOne()->conceedButton(),
        ui->p1StatusIndicator->conceedState());

    connectWiringState(m_state->playerOne()->readyButton(), ui->p1ReadySwitchKind);
    connectWiringState(m_state->playerOne()->doorButton(), ui->p1DoorSwitchKind);
    connectWiringState(m_state->playerOne()->conceedButton(), ui->p1ConceedSwitchKind);
    connectWiringState(m_state->playerOne()->trapDoorButton(), ui->p1TrapDoorSwitchKind);
}

void ConfigurationWidget::initPlayerTwoConfig() {
    connectButtonState(m_state->playerTwo()->readyButton(),
        ui->p2StatusIndicator->readyState());

    connectButtonState(m_state->playerTwo()->doorButton(),
        ui->p2StatusIndicator->doorState());

    connectButtonState(m_state->playerTwo()->trapDoorButton(),
        ui->p2StatusIndicator->trapDoorState());

    connectButtonState(m_state->playerTwo()->conceedButton(),
        ui->p2StatusIndicator->conceedState());

    connectWiringState(m_state->playerTwo()->readyButton(), ui->p2ReadySwitchKind);
    connectWiringState(m_state->playerTwo()->doorButton(), ui->p2DoorSwitchKind);
    connectWiringState(m_state->playerTwo()->conceedButton(), ui->p2ConceedSwitchKind);
    connectWiringState(m_state->playerTwo()->trapDoorButton(), ui->p2TrapDoorSwitchKind);
}

void ConfigurationWidget::initLedConfig() {

}

void ConfigurationWidget::initSpotLightConfig() {

}
constexpr size_t LOG_LINES = 1000;
void ConfigurationWidget::initArduinoConfig() {
    ui->arduinoConnectionIndicator->setState(m_state->connectionManager()->isConnected());
    connect(m_state->connectionManager(), &ArduinoConnectionManager::connected,
            [&](QString port) {
        ui->arduinoConnectionIndicator->setState(m_state->connectionManager()->isConnected());
        ui->availableComPorts->setCurrentText(port);
    });

    connect(m_state->connectionManager(), &ArduinoConnectionManager::disconnected,
            [&](QString port) {
        ui->arduinoConnectionIndicator->setState(m_state->connectionManager()->isConnected());
        ui->availableComPorts->setCurrentText("");
    });

    // Adding initial empty elements.
    ui->availableComPorts->addItem("");
    ui->availableComPorts->addItems(m_state->connectionManager()->availableSerialPorts());

    connect(m_state->connectionManager(), &ArduinoConnectionManager::availableSerialPortsChanged,
            [&](const QStringList &ports) {
        auto text = ui->availableComPorts->currentText();
        ui->availableComPorts->clear();
        ui->availableComPorts->addItem("");
        ui->availableComPorts->addItems(m_state->connectionManager()->availableSerialPorts());
        ui->availableComPorts->setCurrentText(text);
    });

    connect(m_state->connectionManager(), &ArduinoConnectionManager::error,
            [&](QString msg){
        // Update state because this could me we are disconnected.
        ui->arduinoConnectionIndicator->setState(m_state->connectionManager()->isConnected());
        qDebug() << "Received an error message from arduino connection";
    });

    // Making sure to update connected serial port values from the selection.
    connect(ui->availableComPorts, &QComboBox::currentTextChanged,
            [&](const QString& text) {
        // The remainder of the state will be updated by the rest of
        // the slots.
        m_state->connectionManager()->connectToSerialPort(text);
        qDebug() << "Selecting new arduino connection:" << text;
        m_settings->setValue("arduino/com_port", text);

    });

    connect(m_state->connectionManager(), &ArduinoConnectionManager::connectToSerialPort,
            ui->availableComPorts, &QComboBox::currentTextChanged);

    connect(m_state->connectionManager(), &ArduinoConnectionManager::receivedData,
            [&](QString msg) {
        QString cleanMsg = msg.remove('\r').remove('\n');

        // Add things to the QTableWidget
        QDateTime now = QDateTime::currentDateTime();
        ui->arduinoTextLog->appendPlainText("[" + now.toString(Qt::ISODate) +"]" + cleanMsg);
        auto newlines = ui->arduinoTextLog->toPlainText().count('\n');
        if (newlines > LOG_LINES) {
            QTextCursor cursor = ui->arduinoTextLog->textCursor();
            cursor.movePosition(QTextCursor::Start);
            cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, newlines - LOG_LINES);
            cursor.select(QTextCursor::LineUnderCursor);
            cursor.removeSelectedText();
            cursor.deleteChar(); // Delete old stuff
            cursor.movePosition(QTextCursor::End);
            ui->arduinoTextLog->setTextCursor(cursor);
        }
    });
}

void ConfigurationWidget::initMediaDialog() {
    connect(ui->showCannonButton, &QPushButton::pressed,
            [&]{
                m_media->showWinnerScreen("cannon/main.qml", ui->winningPlayerNameInpuit->text());
            });
    connect(ui->showPlayerWinsButton, &QPushButton::pressed,
            [&]{
                m_media->showWinnerScreen("confetti/main.qml", ui->winningPlayerNameInpuit->text());
            });

    connect(ui->restoreMediaScreen, &QPushButton::pressed,
            [&]{
                m_media->show();
            });
}

void ConfigurationWidget::connectButtonState(PhysicalButton *sw, StateIndicatorWidget *indicator) {
    // Set the initial state.
    indicator->setState(sw->state());
    connect(sw, &PhysicalButton::stateChanged,
            indicator, &StateIndicatorWidget::setState);
}

void ConfigurationWidget::connectWiringState(PhysicalButton *sw, ButtonConfigWidget *wiringCfg) {
    wiringCfg->setSwitchKind(sw->switchKind());
    connect(sw, &PhysicalButton::switchKindChanged,
            wiringCfg, &ButtonConfigWidget::setSwitchKind);
    connect(wiringCfg, &ButtonConfigWidget::switchKindChanged,
            sw, &PhysicalButton::setSwitchKind);
}
