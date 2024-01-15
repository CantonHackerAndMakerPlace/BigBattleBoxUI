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
#include "app_state/deathmatchconfig.h"
#include "app_state/applicationstate.h"
#include "configurationwidget.h"
#include "app_state/screen.h"

// sudo chmod a+rw /dev/ttyACM0

static const char *GREEN_BG_STYLE_SHEET = "background-color:green;";
static const char *RED_BG_STYLE_SHEET = "background-color:red;";
static const char *DEATHMATCH_QUICK_LOAD_FOLDER = "/home/battlbox/DeathMatchConfig";
static const char *SOCCER_QUICK_LOAD_FOLDER = "/home/battlbox/SoccerConfig";

BattleBoxMainWindow::BattleBoxMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BattleBoxMainWindow)
    , m_state(new ApplicationState(this))
    , m_dmcdAnimationGroup(new QSequentialAnimationGroup(this))
    , m_scdAnimationGroup(new QSequentialAnimationGroup(this))
    , m_dirWatcher(new QFileSystemWatcher(this))
    , m_mediaScreen(new MediaDialog(m_state, this))
{
    ui->setupUi(this);
    connectScreenSlots();
    m_mediaScreen->loadSettingsDependentResources();

    initializeSystemConfigurationScreen();

    initMediaDialog();

    // Quick load widgets
    initQuickSelectWidgets();

    // Game selection
    initGameSelectScreen();

    // Connecting all signals to the LED controller.
    initLEDController();

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
    m_state->screen()->changeToGameSelectScreen();

    m_state->data()->saveSettings();
}

void BattleBoxMainWindow::closeEvent(QCloseEvent *event) {
    qDebug() << "Received a close event!";
    m_state->physicalState()->connectionManager()->consumeUntilQuiet(1000);
    m_state->physicalState()->connectionManager()->blockingSendData("LEDAllSetBrightness 0");
    m_state->physicalState()->connectionManager()->blockingSendData("LEDAllShow");
    QMainWindow::closeEvent(event);
}

BattleBoxMainWindow::~BattleBoxMainWindow() {
    delete ui;
}

DeathMatchConfig *BattleBoxMainWindow::deathMatchConfig() const {
    return m_state->data()->deathMatchConfig();
}

void BattleBoxMainWindow::connectScreenSlots() {
#define SCREEN_CONNECT(NAME)\
    connect(m_state->screen(), &Screen::NAME,\
            this, &BattleBoxMainWindow::NAME);
    SCREEN_CONNECT(enterConfigurationScreen);
    SCREEN_CONNECT(leaveConfigurationScreen);

    SCREEN_CONNECT(enterGameSelectScreen);
    SCREEN_CONNECT(leaveGameSelectScreen);

    SCREEN_CONNECT(enterDMConfigScreen);
    SCREEN_CONNECT(leaveDMConfigScreen);

    SCREEN_CONNECT(enterDMCountDownScreen);
    SCREEN_CONNECT(postEnterDMCountDownScreen)
    SCREEN_CONNECT(leaveDMCountDownScreen);

    SCREEN_CONNECT(enterDMPlayersReadyScreen);
    SCREEN_CONNECT(leaveDMPlayersReadyScreen);

    SCREEN_CONNECT(enterDMRunningScreen);
    SCREEN_CONNECT(leaveDMRunningScreen);

    SCREEN_CONNECT(enterDMWinnerDisplayScreen);
    SCREEN_CONNECT(leaveDMWinnerDisplayScreen);

    SCREEN_CONNECT(enterSoccerConfigScreen);
    SCREEN_CONNECT(leaveSoccerConfigScreen);

    SCREEN_CONNECT(leaveSoccerPlayersReadyScreen);
    SCREEN_CONNECT(enterSoccerPlayersReadyScreen);

    SCREEN_CONNECT(enterSoccerRunningScreen);
    SCREEN_CONNECT(leaveSoccerRunningScreen);

    SCREEN_CONNECT(enterSoccerCountDownScreen);
    SCREEN_CONNECT(leaveSoccerCountDownScreen);

    SCREEN_CONNECT(enterSoccerGameOverScreen);
    SCREEN_CONNECT(leaveSoccerGameOverScreen);
#undef SCREEN_CONNECT
}

void BattleBoxMainWindow::initializeSystemConfigurationScreen() {
    // Configure the system configuration screen. This may require
    // things like back buttons, and access to the current data
    connect(ui->configuration, &ConfigurationWidget::clickedBack,
            m_state->screen(), &Screen::changeToGameSelectScreen);
    ui->configuration->init(m_state, m_mediaScreen);
}


void BattleBoxMainWindow::initMediaDialog() {
    m_mediaScreen->setModal(false);
    m_mediaScreen->show();
}

