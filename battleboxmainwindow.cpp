#include "battleboxmainwindow.h"
#include "./ui_battleboxmainwindow.h"
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QFileDialog>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QFileSystemWatcher>
#include <QVariant>
#include <iostream>

#include "mediadialog.h"
#include "battleboxviewmodel.h"
#include "deathmatchconfig.h"
#include "battleboxphysicalstate.h"
#include "configurationwidget.h"

// sudo chmod a+rw /dev/ttyACM0

static const char *GREEN_BG_STYLE_SHEET = "background-color:green;";
static const char *RED_BG_STYLE_SHEET = "background-color:red;";
static const char *DEATHMATCH_QUICK_LOAD_FOLDER = "/home/battlbox/DeathMatchConfig";
static const char *SOCCER_QUICK_LOAD_FOLDER = "/home/battlbox/SoccerConfig";

BattleBoxMainWindow::BattleBoxMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BattleBoxMainWindow)
    , m_boxState(new BattleBoxPhysicalState(this))
    , m_data(new BattleBoxViewModel(this))
    , m_dmcdAnimationGroup(new QSequentialAnimationGroup(this))
    , m_scdAnimationGroup(new QSequentialAnimationGroup(this))
    , m_currentScreen(Screen::InitialLoad)
    , m_dirWatcher(new QFileSystemWatcher(this))
    , m_mediaScreen(new MediaDialog(m_data, this))
{
    ui->setupUi(this);
    initSettings();
//    this->showMaximized();

    initBattleBoxState();

    initializeSystemConfigurationScreen();

    initMediaDialog();

    // Quick load widgets
    initQuickSelectWidgets();

    // Game selection
    initGameSelectScreen();

    // DeathMatch
    initDeathMatchConfigScreen();
    initDeathMatchPlayersReadyScreen();
    initDeathMatchCountDownScreen();
    initDeathMatchRunningScreen();
    initDeathMatchWinnerScreen();

    // Soccer
    initSoccerConfigScreen();
    initSoccerPlayersReadyScreen();
    initSoccerCountDownScreen();
    initSoccerRunningScreen();
    initSoccerGameOverScreen();

    // Setting the current scren.
    setCurrentScreen(Screen::GameSelectionScreen);

    m_data->saveSettings();
}

BattleBoxMainWindow::~BattleBoxMainWindow() {
    delete ui;
}

DeathMatchConfig *BattleBoxMainWindow::deathMatchConfig() const {
    return m_data->deathMatchConfig();
}

void BattleBoxMainWindow::initSettings() {
    m_data->loadSettings();

    // player one settings
    attachSettingToSwitch(m_boxState->playerOne()->readyButton(), "player_one/ready_switch_kind");
    attachSettingToSwitch(m_boxState->playerOne()->doorButton(), "player_one/door_switch_kind");
    attachSettingToSwitch(m_boxState->playerOne()->trapDoorButton(), "player_one/trap_door_switch_kind");
    attachSettingToSwitch(m_boxState->playerOne()->conceedButton(), "player_one/conceed_switch_kind");

    // Player two settings
    attachSettingToSwitch(m_boxState->playerTwo()->readyButton(), "player_two/ready_switch_kind");
    attachSettingToSwitch(m_boxState->playerTwo()->doorButton(), "player_two/door_switch_kind");
    attachSettingToSwitch(m_boxState->playerTwo()->trapDoorButton(), "player_two/trap_door_switch_kind");
    attachSettingToSwitch(m_boxState->playerTwo()->conceedButton(), "player_two/conceed_switch_kind");


    // Creating deathmatch default values
//    int m_matchDuration;
//    int m_doorDropTime;
//    QString m_playerOneName;
//    QString m_playerTwoName;
//    DoorDrop m_doorDropKind;

//    toString
//     Deathmatch initial configurations
//    m_data->loadSettings();
//    auto settings = m_data->settings();
//    settings->beginGroup("DeathMatchDefaults");
//    settings->setValue("MatchDuration", 180);
//    settings->setValue("DoorDropTime", 120);
//    m_data->settings()->setValue("DoorDropKind", int(DeathMatchConfig::DoorDrop::Random));
//    settings->setValue("PlayerOneName", "");
//    settings->setValue("PlayerTwoName", "");
//    settings->endGroup();

//    settings->beginGroup("DeathMatchDefaults");
    m_data->saveSettings();
}

void BattleBoxMainWindow::attachSettingToSwitch(PhysicalButton *button, const char* settingsKey) {
    using PBSwitchConfig = PhysicalButton::SwitchConfig;
    auto loadedSetting = intToSwitchConfig(m_data->settings()->value(settingsKey, (int)PhysicalButton::SwitchConfig::NormallyClosed).value<int>());
    connect(button, &PhysicalButton::switchKindChanged,
            [=](PBSwitchConfig kind){
        qDebug() << "Called save setting change for " << settingsKey;
        m_data->settings()->setValue(settingsKey, (int)kind);
        m_data->saveSettings();
    });
    if (loadedSetting.has_value()) {
        button->setSwitchKind(loadedSetting.value());
        m_data->settings()->setValue(settingsKey, (int)loadedSetting.value());
    }
}

