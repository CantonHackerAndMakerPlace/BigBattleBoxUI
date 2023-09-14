#include "applicationstate.h"

ApplicationState::ApplicationState(QObject *parent)
    : QObject{parent}
    , m_screen(new Screen(this))
    , m_model(new BattleBoxViewModel(this))
    , m_physicalState(new BattleBoxPhysicalState(this))
    , m_ledConfig(new LEDConfiguration(this))
    , m_arduinoClient(new ArduinoClient(m_ledConfig->generalLEDConfiguration(), m_physicalState->messanger(), this))
    , m_ledController(new LEDController(m_arduinoClient, this))
{
    initSettings();
    initBattleBoxState();
}

void ApplicationState::initSettings() {
    m_model->loadSettings();

    // player one settings
    attachSettingToSwitch(m_physicalState->playerOne()->readyButton(), "player_one/ready_switch_kind");
    attachSettingToSwitch(m_physicalState->playerOne()->doorButton(), "player_one/door_switch_kind");
    attachSettingToSwitch(m_physicalState->playerOne()->trapDoorButton(), "player_one/trap_door_switch_kind");
    attachSettingToSwitch(m_physicalState->playerOne()->conceedButton(), "player_one/conceed_switch_kind");

    // Player two settings
    attachSettingToSwitch(m_physicalState->playerTwo()->readyButton(), "player_two/ready_switch_kind");
    attachSettingToSwitch(m_physicalState->playerTwo()->doorButton(), "player_two/door_switch_kind");
    attachSettingToSwitch(m_physicalState->playerTwo()->trapDoorButton(), "player_two/trap_door_switch_kind");
    attachSettingToSwitch(m_physicalState->playerTwo()->conceedButton(), "player_two/conceed_switch_kind");

    // Attaching the LED light settings.
    m_ledConfig->loadSettings(m_model->settings());

    // Sync settings on disk
    m_model->saveSettings();
}

void ApplicationState::attachSettingToSwitch(PhysicalButton *button, const char* settingsKey) {
    using PBSwitchConfig = PhysicalButton::SwitchConfig;
    auto loadedSetting = intToSwitchConfig(data()->settings()->value(settingsKey, (int)PhysicalButton::SwitchConfig::NormallyClosed).value<int>());
    connect(button, &PhysicalButton::switchKindChanged,
            [=](PBSwitchConfig kind){
                qDebug() << "Called save setting change for " << settingsKey;
                data()->settings()->setValue(settingsKey, (int)kind);
                data()->saveSettings();
            });
    if (loadedSetting.has_value()) {
        button->setSwitchKind(loadedSetting.value());
        data()->settings()->setValue(settingsKey, (int)loadedSetting.value());
    }
}

void ApplicationState::initBattleBoxState() {
    connect(m_physicalState->connectionManager(), &ArduinoConnectionManager::connected,
            [&] {
                qDebug() << "Connected serial port";
            });

    connect(m_arduinoClient, &ArduinoClient::connected,
            [&] {
        // NOTE: Sending reconfiguration messages directly is best I think?
        qDebug() << "Arduino ready for send and receive sending configuration messages";

        }
    );

    // TODO: Eventuall move this into the PhyiscalState Class.
    connect(m_physicalState->connectionManager(), &ArduinoConnectionManager::disconnected,
            [] {
                qDebug() << "disconnected from serial port";
            });

    connect(m_physicalState->connectionManager(), &ArduinoConnectionManager::error,
            [](QString msg) {
                qDebug() << "Serial port error occurred: " << msg;
            });

    connect(m_physicalState->connectionManager(), &ArduinoConnectionManager::error,
            [](QString msg) {
                qDebug() << "Serial port error occurred: " << msg;
            });

    connect(m_physicalState->connectionManager(), &ArduinoConnectionManager::availableSerialPortsChanged,
            [](QStringList msg) {
                qDebug() << "Received new serial ports" << msg;
            });
    auto port = m_model->settings()->value("arduino/com_port", "/dev/ttyACM0").toString();
    m_physicalState->connectionManager()->connectToSerialPort(port);
}

void ApplicationState::onArduinoConnection() {
    qDebug() << "Called onArduinoConnection";

    // When we connect to the arduino we must send the LED
    // configuration settings

}

LEDConfiguration *ApplicationState::ledConfig() const {
    return m_ledConfig;
}

Screen *ApplicationState::screen() const {
    return m_screen;
}

BattleBoxViewModel *ApplicationState::data() const {
    return m_model;
}

BattleBoxPhysicalState *ApplicationState::physicalState() const {
    return m_physicalState;
}


LEDController *ApplicationState::ledController() const {
    return m_ledController;
}