void BattleBoxMainWindow::initGameSelectScreen() {
    // Slot Connections.
    connect(ui->dmConfigButton, &QPushButton::clicked,
            m_state->screen(), &Screen::changeToDMConfigScreen);
    connect(ui->soccerConfigButton, &QPushButton::clicked,
            m_state->screen(), &Screen::changeToSoccerConfigScreen);
    connect(ui->systemConfigurationButton, &QPushButton::clicked,
            m_state->screen(), &Screen::changeToConfigurationScreen);
}

void BattleBoxMainWindow::initQuickSelectWidgets() {

    // TODO: Move some this into the application state.

    // Setting up directory watcher for quick loading for both
    // death match and soccer.
    connect(m_dirWatcher, &QFileSystemWatcher::directoryChanged,
            this, &BattleBoxMainWindow::updateQuickLoadFiles);

    m_dirWatcher->addPath(DEATHMATCH_QUICK_LOAD_FOLDER);
    loadQuickLoadFiles(DEATHMATCH_QUICK_LOAD_FOLDER);
    m_dirWatcher->addPath(SOCCER_QUICK_LOAD_FOLDER);
    loadQuickLoadFiles(SOCCER_QUICK_LOAD_FOLDER);
}

void BattleBoxMainWindow::initLEDController() {
    // Connecting count down signals.
    connect(this, &BattleBoxMainWindow::DMCDstart3,
            m_state->ledController(), &LEDController::DMCDstart3);
    connect(this, &BattleBoxMainWindow::DMCDstart2,
            m_state->ledController(), &LEDController::DMCDstart2);
    connect(this, &BattleBoxMainWindow::DMCDstart1,
            m_state->ledController(), &LEDController::DMCDstart1);
    connect(this, &BattleBoxMainWindow::DMCDstartFight,
            m_state->ledController(), &LEDController::DMCDstartFight);

    // Connecting death match player wins screen light signals.
    connect(this, &BattleBoxMainWindow::dmPlayerOneWins,
            m_state->ledController(), &LEDController::dmPlayerOneWins);
    connect(this, &BattleBoxMainWindow::dmPlayerTwoWins,
            m_state->ledController(), &LEDController::dmPlayerTwoWins);

    // Connecting player ready screen signals.
    connect(this, &BattleBoxMainWindow::dmPlayerOneReady,
            m_state->ledController(), &LEDController::dmPlayerOneReady);
    connect(this, &BattleBoxMainWindow::dmPlayerOneCancelledReady,
            m_state->ledController(), &LEDController::dmPlayerOneCancelledReady);
    connect(this, &BattleBoxMainWindow::dmPlayerOneCantBeReady,
            m_state->ledController(), &LEDController::dmPlayerOneCantBeReady);

    connect(this, &BattleBoxMainWindow::dmPlayerTwoReady,
            m_state->ledController(), &LEDController::dmPlayerTwoReady);
    connect(this, &BattleBoxMainWindow::dmPlayerTwoCancelledReady,
            m_state->ledController(), &LEDController::dmPlayerTwoCancelledReady);
    connect(this, &BattleBoxMainWindow::dmPlayerTwoCantBeReady,
            m_state->ledController(), &LEDController::dmPlayerTwoCantBeReady);

    // Connecting the deathmatch countdown trigger signals from the
    // death match runtime.
    connect(m_state->data()->deathMatchRuntime(), &DeathMatchRuntime::doorDropCountDown,
            m_state->ledController(), &LEDController::dmDoorDropCountDown);
    connect(m_state->data()->deathMatchRuntime(), &DeathMatchRuntime::matchOverCountDown,
            m_state->ledController(), &LEDController::dmMatchOverCountDown);

}