void BattleBoxMainWindow::initBattleBoxState() {

    connect(m_boxState->connectionManager(), &ArduinoConnectionManager::connected,
            [] {
        qDebug() << "Connected serial port";
    });

    connect(m_boxState->connectionManager(), &ArduinoConnectionManager::disconnected,
            [] {
        qDebug() << "disconnected from serial port";
    });

    connect(m_boxState->connectionManager(), &ArduinoConnectionManager::disconnected,
            [] {
        qDebug() << "disconnected from serial port";
    });

    connect(m_boxState->connectionManager(), &ArduinoConnectionManager::error,
            [](QString msg) {
        qDebug() << "Serial port error occurred: " << msg;
    });

    connect(m_boxState->connectionManager(), &ArduinoConnectionManager::error,
            [](QString msg) {
        qDebug() << "Serial port error occurred: " << msg;
    });

    connect(m_boxState->connectionManager(), &ArduinoConnectionManager::availableSerialPortsChanged,
            [](QStringList msg) {
        qDebug() << "Received new serial ports" << msg;
    });
    auto port = m_data->settings()->value("arduino/com_port", "/dev/ttyACM0").toString();
    m_boxState->connectionManager()->connectToSerialPort(port);

    // TODO: Load things from settings into the box state or move that code
    // into the box state itself.
}

void BattleBoxMainWindow::initializeSystemConfigurationScreen() {
    // Configure the system configuration screen. This may require
    // things like back buttons, and access to the current data
    connect(ui->configuration, &ConfigurationWidget::clickedBack,
            [&] { setCurrentScreen(Screen::GameSelectionScreen); });
    ui->configuration->init(m_data->settings(), m_boxState);
}


void BattleBoxMainWindow::initMediaDialog() {
    m_mediaScreen->setModal(false);
    m_mediaScreen->show();
    //    m_mediaScreen->showFullScreen();
}


void BattleBoxMainWindow::initGameSelectScreen() {
    // Slot Connections.
    connect(ui->dmConfigButton, &QPushButton::clicked,
            [&] { setCurrentScreen(Screen::DMConfigScreen); });
    connect(ui->soccerConfigButton, &QPushButton::clicked,
            [&] { setCurrentScreen(Screen::SoccerConfigScreen); });
    connect(ui->systemConfigurationButton, &QPushButton::clicked,
            [&] { setCurrentScreen(Screen::ConfigurationScreen); });
}

void BattleBoxMainWindow::initQuickSelectWidgets() {
    // Setting up directory watcher for quick loading for both
    // death match and soccer.
    connect(m_dirWatcher, &QFileSystemWatcher::directoryChanged,
            this, &BattleBoxMainWindow::updateQuickLoadFiles);

    m_dirWatcher->addPath(DEATHMATCH_QUICK_LOAD_FOLDER);
    loadQuickLoadFiles(DEATHMATCH_QUICK_LOAD_FOLDER);
    m_dirWatcher->addPath(SOCCER_QUICK_LOAD_FOLDER);
    loadQuickLoadFiles(SOCCER_QUICK_LOAD_FOLDER);
}

void BattleBoxMainWindow::initDeathMatchConfigScreen() {
    // Death match configuration screen slots

    // Other slot
    connect(ui->dmCfgSaveButton, &QPushButton::clicked,
            this, &BattleBoxMainWindow::on_dmCfgSaveButton_clicked);
    connect(ui->dmCfgLoadButton, &QPushButton::clicked,
            this, &BattleBoxMainWindow::on_dmCfgLoadButton_clicked);

    connect(ui->dmStart, &QPushButton::clicked,
            [&] { setCurrentScreen(Screen::DMPlayersReadyScreen); });
    connect(ui->dmCancel, &QPushButton::clicked,
            [&] { setCurrentScreen(Screen::GameSelectionScreen); });
    connect(ui->dmCfgReset, &QPushButton::clicked,
            m_data, &BattleBoxViewModel::resetDeathMatchConfig);

    // Setting up bidirectional connections between the deathmatch configuration
    // and the configuration screen.

    // Connecting player one name edit
    ui->playerOneNameLineEdit->setText(m_data->deathMatchConfig()->playerOneName());
    connect(ui->playerOneNameLineEdit, &QLineEdit::textChanged,
            m_data->deathMatchConfig(), &DeathMatchConfig::setPlayerOneName);
    connect(m_data->deathMatchConfig(), &DeathMatchConfig::playerOneNameChanged,
            ui->playerOneNameLineEdit, &QLineEdit::setText);

    // Connecting player two name edit
    ui->playerTwoNameLineEdit->setText(m_data->deathMatchConfig()->playerTwoName());
    connect(ui->playerTwoNameLineEdit, &QLineEdit::textChanged,
            m_data->deathMatchConfig(), &DeathMatchConfig::setPlayerTwoName);
    connect(m_data->deathMatchConfig(), &DeathMatchConfig::playerTwoNameChanged,
            ui->playerTwoNameLineEdit, &QLineEdit::setText);

    // Connecting match duration widget
    ui->matchDurationWidget->setDuration(m_data->deathMatchConfig()->matchDuration());
    connect(ui->matchDurationWidget, &DurationWidget::durationChanged,
            m_data->deathMatchConfig(), &DeathMatchConfig::setMatchDuration);
    connect(m_data->deathMatchConfig(), &DeathMatchConfig::matchDurationChanged,
            ui->matchDurationWidget, &DurationWidget::setDuration);

    // Connecting door drop time duration widget
    ui->doorDropTimeWidget->setDuration(m_data->deathMatchConfig()->doorDropTime());
    connect(ui->doorDropTimeWidget, &DurationWidget::durationChanged,
            m_data->deathMatchConfig(), &DeathMatchConfig::setDoorDropTime);
    connect(m_data->deathMatchConfig(), &DeathMatchConfig::doorDropChanged,
            ui->doorDropTimeWidget, &DurationWidget::setDuration);

    // Connecting drop down with kind
    ui->doorDropKindComboBox->setCurrentIndex((int)m_data->deathMatchConfig()->doorDropKind());
    connect(ui->doorDropKindComboBox, &QComboBox::currentIndexChanged,
            m_data->deathMatchConfig(), &DeathMatchConfig::setDoorDropKindFromInt);
    connect(m_data->deathMatchConfig(), &DeathMatchConfig::doorDropKindChangedInt,
            ui->doorDropKindComboBox, &QComboBox::setCurrentIndex);

    // Connecting quick load slot
    connect(ui->dmQuickLoadButton, &QPushButton::clicked,
            [&] {
        auto items = ui->dmQuickLoadListWidget->selectedItems();
        if(items.size() != 1) {
            return;
        }
        QString path = DEATHMATCH_QUICK_LOAD_FOLDER + QString("/") + items[0]->text();
        this->m_data->deathMatchConfig()->loadFromFile(path);
    });

    // Error signal connection.
    connect(this->m_data->deathMatchConfig(), &DeathMatchConfig::error,
            this, &BattleBoxMainWindow::receivedError);

    // Configuring default values
    m_data->deathMatchConfig()->setMatchDuration(180);
    m_data->deathMatchConfig()->setDoorDropTime(60);
}

