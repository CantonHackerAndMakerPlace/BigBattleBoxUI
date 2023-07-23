#include "applicationstate.h"

ApplicationState::ApplicationState(QObject *parent)
    : QObject{parent}
    , m_screen(new Screen(this))
    , m_model(new BattleBoxViewModel(this))
    , m_physicalState(new BattleBoxPhysicalState(this))
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
                m_physicalState->connectionManager()->sendData("Status");
            });

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

Screen *ApplicationState::screen() const {
    return m_screen;
}

BattleBoxViewModel *ApplicationState::data() const {
    return m_model;
}

BattleBoxPhysicalState *ApplicationState::physicalState() const {
    return m_physicalState;
}