void BattleBoxMainWindow::initDeathMatchConfigScreen() {
    // Death match configuration screen slots

    // Other slot
    connect(ui->dmCfgSaveButton, &QPushButton::clicked,
            this, &BattleBoxMainWindow::on_dmCfgSaveButton_clicked);
    connect(ui->dmCfgLoadButton, &QPushButton::clicked,
            this, &BattleBoxMainWindow::on_dmCfgLoadButton_clicked);

    connect(ui->dmStart, &QPushButton::clicked,
            m_state->screen(), &Screen::changeToDMPlayersReadyScreen);
    connect(ui->dmCancel, &QPushButton::clicked,
            m_state->screen(), &Screen::changeToGameSelectScreen);
    connect(ui->dmCfgReset, &QPushButton::clicked,
            m_state->data(), &BattleBoxViewModel::resetDeathMatchConfig);

    // Setting up bidirectional connections between the deathmatch configuration
    // and the configuration screen.

    // Connecting player one name edit
    ui->playerOneNameLineEdit->setText(m_state->data()->deathMatchConfig()->playerOneName());
    connect(ui->playerOneNameLineEdit, &QLineEdit::textChanged,
            m_state->data()->deathMatchConfig(), &DeathMatchConfig::setPlayerOneName);
    connect(m_state->data()->deathMatchConfig(), &DeathMatchConfig::playerOneNameChanged,
            ui->playerOneNameLineEdit, &QLineEdit::setText);

    // Connecting player two name edit
    ui->playerTwoNameLineEdit->setText(m_state->data()->deathMatchConfig()->playerTwoName());
    connect(ui->playerTwoNameLineEdit, &QLineEdit::textChanged,
            m_state->data()->deathMatchConfig(), &DeathMatchConfig::setPlayerTwoName);
    connect(m_state->data()->deathMatchConfig(), &DeathMatchConfig::playerTwoNameChanged,
            ui->playerTwoNameLineEdit, &QLineEdit::setText);

    // Connecting match duration widget
    ui->matchDurationWidget->setDuration(m_state->data()->deathMatchConfig()->matchDuration());
    connect(ui->matchDurationWidget, &DurationWidget::durationChanged,
            m_state->data()->deathMatchConfig(), &DeathMatchConfig::setMatchDuration);
    connect(m_state->data()->deathMatchConfig(), &DeathMatchConfig::matchDurationChanged,
            ui->matchDurationWidget, &DurationWidget::setDuration);

    // Connecting door drop time duration widget
    ui->doorDropTimeWidget->setDuration(m_state->data()->deathMatchConfig()->doorDropTime());
    connect(ui->doorDropTimeWidget, &DurationWidget::durationChanged,
            m_state->data()->deathMatchConfig(), &DeathMatchConfig::setDoorDropTime);
    connect(m_state->data()->deathMatchConfig(), &DeathMatchConfig::doorDropChanged,
            ui->doorDropTimeWidget, &DurationWidget::setDuration);

    // Connecting drop down with kind
    ui->doorDropKindComboBox->setCurrentIndex((int)m_state->data()->deathMatchConfig()->doorDropKind());
    connect(ui->doorDropKindComboBox, &QComboBox::currentIndexChanged,
            m_state->data()->deathMatchConfig(), &DeathMatchConfig::setDoorDropKindFromInt);
    connect(m_state->data()->deathMatchConfig(), &DeathMatchConfig::doorDropKindChangedInt,
            ui->doorDropKindComboBox, &QComboBox::setCurrentIndex);

    // Connecting do matchOverWarningTime
    ui->matchOverWarningTime->setValue(m_state->data()->deathMatchConfig()->matchOverWarningTime());
    connect(ui->matchOverWarningTime, &QSpinBox::valueChanged,
            m_state->data()->deathMatchConfig(), &DeathMatchConfig::setMatchOverWarningTime);
    connect(m_state->data()->deathMatchConfig(), &DeathMatchConfig::matchOverWarningTimeChanged,
            ui->matchOverWarningTime, &QSpinBox::setValue);

    // Connecting do doorDropWarningTime
    ui->doorDropWarningTime->setValue(m_state->data()->deathMatchConfig()->doorDropWarningTime());
    connect(ui->doorDropWarningTime, &QSpinBox::valueChanged,
            m_state->data()->deathMatchConfig(), &DeathMatchConfig::setDoorDropWarningTime);
    connect(m_state->data()->deathMatchConfig(), &DeathMatchConfig::doorDropWarningTimeChanged,
            ui->doorDropWarningTime, &QSpinBox::setValue);

    // Connecting quick load slot
    connect(ui->dmQuickLoadButton, &QPushButton::clicked,
            [&] {
        auto items = ui->dmQuickLoadListWidget->selectedItems();
        if(items.size() != 1) {
            return;
        }
        QString path = DEATHMATCH_QUICK_LOAD_FOLDER + QString("/") + items[0]->text();
        this->m_state->data()->deathMatchConfig()->loadFromFile(path);
    });

    // Error signal connection.
    connect(this->m_state->data()->deathMatchConfig(), &DeathMatchConfig::error,
            this, &BattleBoxMainWindow::receivedError);

    // Configuring default values
    m_state->data()->deathMatchConfig()->setMatchDuration(180);
    m_state->data()->deathMatchConfig()->setDoorDropTime(60);
}