void BattleBoxMainWindow::initDeathMatchPlayersReadyScreen() {
    // Connecting buttons.
    connect(ui->dmprPlayerOneReadyButton, &QPushButton::clicked,
            [&] { m_data->deathMatchPlayerOneReady()->setPlayerReady(true); });
    connect(ui->dmprPlayerTwoReadyButton, &QPushButton::clicked,
            [&] { m_data->deathMatchPlayerTwoReady()->setPlayerReady(true); });

    // Screen changing buttons
    connect(ui->dmprStart, &QPushButton::clicked,
            [&] { setCurrentScreen(Screen::DMCountDownScreen); });
    connect(ui->dmprCancel, &QPushButton::clicked,
            [&] { setCurrentScreen(Screen::DMConfigScreen); });

    connect(m_data->deathMatchPlayerOneReady(), &DeathMatchPlayerReadyModel::readyTextChanged,
            this, &BattleBoxMainWindow::dmprUpdateP1ReadyText);
    connect(m_data->deathMatchPlayerTwoReady(), &DeathMatchPlayerReadyModel::readyTextChanged,
            this, &BattleBoxMainWindow::dmprUpdateP2ReadyText);

    connect(m_data->deathMatchPlayerOneReady(), &DeathMatchPlayerReadyModel::doorTextChanged,
            this, &BattleBoxMainWindow::dmprUpdateP1DoorText);
    connect(m_data->deathMatchPlayerTwoReady(), &DeathMatchPlayerReadyModel::doorTextChanged,
            this, &BattleBoxMainWindow::dmprUpdateP2DoorText);

    // Connecting the door not closed indicator to player ready indicator.
    connect(this->m_data->deathMatchPlayerOneReady(), &DeathMatchPlayerReadyModel::doorNotClosed,
            this, &BattleBoxMainWindow::receivedError);
    connect(this->m_data->deathMatchPlayerTwoReady(), &DeathMatchPlayerReadyModel::doorNotClosed,
            this, &BattleBoxMainWindow::receivedError);
}

void BattleBoxMainWindow::initDeathMatchCountDownScreen() {

    QGraphicsOpacityEffect *eff1 = new QGraphicsOpacityEffect(ui->dmCDCountDownLabel);
    ui->dmCDCountDownLabel->setGraphicsEffect(eff1);
    {
        QPropertyAnimation *a = new QPropertyAnimation(eff1, "opacity");
        a->setDuration(1000);
        a->setStartValue(0);
        a->setEndValue(1);
        a->setEasingCurve(QEasingCurve::InBack);
        connect(a, &QPropertyAnimation::stateChanged,
                [&](QAbstractAnimation::State newState, QAbstractAnimation::State) {
            if(newState == QAbstractAnimation::State::Running) {
                qDebug() << "Emitting DMCDStart3";
                emit DMCDstart3();
                qDebug() << "Finished Emitting DMCDStart3";
                ui->dmCDCountDownLabel->setText("3");
            }
        });
        m_dmcdAnimationGroup->addAnimation(a);
    }
    {
        QPropertyAnimation *a = new QPropertyAnimation(eff1, "opacity");
        a->setDuration(1000);
        a->setStartValue(0);
        a->setEndValue(1);
        a->setEasingCurve(QEasingCurve::InBack);
        connect(a, &QPropertyAnimation::stateChanged,
                [&](QAbstractAnimation::State newState, QAbstractAnimation::State) {
            if(newState == QAbstractAnimation::State::Running) {
                emit DMCDstart2();
                ui->dmCDCountDownLabel->setText("2");
            }
        });
        m_dmcdAnimationGroup->addAnimation(a);
    }
    {
        QPropertyAnimation *a = new QPropertyAnimation(eff1, "opacity");
        a->setDuration(1000);
        a->setStartValue(0);
        a->setEndValue(1);
        a->setEasingCurve(QEasingCurve::InBack);
        connect(a, &QPropertyAnimation::stateChanged,
                [&](QAbstractAnimation::State newState, QAbstractAnimation::State) {
            if(newState == QAbstractAnimation::State::Running) {
                emit DMCDstart1();
                ui->dmCDCountDownLabel->setText("1");
            }
        });
        m_dmcdAnimationGroup->addAnimation(a);
    }
    {
        QPropertyAnimation *a = new QPropertyAnimation(eff1, "opacity");
        a->setDuration(1000);
        a->setStartValue(0);
        a->setEndValue(1);
        a->setEasingCurve(QEasingCurve::InBack);
        connect(a, &QPropertyAnimation::stateChanged,
                [&](QAbstractAnimation::State newState, QAbstractAnimation::State) {
            if(newState == QAbstractAnimation::State::Running) {
                emit DMCDstartFight();
                ui->dmCDCountDownLabel->setText("FIGHT!!!");
            }
        });
        m_dmcdAnimationGroup->addAnimation(a);
    }
    // Connecting final part of the animation signal
    connect(m_dmcdAnimationGroup, &QSequentialAnimationGroup::finished,
            [&] { setCurrentScreen(Screen::DMRunningScreen); });

    // Connecting cancel.
    connect(ui->dmcdCancel, &QPushButton::clicked,
            [&]{ setCurrentScreen(Screen::DMConfigScreen); });

}