void BattleBoxMainWindow::initDeathMatchPlayersReadyScreen() {
    // Make sure to only only handle input while
    // m_state->screen()->currentScreen() == Screen::ScreenKind::DMPlayersReadyScreen
    // is true.

    // Connecting buttons.
    connect(ui->dmprPlayerOneReadyButton, &QPushButton::clicked,
            [&] {
                m_state->data()->deathMatchPlayerOneReady()->setPlayerReady(true);
                m_state->arduinoClient()->setP1SpotLight(true);
    });
    connect(ui->dmprPlayerTwoReadyButton, &QPushButton::clicked,
            [&] {
                m_state->data()->deathMatchPlayerTwoReady()->setPlayerReady(true);
                m_state->arduinoClient()->setP2SpotLight(true);
    });

    // Screen changing buttons
    connect(ui->dmprStart, &QPushButton::clicked,
            m_state->screen(), &Screen::changeToDMCountDownScreen);
    connect(ui->dmprCancel, &QPushButton::clicked,
            m_state->screen(), &Screen::changeToDMConfigScreen);
    // Connecting battle box to UI screen

    // Connecting player one to battle box UI screen controls
    connect(m_state->physicalState()->playerOne()->readyButton(), &PhysicalButton::stateChanged,
            [&] (bool arg) {
                if (m_state->screen()->currentScreen() == Screen::ScreenKind::DMPlayersReadyScreen) {
                    m_state->data()->deathMatchPlayerOneReady()->setPlayerReadyForRound(arg);
                    m_state->arduinoClient()->setP1SpotLight(true);
                }
            });

    connect(m_state->physicalState()->playerOne()->doorButton(), &PhysicalButton::stateChanged,
        m_state->data()->deathMatchPlayerOneReady(), &DeathMatchPlayerReadyModel::setDoorClosedForRound);

    connect(m_state->physicalState()->playerOne()->conceedButton(), &PhysicalButton::stateChanged,
            [&] {
                if (m_state->screen()->currentScreen() == Screen::ScreenKind::DMPlayersReadyScreen) {
                    m_state->data()->deathMatchPlayerOneReady()->cancelPlayerReadyForRound();
                    m_state->arduinoClient()->setP1SpotLight(false);
                }
            });

    // Connecting player two to battle box UI screen controls
    connect(m_state->physicalState()->playerTwo()->readyButton(), &PhysicalButton::stateChanged,
            [&] (bool arg) {
                if (m_state->screen()->currentScreen() == Screen::ScreenKind::DMPlayersReadyScreen) {
                    m_state->data()->deathMatchPlayerTwoReady()->setPlayerReadyForRound(arg);
                    m_state->arduinoClient()->setP2SpotLight(true);
                }
            });
    connect(m_state->physicalState()->playerTwo()->doorButton(), &PhysicalButton::stateChanged,
        m_state->data()->deathMatchPlayerTwoReady(), &DeathMatchPlayerReadyModel::setDoorClosedForRound);
    connect(m_state->physicalState()->playerTwo()->conceedButton(), &PhysicalButton::stateChanged,
            [&] {
                if (m_state->screen()->currentScreen() == Screen::ScreenKind::DMPlayersReadyScreen) {
                    m_state->data()->deathMatchPlayerTwoReady()->cancelPlayerReadyForRound();
                    m_state->arduinoClient()->setP2SpotLight(false);
                }
            });


    connect(m_state->data()->deathMatchPlayerOneReady(), &DeathMatchPlayerReadyModel::readyTextChanged,
            this, &BattleBoxMainWindow::dmprUpdateP1ReadyText);
    connect(m_state->data()->deathMatchPlayerTwoReady(), &DeathMatchPlayerReadyModel::readyTextChanged,
            this, &BattleBoxMainWindow::dmprUpdateP2ReadyText);

    connect(m_state->data()->deathMatchPlayerOneReady(), &DeathMatchPlayerReadyModel::doorTextChanged,
            this, &BattleBoxMainWindow::dmprUpdateP1DoorText);
    connect(m_state->data()->deathMatchPlayerTwoReady(), &DeathMatchPlayerReadyModel::doorTextChanged,
            this, &BattleBoxMainWindow::dmprUpdateP2DoorText);

    // Connecting the door not closed indicator to player ready indicator.
    connect(this->m_state->data()->deathMatchPlayerOneReady(), &DeathMatchPlayerReadyModel::doorNotClosed,
            this, &BattleBoxMainWindow::receivedError);
    connect(this->m_state->data()->deathMatchPlayerTwoReady(), &DeathMatchPlayerReadyModel::doorNotClosed,
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
        [&] {
            m_state->screen()->changeToDMRunningScreen();
        });

    // Connecting cancel.
    connect(ui->dmcdCancel, &QPushButton::clicked,
        [&]{
            m_state->screen()->changeToDMConfigScreen();
        });

}

void BattleBoxMainWindow::initDeathMatchRunningScreen() {
    ui->dmrCountDownWidget->setup(deathMatchConfig(), m_state->data()->deathMatchRuntime());

    // Configuring buttons
    connect(ui->dmrPlayerOneWinsButton, &QPushButton::clicked,
            [&] {
        if(m_state->data()->deathMatchConfig()->playerOneName() == "") {
            m_state->data()->setDeathMatchWinner("Player One");
        } else {
            m_state->data()->setDeathMatchWinner(m_state->data()->deathMatchConfig()->playerOneName());
        }
        m_state->screen()->changeToDMWinnerDisplayScreen(m_state->data()->deathMatchWinner());
    });
    connect(ui->dmrPlayerTwoWinsButton, &QPushButton::clicked,
            [&] {
        if(m_state->data()->deathMatchConfig()->playerTwoName() == "") {
            m_state->data()->setDeathMatchWinner("Player Two");
        } else {
            m_state->data()->setDeathMatchWinner(m_state->data()->deathMatchConfig()->playerTwoName());
        }
        m_state->screen()->changeToDMWinnerDisplayScreen(m_state->data()->deathMatchWinner());
    });
    // Naviaging buttons
    connect(ui->dmrBackToDMConfigButton, &QPushButton::clicked,
            m_state->screen(), &Screen::changeToDMConfigScreen);
    connect(ui->dmrRestartMatchButton, &QPushButton::clicked,
            m_state->screen(), &Screen::changeToDMPlayersReadyScreen);
    connect(ui->dmrCancel, &QPushButton::clicked,
            m_state->screen(), &Screen::changeToGameSelectScreen);
}

void BattleBoxMainWindow::initDeathMatchWinnerScreen() {
    connect(ui->dmwRestartButton, &QPushButton::clicked,
            m_state->screen(), &Screen::changeToDMPlayersReadyScreen);
    connect(ui->dmwToDMCButton, &QPushButton::clicked,
            m_state->screen(), &Screen::changeToDMConfigScreen);
    connect(ui->dmwToGameSelectButton, &QPushButton::clicked,
            m_state->screen(), &Screen::changeToGameSelectScreen);
    connect(m_state->data(), &BattleBoxViewModel::notifyDeathMatchWinnerChanged,
            [&](QString arg) {
        ui->dmWinnerDisplayLabel->setText(QString("%1\nWINS!!").arg(arg));
    });

}

void BattleBoxMainWindow::initSoccerConfigScreen() {
    // Configuring buttons
    connect(ui->soccerCfgStartButton, &QPushButton::clicked,
            [&] { m_state->screen()->changeToSoccerPlayersReadyScreen(); });
    connect(ui->soccerCfgCancelButton, &QPushButton::clicked,
            [&] { m_state->screen()->changeToGameSelectScreen(); });

    connect(ui->soccerCfgResetButton, &QPushButton::clicked,
            m_state->data(), &BattleBoxViewModel::resetSoccerConfig);

    connect(ui->soccerCfgSaveFileButton, &QPushButton::clicked,
            this, &BattleBoxMainWindow::on_soccerCfgSaveButton_clicked);
    connect(ui->soccerCfgOpenFileButton, &QPushButton::clicked,
            this, &BattleBoxMainWindow::on_soccerCfgLoadButton_clicked);

    // Connecting team one name edit
    ui->soccerCfgTeamOneNameLineEdit->setText(m_state->data()->soccerConfig()->teamOneName());
    connect(ui->soccerCfgTeamOneNameLineEdit, &QLineEdit::textChanged,
            m_state->data()->soccerConfig(), &SoccerConfig::setTeamOneName);
    connect(m_state->data()->soccerConfig(), &SoccerConfig::notifyTeamOneNameChanged,
            ui->soccerCfgTeamOneNameLineEdit, &QLineEdit::setText);

    // Connecting team two name edit
    ui->soccerCfgTeamTwoNameLineEdit->setText(m_state->data()->soccerConfig()->teamTwoName());
    connect(ui->soccerCfgTeamTwoNameLineEdit, &QLineEdit::textChanged,
            m_state->data()->soccerConfig(), &SoccerConfig::setTeamTwoName);
    connect(m_state->data()->soccerConfig(), &SoccerConfig::notifyTeamTwoNameChanged,
            ui->soccerCfgTeamTwoNameLineEdit, &QLineEdit::setText);

    // Connecting match duration widget
    ui->soccerCfgMatchDurationWidget->setDuration(m_state->data()->soccerConfig()->matchDuration());
    connect(ui->soccerCfgMatchDurationWidget, &DurationWidget::durationChanged,
            m_state->data()->soccerConfig(), &SoccerConfig::setMatchDuration);
    connect(m_state->data()->soccerConfig(), &SoccerConfig::notifyMatchDurationChanged,
            ui->soccerCfgMatchDurationWidget, &DurationWidget::setDuration);

    // Connecting match score
    ui->soccerCfgGameScoreSpinBox->setValue(m_state->data()->soccerConfig()->maxScore());
    connect(ui->soccerCfgGameScoreSpinBox, &QSpinBox::valueChanged,
            m_state->data()->soccerConfig(), &SoccerConfig::setMaxScore);
    connect(m_state->data()->soccerConfig(), &SoccerConfig::notifyMaxScoreChanged,
            ui->soccerCfgGameScoreSpinBox, &QSpinBox::setValue);

    // Error signal connection.
    connect(this->m_state->data()->soccerConfig(), &SoccerConfig::error,
            this, &BattleBoxMainWindow::receivedError);

    // Connecting quick load slot
    connect(ui->soccerCfgQuickLoadButton, &QPushButton::clicked,
            [&] {
        auto items = ui->soccerCfgQuickLoadListWidget->selectedItems();
        if(items.size() != 1) {
            return;
        }
        QString path = SOCCER_QUICK_LOAD_FOLDER + QString("/") + items[0]->text();
        this->m_state->data()->soccerConfig()->loadFromFile(path);

    });

}