void BattleBoxMainWindow::initDeathMatchRunningScreen() {
    ui->dmrCountDownWidget->setup(deathMatchConfig());

    // Configuring buttons
    connect(ui->dmrPlayerOneWinsButton, &QPushButton::clicked,
            [&] {
        if(m_data->deathMatchConfig()->playerOneName() == "") {
            m_data->setDeathMatchWinner("Player One");
        } else {
            m_data->setDeathMatchWinner(m_data->deathMatchConfig()->playerOneName());
        }
        this->setCurrentScreen(Screen::DMWinnerDisplayScreen);
    });
    connect(ui->dmrPlayerTwoWinsButton, &QPushButton::clicked,
            [&] {
        if(m_data->deathMatchConfig()->playerTwoName() == "") {
            m_data->setDeathMatchWinner("Player Two");
        } else {
            m_data->setDeathMatchWinner(m_data->deathMatchConfig()->playerTwoName());
        }
        this->setCurrentScreen(Screen::DMWinnerDisplayScreen);
    });
    // Naviaging buttons
    connect(ui->dmrBackToDMConfigButton, &QPushButton::clicked,
            [&] { setCurrentScreen(Screen::DMConfigScreen); });
    connect(ui->dmrRestartMatchButton, &QPushButton::clicked,
            [&] { setCurrentScreen(Screen::DMPlayersReadyScreen); });
    connect(ui->dmrCancel, &QPushButton::clicked,
            [&] { setCurrentScreen(Screen::GameSelectionScreen); });

    // Changes the displayed widget to the one I want.
//    connect(ui->dmrCountDownWidget, &DeathMatchRunningClockWidget::matchOver,
//            [&] { ui->srStackedWidget->setCurrentWidget(ui->srMatchOverWidget); });

}

void BattleBoxMainWindow::initDeathMatchWinnerScreen() {
    connect(ui->dmwRestartButton, &QPushButton::clicked,
            [&] { setCurrentScreen(Screen::DMPlayersReadyScreen); });
    connect(ui->dmwToDMCButton, &QPushButton::clicked,
            [&] { setCurrentScreen(Screen::DMConfigScreen); });
    connect(ui->dmwToGameSelectButton, &QPushButton::clicked,
            [&] { setCurrentScreen(Screen::GameSelectionScreen); });
    connect(m_data, &BattleBoxViewModel::notifyDeathMatchWinnerChanged,
            [&](QString arg) {
        ui->dmWinnerDisplayLabel->setText(QString("%1\nWINS!!").arg(arg));
    });

}

void BattleBoxMainWindow::initSoccerConfigScreen() {
    // Configuring buttons
    connect(ui->soccerCfgStartButton, &QPushButton::clicked,
            [&] { setCurrentScreen(Screen::SoccerPlayersReadyScreen); });
    connect(ui->soccerCfgCancelButton, &QPushButton::clicked,
            [&] { setCurrentScreen(Screen::GameSelectionScreen); });

    connect(ui->soccerCfgResetButton, &QPushButton::clicked,
            m_data, &BattleBoxViewModel::resetSoccerConfig);

    connect(ui->soccerCfgSaveFileButton, &QPushButton::clicked,
            this, &BattleBoxMainWindow::on_soccerCfgSaveButton_clicked);
    connect(ui->soccerCfgOpenFileButton, &QPushButton::clicked,
            this, &BattleBoxMainWindow::on_soccerCfgLoadButton_clicked);

    // Connecting team one name edit
    ui->soccerCfgTeamOneNameLineEdit->setText(m_data->soccerConfig()->teamOneName());
    connect(ui->soccerCfgTeamOneNameLineEdit, &QLineEdit::textChanged,
            m_data->soccerConfig(), &SoccerConfig::setTeamOneName);
    connect(m_data->soccerConfig(), &SoccerConfig::notifyTeamOneNameChanged,
            ui->soccerCfgTeamOneNameLineEdit, &QLineEdit::setText);

    // Connecting team two name edit
    ui->soccerCfgTeamTwoNameLineEdit->setText(m_data->soccerConfig()->teamTwoName());
    connect(ui->soccerCfgTeamTwoNameLineEdit, &QLineEdit::textChanged,
            m_data->soccerConfig(), &SoccerConfig::setTeamTwoName);
    connect(m_data->soccerConfig(), &SoccerConfig::notifyTeamTwoNameChanged,
            ui->soccerCfgTeamTwoNameLineEdit, &QLineEdit::setText);

    // Connecting match duration widget
    ui->soccerCfgMatchDurationWidget->setDuration(m_data->soccerConfig()->matchDuration());
    connect(ui->soccerCfgMatchDurationWidget, &DurationWidget::durationChanged,
            m_data->soccerConfig(), &SoccerConfig::setMatchDuration);
    connect(m_data->soccerConfig(), &SoccerConfig::notifyMatchDurationChanged,
            ui->soccerCfgMatchDurationWidget, &DurationWidget::setDuration);

    // Connecting match score
    ui->soccerCfgGameScoreSpinBox->setValue(m_data->soccerConfig()->maxScore());
    connect(ui->soccerCfgGameScoreSpinBox, &QSpinBox::valueChanged,
            m_data->soccerConfig(), &SoccerConfig::setMaxScore);
    connect(m_data->soccerConfig(), &SoccerConfig::notifyMaxScoreChanged,
            ui->soccerCfgGameScoreSpinBox, &QSpinBox::setValue);

    // Error signal connection.
    connect(this->m_data->soccerConfig(), &SoccerConfig::error,
            this, &BattleBoxMainWindow::receivedError);

    // Connecting quick load slot
    connect(ui->soccerCfgQuickLoadButton, &QPushButton::clicked,
            [&] {
        auto items = ui->soccerCfgQuickLoadListWidget->selectedItems();
        if(items.size() != 1) {
            return;
        }
        QString path = SOCCER_QUICK_LOAD_FOLDER + QString("/") + items[0]->text();
        this->m_data->soccerConfig()->loadFromFile(path);

    });

}

void BattleBoxMainWindow::initSoccerPlayersReadyScreen() {

    // Soccer players ready screen
    connect(ui->sprStartButton, &QPushButton::clicked,
            [&] { setCurrentScreen(Screen::SoccerCountDownScreen); });
    connect(ui->sprCancelButton, &QPushButton::clicked,
            [&] { setCurrentScreen(Screen::SoccerConfigScreen); });

    connect(ui->sprTeamOneReadyButton, &QPushButton::clicked,
            [&] { m_data->soccerTeamOneReady()->setTeamReady(true); });
    connect(ui->sprTeamTwoReadyButton, &QPushButton::clicked,
            [&] { m_data->soccerTeamTwoReady()->setTeamReady(true); });

    // Screen changing buttons
    connect(m_data->soccerTeamOneReady(), &SoccerTeamReady::readyTextChanged,
            this, &BattleBoxMainWindow::sprUpdateT1ReadyText);
    connect(m_data->soccerTeamTwoReady(), &SoccerTeamReady::readyTextChanged,
            this, &BattleBoxMainWindow::sprUpdateT2ReadyText);
}

void BattleBoxMainWindow::initSoccerCountDownScreen() {
    QGraphicsOpacityEffect *eff1 = new QGraphicsOpacityEffect(ui->scdLabel);
    ui->scdLabel->setGraphicsEffect(eff1);
    // TODO: consider emitting signals from here.
    {
        QPropertyAnimation *a = new QPropertyAnimation(eff1, "opacity");
        a->setDuration(1000);
        a->setStartValue(0);
        a->setEndValue(1);
        a->setEasingCurve(QEasingCurve::InBack);
        connect(a, &QPropertyAnimation::stateChanged,
                [&](QAbstractAnimation::State newState, QAbstractAnimation::State) {
            if(newState == QAbstractAnimation::State::Running) {
                ui->scdLabel->setText("3");
            }
        });
        m_scdAnimationGroup->addAnimation(a);
    }
    {
        QPropertyAnimation *a = new QPropertyAnimation(eff1, "opacity");
        a->setDuration(1000);
        a->setStartValue(0);
        a->setEndValue(1);
        a->setEasingCurve(QEasingCurve::InBack);
        connect(a, &QPropertyAnimation::stateChanged,
                [&](QAbstractAnimation::State newState, QAbstractAnimation::State) {
            if(newState == QAbstractAnimation::State::Running) {
                ui->scdLabel->setText("2");
            }
        });
        m_scdAnimationGroup->addAnimation(a);
    }
    {
        QPropertyAnimation *a = new QPropertyAnimation(eff1, "opacity");
        a->setDuration(1000);
        a->setStartValue(0);
        a->setEndValue(1);
        a->setEasingCurve(QEasingCurve::InBack);
        connect(a, &QPropertyAnimation::stateChanged,
                [&](QAbstractAnimation::State newState, QAbstractAnimation::State) {
            if(newState == QAbstractAnimation::State::Running) {
                ui->scdLabel->setText("1");
            }
        });
        m_scdAnimationGroup->addAnimation(a);
    }
    {
        QPropertyAnimation *a = new QPropertyAnimation(eff1, "opacity");
        a->setDuration(1000);
        a->setStartValue(0);
        a->setEndValue(1);
        a->setEasingCurve(QEasingCurve::InBack);
        connect(a, &QPropertyAnimation::stateChanged,
                [&](QAbstractAnimation::State newState, QAbstractAnimation::State) {
            if(newState == QAbstractAnimation::State::Running) {
                ui->scdLabel->setText("GO!!!");
            }
        });
        m_scdAnimationGroup->addAnimation(a);
    }
    // Connecting final part of the animation signal
    connect(m_scdAnimationGroup, &QSequentialAnimationGroup::finished,
            [&] { setCurrentScreen(Screen::SoccerRunningScreen); });

    // Connecting cancel.
    connect(ui->scdCancelButton, &QPushButton::clicked,
            [&]{ setCurrentScreen(Screen::SoccerConfigScreen); });
}