void BattleBoxMainWindow::initSoccerPlayersReadyScreen() {

    // Soccer players ready screen
    connect(ui->sprStartButton, &QPushButton::clicked,
            [&] { m_state->screen()->changeToSoccerCountDownScreen(); });
    connect(ui->sprCancelButton, &QPushButton::clicked,
            [&] { m_state->screen()->changeToSoccerConfigScreen(); });

    connect(ui->sprTeamOneReadyButton, &QPushButton::clicked,
            [&] { m_state->data()->soccerTeamOneReady()->setTeamReady(true); });
    connect(ui->sprTeamTwoReadyButton, &QPushButton::clicked,
            [&] { m_state->data()->soccerTeamTwoReady()->setTeamReady(true); });

    // Screen changing buttons
    connect(m_state->data()->soccerTeamOneReady(), &SoccerTeamReady::readyTextChanged,
            this, &BattleBoxMainWindow::sprUpdateT1ReadyText);
    connect(m_state->data()->soccerTeamTwoReady(), &SoccerTeamReady::readyTextChanged,
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
            [&] { m_state->screen()->changeToSoccerRunningScreen(); });

    // Connecting cancel.
    connect(ui->scdCancelButton, &QPushButton::clicked,
            [&]{ m_state->screen()->changeToSoccerConfigScreen(); });
}

void BattleBoxMainWindow::initSoccerRunningScreen() {
    ui->srRunningWidget->setup(m_state->data()->soccerMatch());

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
        if(m_state->data()->soccerMatch()->teamOneScore() >= 1000) {
            m_state->data()->soccerMatch()->setTeamOneScore(1000);
        } else {
            m_state->data()->soccerMatch()->setTeamOneScore(m_state->data()->soccerMatch()->teamOneScore() + 1);
        }
    });


    connect(ui->srTeamOneWinsButton, &QPushButton::clicked,
            [&] {

    });


    connect(ui->srT1ScorePlusOneButton, &QPushButton::clicked,
            [&] {
        if(m_state->data()->soccerMatch()->teamOneScore() >= 1000) {
            m_state->data()->soccerMatch()->setTeamOneScore(1000);
        } else {
            m_state->data()->soccerMatch()->setTeamOneScore(m_state->data()->soccerMatch()->teamOneScore() + 1);
        }
    });

    connect(ui->srT1ScoreMinusOneButton, &QPushButton::clicked,
            [&] {
        if(m_state->data()->soccerMatch()->teamOneScore() <= 0) {
            m_state->data()->soccerMatch()->setTeamOneScore(0);
        } else {
            m_state->data()->soccerMatch()->setTeamOneScore(m_state->data()->soccerMatch()->teamOneScore() - 1);
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
        if(m_state->data()->soccerMatch()->teamTwoScore() >= 1000) {
            m_state->data()->soccerMatch()->setTeamTwoScore(1000);
        } else {
            m_state->data()->soccerMatch()->setTeamTwoScore(m_state->data()->soccerMatch()->teamTwoScore() + 1);
        }
    });


    connect(ui->srT2ScorePlusOneButton, &QPushButton::clicked,
            [&] {
        if(m_state->data()->soccerMatch()->teamTwoScore() >= 1000) {
            m_state->data()->soccerMatch()->setTeamTwoScore(1000);
        } else {
            m_state->data()->soccerMatch()->setTeamTwoScore(m_state->data()->soccerMatch()->teamTwoScore() + 1);
        }
    });

    connect(ui->srT2ScoreMinusOneButton, &QPushButton::clicked,
            [&] {
        if(m_state->data()->soccerMatch()->teamTwoScore() <= 0) {
            m_state->data()->soccerMatch()->setTeamTwoScore(0);
        } else {
            m_state->data()->soccerMatch()->setTeamTwoScore(m_state->data()->soccerMatch()->teamTwoScore() - 1);
        }
    });

    // Naviaging buttons
    connect(ui->srRestartMatchButton,  &QPushButton::clicked,
            [&] { m_state->screen()->changeToSoccerPlayersReadyScreen(); });
    connect(ui->srCancelGameSelectionButton, &QPushButton::clicked,
            [&] { m_state->screen()->changeToGameSelectScreen(); });
    connect(ui->srCancelConfigButton, &QPushButton::clicked,
            [&] { m_state->screen()->changeToSoccerConfigScreen(); });

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

// TODO: Move this into the application state instead of here.
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

// TODO: Move this into the application state.
void BattleBoxMainWindow::on_dmCfgSaveButton_clicked() {
    auto fileName = QFileDialog::getSaveFileName(
        this,
        tr("Open File"),
        DEATHMATCH_QUICK_LOAD_FOLDER,
        tr("Json Files (*.json)"));
    this->m_state->data()->deathMatchConfig()->saveToFile(fileName);
}

// TODO: Move this into the application state.
void BattleBoxMainWindow::on_dmCfgLoadButton_clicked() {
    auto fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        DEATHMATCH_QUICK_LOAD_FOLDER,
        tr("Json Files (*.json)"));
    this->m_state->data()->deathMatchConfig()->loadFromFile(fileName);
}