void BattleBoxMainWindow::initSoccerRunningScreen() {
    ui->srRunningWidget->setup(m_data->soccerMatch());

    // Connecting the resume button.
    connect(ui->srResumeButton, &QPushButton::clicked,
            [&] {
        ui->srStackedWidget->setCurrentWidget(ui->srResumeCountDownWidget);
        ui->srResumeCountDownWidget->start();
        ui->srResumeButton->setEnabled(false);
    });

    connect(ui->srMatchEndsInDrawButton, &QPushButton::clicked,
            [&] {
        qDebug() << "Trigger draw";
    });

    connect(ui->srT1GoalButton, &QPushButton::clicked,
            [&] {
        ui->srRunningWidget->pause();
        ui->srGoalScoredLabel->setText("Team One scorred a goal with " + msToTimeRep(ui->srRunningWidget->remainingMS()) +  "s remaining");
        ui->srResumeButton->setEnabled(true);
        ui->srStackedWidget->setCurrentWidget(ui->srGoalScoredWidget);
        if(m_data->soccerMatch()->teamOneScore() >= 1000) {
            m_data->soccerMatch()->setTeamOneScore(1000);
        } else {
            m_data->soccerMatch()->setTeamOneScore(m_data->soccerMatch()->teamOneScore() + 1);
        }
    });


    connect(ui->srTeamOneWinsButton, &QPushButton::clicked,
            [&] {

    });


    connect(ui->srT1ScorePlusOneButton, &QPushButton::clicked,
            [&] {
        if(m_data->soccerMatch()->teamOneScore() >= 1000) {
            m_data->soccerMatch()->setTeamOneScore(1000);
        } else {
            m_data->soccerMatch()->setTeamOneScore(m_data->soccerMatch()->teamOneScore() + 1);
        }
    });

    connect(ui->srT1ScoreMinusOneButton, &QPushButton::clicked,
            [&] {
        if(m_data->soccerMatch()->teamOneScore() <= 0) {
            m_data->soccerMatch()->setTeamOneScore(0);
        } else {
            m_data->soccerMatch()->setTeamOneScore(m_data->soccerMatch()->teamOneScore() - 1);
        }
    });


    connect(ui->srTeamTwoWinsButton, &QPushButton::clicked,
            [&] {
        qDebug() << "Team two wins!";

    });


    connect(ui->srT2GoalButton, &QPushButton::clicked,
            [&] {
        ui->srRunningWidget->pause();
        ui->srGoalScoredLabel->setText("Team Two scorred a goal with " + msToTimeRep(ui->srRunningWidget->remainingMS()) +  "s remaining");
        ui->srResumeButton->setEnabled(true);
        ui->srStackedWidget->setCurrentWidget(ui->srGoalScoredWidget);
        if(m_data->soccerMatch()->teamTwoScore() >= 1000) {
            m_data->soccerMatch()->setTeamTwoScore(1000);
        } else {
            m_data->soccerMatch()->setTeamTwoScore(m_data->soccerMatch()->teamTwoScore() + 1);
        }
    });


    connect(ui->srT2ScorePlusOneButton, &QPushButton::clicked,
            [&] {
        if(m_data->soccerMatch()->teamTwoScore() >= 1000) {
            m_data->soccerMatch()->setTeamTwoScore(1000);
        } else {
            m_data->soccerMatch()->setTeamTwoScore(m_data->soccerMatch()->teamTwoScore() + 1);
        }
    });

    connect(ui->srT2ScoreMinusOneButton, &QPushButton::clicked,
            [&] {
        if(m_data->soccerMatch()->teamTwoScore() <= 0) {
            m_data->soccerMatch()->setTeamTwoScore(0);
        } else {
            m_data->soccerMatch()->setTeamTwoScore(m_data->soccerMatch()->teamTwoScore() - 1);
        }
    });

    // Naviaging buttons
    connect(ui->srRestartMatchButton,  &QPushButton::clicked,
            [&] { setCurrentScreen(Screen::SoccerPlayersReadyScreen); });
    connect(ui->srCancelGameSelectionButton, &QPushButton::clicked,
            [&] { setCurrentScreen(Screen::GameSelectionScreen); });
    connect(ui->srCancelConfigButton, &QPushButton::clicked,
            [&] { setCurrentScreen(Screen::SoccerConfigScreen); });

    // Binding the reumed button.
    connect(ui->srResumeCountDownWidget, &SoccerResumeCountDownWidget::resumed,
            [&] {
        ui->srStackedWidget->setCurrentWidget(ui->srRunningWidget);
        ui->srRunningWidget->resume();
        ui->srResumeButton->setEnabled(false);
    });
    connect(ui->srRunningWidget, &SoccerRunningClockWidget::gameOver,
            [&] {
        ui->srRunningWidget->stop();
        ui->srStackedWidget->setCurrentWidget(ui->srGameOverWidget);
    });
}

void BattleBoxMainWindow::initSoccerGameOverScreen() {

}

void BattleBoxMainWindow::changeScreen(BattleBoxMainWindow::Screen newPage,
                                       BattleBoxMainWindow::Screen oldPage) {
    // Leaving signals.
    switch(oldPage) {
    // Do nothing here.
    case InitialLoad: break;
    case ConfigurationScreen:
        emit leaveConfigurationScreen();
        break;

    case GameSelectionScreen:
        emit leaveGameSelectScreen();
        break;

    case DMConfigScreen:
        emit leaveDMConfigScreen();
        break;

    case DMCountDownScreen:
        qDebug() << "Leaving DMCountDownScreen";
        m_dmcdAnimationGroup->stop();
        emit leaveDMCountDownScreen();
        break;

    case DMPlayersReadyScreen:
        emit leaveDMPlayersReadyScreen();
        break;

    case DMRunningScreen:
        ui->dmrCountDownWidget->stop();
        emit leaveDMRunningScreen();
        break;

    case DMWinnerDisplayScreen:
        emit leaveDMWinnerDisplayScreen();
        break;

    case SoccerConfigScreen:
        emit leaveSoccerConfigScreen();
        break;

    case SoccerPlayersReadyScreen:
        emit leaveSoccerPlayersReadyScreen();
        break;

    case SoccerRunningScreen:
        ui->srResumeCountDownWidget->cancel();
        ui->srRunningWidget->stop();
        emit leaveSoccerRunningScreen();
        break;

    case SoccerGameOverScreen:
        emit leaveSoccerGameOverScreen();
        break;

    case SoccerCountDownScreen:
        m_scdAnimationGroup->stop();
        emit leaveSoccerCountDownScreen();
        break;
    }

    // Enter signals.
    switch(newPage) {
    // Do nothing because we can never enter this screen.
    case InitialLoad: break;

    case ConfigurationScreen:
        ui->mainDisplay->setCurrentWidget(ui->configuration);
        emit enterConfigurationScreen();
        break;

    case GameSelectionScreen:
        ui->mainDisplay->setCurrentWidget(ui->gameSelection);
        emit enterGameSelectScreen();
        break;

    case DMConfigScreen:
        ui->mainDisplay->setCurrentWidget(ui->deathMatchConfig);
        emit enterDMConfigScreen();
        break;

    case DMCountDownScreen:
        qDebug() << "Entering DMCountDownScreen";
        ui->mainDisplay->setCurrentWidget(ui->deathMatchCountDown);
        emit enterDMCountDownScreen();
        m_dmcdAnimationGroup->start();

        break;

    case DMPlayersReadyScreen:
        m_data->deathMatchPlayerOneReady()->reset();
        m_data->deathMatchPlayerTwoReady()->reset();
        // FIXME: remove this eventually!
        // m_data->deathMatchPlayerOneReady()->setDoorClosed(true);
        // m_data->deathMatchPlayerTwoReady()->setDoorClosed(true);
        ui->mainDisplay->setCurrentWidget(ui->deathMatchPlayersReady);
        emit enterDMPlayersReadyScreen();
        break;

    case DMRunningScreen:
        ui->mainDisplay->setCurrentWidget(ui->deathMatchRunning);
        ui->dmrStackedWidget->setCurrentWidget(ui->dmrCountDownWidget);
        ui->dmrCountDownWidget->start();
        emit enterDMRunningScreen();
        break;

    case DMWinnerDisplayScreen:
        ui->mainDisplay->setCurrentWidget(ui->deathMatchWinner);
        emit enterDMWinnerDisplayScreen(m_data->deathMatchWinner());
        break;

    case SoccerConfigScreen:
        ui->mainDisplay->setCurrentWidget(ui->soccerConfig);
        emit enterSoccerConfigScreen();
        break;

    case SoccerPlayersReadyScreen:
        m_data->resetSoccerTeamOneReady();
        m_data->resetSoccerTeamTwoReady();
        ui->mainDisplay->setCurrentWidget(ui->soccerPlayersReady);
        emit enterSoccerPlayersReadyScreen();
        break;

    case SoccerRunningScreen:
        // Loading new soccer match data
        m_data->soccerMatch()->loadSoccerConfig(m_data->soccerConfig());
        ui->srStackedWidget->setCurrentWidget(ui->srRunningWidget);
        ui->mainDisplay->setCurrentWidget(ui->soccerRunning);
        ui->srRunningWidget->start();
        ui->srResumeButton->setEnabled(false);
        emit enterSoccerRunningScreen();
        break;

    case SoccerGameOverScreen:
        ui->mainDisplay->setCurrentWidget(ui->soccerGameOver);
        emit enterSoccerGameOverScreen();
        break;

    case SoccerCountDownScreen:
        ui->mainDisplay->setCurrentWidget(ui->soccerCountDown);
        m_scdAnimationGroup->start();
        emit enterSoccerCountDownScreen();
        break;
    }
}