void BattleBoxMainWindow::receivedError(QString msg) {
    std::cout << "Received error message: " << msg.toStdString() << std::endl;
}

void BattleBoxMainWindow::enterConfigurationScreen() {
    ui->mainDisplay->setCurrentWidget(ui->configuration);
}

void BattleBoxMainWindow::leaveConfigurationScreen() {

}

void BattleBoxMainWindow::enterGameSelectScreen() {
    ui->mainDisplay->setCurrentWidget(ui->gameSelection);
}

void BattleBoxMainWindow::leaveGameSelectScreen() {

}

void BattleBoxMainWindow::enterDMConfigScreen() {
    ui->mainDisplay->setCurrentWidget(ui->deathMatchConfig);
}

void BattleBoxMainWindow::leaveDMConfigScreen() {

}

void BattleBoxMainWindow::enterDMCountDownScreen() {
    ui->mainDisplay->setCurrentWidget(ui->deathMatchCountDown);
}

void BattleBoxMainWindow::postEnterDMCountDownScreen() {
    m_dmcdAnimationGroup->start();
}

void BattleBoxMainWindow::leaveDMCountDownScreen() {
    m_dmcdAnimationGroup->stop();
}

void BattleBoxMainWindow::enterDMPlayersReadyScreen() {
    ui->mainDisplay->setCurrentWidget(ui->deathMatchPlayersReady);
    // TODO: Refactor everything from here into the application state and attach it to
    // the signal in a different way. This shouldn't be part of the main window code base.
    m_state->data()->deathMatchPlayerOneReady()->reset();
    m_state->data()->deathMatchPlayerOneReady()->setDoorClosed(m_state->physicalState()->playerOne()->doorButton()->state());
    m_state->data()->deathMatchPlayerTwoReady()->reset();
    m_state->data()->deathMatchPlayerTwoReady()->setDoorClosed(m_state->physicalState()->playerTwo()->doorButton()->state());
    m_state->arduinoClient()->setP1SpotLight(false);
    m_state->arduinoClient()->setP2SpotLight(false);
}

void BattleBoxMainWindow::leaveDMPlayersReadyScreen() {
    // TODO: Refactor everything from here into the application state and attach it to
    // the signal in a different way. This shouldn't be part of the main window code base.
    m_state->physicalState()->playerOne()->spotLight()->setState(false);
    m_state->physicalState()->playerTwo()->spotLight()->setState(false);
    m_state->arduinoClient()->setP1SpotLight(false);
    m_state->arduinoClient()->setP2SpotLight(false);
}

void BattleBoxMainWindow::enterDMRunningScreen() {
    ui->mainDisplay->setCurrentWidget(ui->deathMatchRunning);
    ui->dmrStackedWidget->setCurrentWidget(ui->dmrCountDownWidget);
    ui->dmrCountDownWidget->start();
}

void BattleBoxMainWindow::leaveDMRunningScreen() {
    ui->dmrCountDownWidget->stop();
}

void BattleBoxMainWindow::enterDMWinnerDisplayScreen(QString playerName) {
    ui->mainDisplay->setCurrentWidget(ui->deathMatchWinner);
    if (playerName == m_state->data()->deathMatchConfig()->playerOneName()) {
        emit dmPlayerOneWins(playerName);
    } else {
        emit dmPlayerTwoWins(playerName);
    }
}

void BattleBoxMainWindow::leaveDMWinnerDisplayScreen() {

}

void BattleBoxMainWindow::enterSoccerConfigScreen() {
    ui->mainDisplay->setCurrentWidget(ui->soccerConfig);
}

void BattleBoxMainWindow::leaveSoccerConfigScreen() {

}

void BattleBoxMainWindow::leaveSoccerPlayersReadyScreen() {

}

void BattleBoxMainWindow::enterSoccerPlayersReadyScreen() {
    // TODO: Refactor everything from here into the application state and attach it to
    // the signal in a different way. This shouldn't be part of the main window code base.
    m_state->data()->resetSoccerTeamOneReady();
    m_state->data()->resetSoccerTeamTwoReady();

    // This is not part of the application state.
    ui->mainDisplay->setCurrentWidget(ui->soccerPlayersReady);

}

void BattleBoxMainWindow::enterSoccerRunningScreen() {
    // TODO: Refactor everything from here into the application state and attach it to
    // the signal in a different way. This shouldn't be part of the main window code base.
    m_state->data()->soccerMatch()->loadSoccerConfig(m_state->data()->soccerConfig());

    // Loading new soccer match data
    ui->srStackedWidget->setCurrentWidget(ui->srRunningWidget);
    ui->mainDisplay->setCurrentWidget(ui->soccerRunning);
    ui->srRunningWidget->start();
    ui->srResumeButton->setEnabled(false);
}