void BattleBoxMainWindow::loadQuickLoadFiles(QString dir) {
    QDir directory(dir);
    auto files = directory.entryList();
    QListWidget *toLoad;
    if (dir == DEATHMATCH_QUICK_LOAD_FOLDER) {
        toLoad = ui->dmQuickLoadListWidget;
    } else if(dir == SOCCER_QUICK_LOAD_FOLDER) {
        toLoad = ui->soccerCfgQuickLoadListWidget;
    } else {
        qWarning() << "Received an unknown directory " << dir <<"\n";
        return;
    }
    toLoad->clear();
    for(auto &f : files) {
        if(f.startsWith(".")) {
            continue;
        }
        toLoad->addItem(f);
    }
}

auto BattleBoxMainWindow::currentScreen() const -> Screen {
    return m_currentScreen;
}

void BattleBoxMainWindow::setCurrentScreen(Screen newScreen) {
    if(newScreen != currentScreen()) {
        std::swap(m_currentScreen, newScreen);
        changeScreen(currentScreen(), newScreen);
    }
}

void BattleBoxMainWindow::on_dmCfgSaveButton_clicked() {
    auto fileName = QFileDialog::getSaveFileName(
        this,
        tr("Open File"),
        DEATHMATCH_QUICK_LOAD_FOLDER,
        tr("Json Files (*.json)"));
    this->m_data->deathMatchConfig()->saveToFile(fileName);
}

void BattleBoxMainWindow::on_dmCfgLoadButton_clicked() {
    auto fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        DEATHMATCH_QUICK_LOAD_FOLDER,
        tr("Json Files (*.json)"));
    this->m_data->deathMatchConfig()->loadFromFile(fileName);
}

void BattleBoxMainWindow::receivedError(QString msg) {
    std::cout << "Received error message: " << msg.toStdString() << std::endl;
}

void BattleBoxMainWindow::dmprUpdateP1ReadyText(QString arg) {
    ui->dmprPlayerOneReadyLabel->setText(QString("Player One: %1").arg(arg));
    if(m_data->deathMatchPlayerOneReady()->playerReady()) {
        ui->dmprPlayerOneReadyWidget->setStyleSheet(GREEN_BG_STYLE_SHEET);
    } else {
        ui->dmprPlayerOneReadyWidget->setStyleSheet(RED_BG_STYLE_SHEET);
    }
}

void BattleBoxMainWindow::dmprUpdateP2ReadyText(QString arg) {
    ui->dmprPlayerTwoReadyLabel->setText(QString("Player Two: %1").arg(arg));
    if(m_data->deathMatchPlayerTwoReady()->playerReady()) {
        ui->dmprPlayerTwoReadyWidget->setStyleSheet(GREEN_BG_STYLE_SHEET);
    } else {
        ui->dmprPlayerTwoReadyWidget->setStyleSheet(RED_BG_STYLE_SHEET);
    }
}

void BattleBoxMainWindow::dmprUpdateP1DoorText(QString arg) {
    ui->dmprPlayerOneDoorIndicatorLabel->setText(QString("Door: %1").arg(arg));
    if(m_data->deathMatchPlayerOneReady()->doorClosed()) {
        ui->dmprPlayerOneDoorWidget->setStyleSheet(GREEN_BG_STYLE_SHEET);
    } else {
        ui->dmprPlayerOneDoorWidget->setStyleSheet(RED_BG_STYLE_SHEET);
    }
}

void BattleBoxMainWindow::dmprUpdateP2DoorText(QString arg) {
    ui->dmprPlayerTwoDoorIndicatorLabel->setText(QString("Door: %1").arg(arg));
    if(m_data->deathMatchPlayerTwoReady()->doorClosed()) {
        ui->dmprPlayerTwoDoorWidget->setStyleSheet(GREEN_BG_STYLE_SHEET);
    } else {
        ui->dmprPlayerTwoDoorWidget->setStyleSheet(RED_BG_STYLE_SHEET);
    }
}

void BattleBoxMainWindow::updateQuickLoadFiles(QString dir) {
    loadQuickLoadFiles(dir);
}

void BattleBoxMainWindow::on_soccerCfgSaveButton_clicked() {
    auto fileName = QFileDialog::getSaveFileName(
        this,
        tr("Open File"),
        SOCCER_QUICK_LOAD_FOLDER,
        tr("Json Files (*.json)"));
    m_data->soccerConfig()->saveToFile(fileName);
}

void BattleBoxMainWindow::on_soccerCfgLoadButton_clicked() {
    auto fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        SOCCER_QUICK_LOAD_FOLDER,
        tr("Json Files (*.json)"));
    m_data->soccerConfig()->loadFromFile(fileName);
}

void BattleBoxMainWindow::sprUpdateT1ReadyText(QString arg) {
    ui->sprTeamOneReadyLabel->setText(QString("Team One: %1").arg(arg));
    if(m_data->soccerTeamOneReady()->teamReady()) {
        ui->sprTeamOneReadyLabel->setStyleSheet(GREEN_BG_STYLE_SHEET);
    } else {
        ui->sprTeamOneReadyLabel->setStyleSheet(RED_BG_STYLE_SHEET);
    }
}

void BattleBoxMainWindow::sprUpdateT2ReadyText(QString arg) {
    ui->sprTeamTwoReadyLabel->setText(QString("Team Two: %1").arg(arg));
    if(m_data->soccerTeamTwoReady()->teamReady()) {
        ui->sprTeamTwoReadyLabel->setStyleSheet(GREEN_BG_STYLE_SHEET);
    } else {
        ui->sprTeamTwoReadyLabel->setStyleSheet(RED_BG_STYLE_SHEET);
    }
}