void BattleBoxMainWindow::leaveSoccerRunningScreen() {
    ui->srResumeCountDownWidget->cancel();
    ui->srRunningWidget->stop();
}

void BattleBoxMainWindow::enterSoccerCountDownScreen() {
    ui->mainDisplay->setCurrentWidget(ui->soccerCountDown);
    m_scdAnimationGroup->start();
}

void BattleBoxMainWindow::leaveSoccerCountDownScreen() {
    m_scdAnimationGroup->stop();
}

void BattleBoxMainWindow::enterSoccerGameOverScreen() {
    ui->mainDisplay->setCurrentWidget(ui->soccerGameOver);
}

void BattleBoxMainWindow::leaveSoccerGameOverScreen() {

}

void BattleBoxMainWindow::dmprUpdateP1ReadyText(QString arg) {
    ui->dmprPlayerOneReadyLabel->setText(QString("Player One: %1").arg(arg));
    if(m_state->data()->deathMatchPlayerOneReady()->playerReady()) {
        ui->dmprPlayerOneReadyWidget->setStyleSheet(GREEN_BG_STYLE_SHEET);
        emit dmPlayerOneReady();
    } else {
        ui->dmprPlayerOneReadyWidget->setStyleSheet(RED_BG_STYLE_SHEET);
        emit dmPlayerOneCancelledReady();
    }
}

void BattleBoxMainWindow::dmprUpdateP2ReadyText(QString arg) {
    ui->dmprPlayerTwoReadyLabel->setText(QString("Player Two: %1").arg(arg));
    if(m_state->data()->deathMatchPlayerTwoReady()->playerReady()) {
        ui->dmprPlayerTwoReadyWidget->setStyleSheet(GREEN_BG_STYLE_SHEET);
        emit dmPlayerTwoReady();
    } else {
        ui->dmprPlayerTwoReadyWidget->setStyleSheet(RED_BG_STYLE_SHEET);
        emit dmPlayerTwoCancelledReady();
    }
}

void BattleBoxMainWindow::dmprUpdateP1DoorText(QString arg) {
    ui->dmprPlayerOneDoorIndicatorLabel->setText(QString("Door: %1").arg(arg));
    if(m_state->data()->deathMatchPlayerOneReady()->doorClosed()) {
        ui->dmprPlayerOneDoorWidget->setStyleSheet(GREEN_BG_STYLE_SHEET);
    } else {
        ui->dmprPlayerOneDoorWidget->setStyleSheet(RED_BG_STYLE_SHEET);
    }
}

void BattleBoxMainWindow::dmprUpdateP2DoorText(QString arg) {
    ui->dmprPlayerTwoDoorIndicatorLabel->setText(QString("Door: %1").arg(arg));
    if(m_state->data()->deathMatchPlayerTwoReady()->doorClosed()) {
        ui->dmprPlayerTwoDoorWidget->setStyleSheet(GREEN_BG_STYLE_SHEET);
    } else {
        ui->dmprPlayerTwoDoorWidget->setStyleSheet(RED_BG_STYLE_SHEET);
    }
}

// TODO: Refactor this into ApplicationState.
void BattleBoxMainWindow::updateQuickLoadFiles(QString dir) {
    loadQuickLoadFiles(dir);
}

// TODO: Refactor this into ApplicationState.
void BattleBoxMainWindow::on_soccerCfgSaveButton_clicked() {
    auto fileName = QFileDialog::getSaveFileName(
        this,
        tr("Open File"),
        SOCCER_QUICK_LOAD_FOLDER,
        tr("Json Files (*.json)"));
    m_state->data()->soccerConfig()->saveToFile(fileName);
}

// TODO: Refactor this into ApplicationState.
void BattleBoxMainWindow::on_soccerCfgLoadButton_clicked() {
    auto fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        SOCCER_QUICK_LOAD_FOLDER,
        tr("Json Files (*.json)"));
    m_state->data()->soccerConfig()->loadFromFile(fileName);
}

void BattleBoxMainWindow::sprUpdateT1ReadyText(QString arg) {
    ui->sprTeamOneReadyLabel->setText(QString("Team One: %1").arg(arg));
    if(m_state->data()->soccerTeamOneReady()->teamReady()) {
        ui->sprTeamOneReadyLabel->setStyleSheet(GREEN_BG_STYLE_SHEET);
    } else {
        ui->sprTeamOneReadyLabel->setStyleSheet(RED_BG_STYLE_SHEET);
    }
}

void BattleBoxMainWindow::sprUpdateT2ReadyText(QString arg) {
    ui->sprTeamTwoReadyLabel->setText(QString("Team Two: %1").arg(arg));
    if(m_state->data()->soccerTeamTwoReady()->teamReady()) {
        ui->sprTeamTwoReadyLabel->setStyleSheet(GREEN_BG_STYLE_SHEET);
    } else {
        ui->sprTeamTwoReadyLabel->setStyleSheet(RED_BG_STYLE_SHEET);
    }
}
