#include "mediadialog.h"
#include "triggeringanimation.h"
#include "ui_mediadialog.h"
#include "battleboxmainwindow.h"
#include "soundeffectmedia.h"
#include "util.h"
#include "app_state/applicationstate.h"

#include <QDirIterator>
#include <QAudioDecoder>
#include <QMimeDatabase>
#include <QFileInfo>
#include <QMovie>
#include <QAudioOutput>
#include <QSoundEffect>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QSoundEffect>
#include <QAudioDevice>
#include <QBuffer>

constexpr const char* RESOURCE_ROOT = "qrc:/battlebox/media/sounds/resources";

constexpr const char* THREE_SOUND = "sounds/Three.wav";
constexpr const char* TWO_SOUND = "sounds/Two.wav";
constexpr const char* ONE_SOUND = "sounds/One.wav";
constexpr const char* FIGHT_SOUND = "sounds/Fight.wav";
constexpr const char* DEATHMATCH_SOUND = "sounds/DeathMatch.wav";
constexpr const char* GO_SOUND = "sounds/Go_Angry.wav";
constexpr const char* SOCCER_SOUND = "sounds/Soccer.wav";

MediaDialog::MediaDialog(ApplicationState *app_state, BattleBoxMainWindow *parent)
    : QDialog(parent)
    , ui(new Ui::MediaDialog)
    , m_state(app_state)
    , m_data(app_state->data())
    , m_champCoin(
          new QMovie(
              ":/battlebox/media/images/resources/SpinningCoin_50.gif",
              QByteArray(),
              this
              )
          )
    , m_out(new QAudioOutput(this))
    , m_deathMatch(new SoundEffectMedia(m_out, this))
    , m_soccer(new SoundEffectMedia(m_out, this))
    , m_three(new SoundEffectMedia(m_out, this))
    , m_two(new SoundEffectMedia(m_out, this))
    , m_one(new SoundEffectMedia(m_out, this))
    , m_fight(new SoundEffectMedia(m_out, this))
    , m_go(new SoundEffectMedia(m_out, this))
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    setSizeGripEnabled(true);
    layout()->setSizeConstraint(QLayout::SetNoConstraint);
    setMinimumSize(0, 0);

    // Loading movies from contents.
    ui->coinDisplayLabel->setMovie(m_champCoin);
    ui->coinDisplayLabel->setScaledContents(true);
    m_champCoin->start();

    init();
}

MediaDialog::~MediaDialog() {
    delete ui;
}

void MediaDialog::loadSettingsDependentResources() {
    initSoundEffect(m_deathMatch, "resources/sounds/deathmatch", "sounds/deathmatch", DEATHMATCH_SOUND);
    initSoundEffect(m_soccer, "resources/sounds/soccer", "sounds/soccer", SOCCER_SOUND);
    m_cdEff = new QGraphicsOpacityEffect(ui->countDownTextLabel);
    ui->countDownTextLabel->setGraphicsEffect(m_cdEff);
    setVolume(1.0f);
    initAnimatedSoundEffect(m_three, "resource/sounds/three", "sounds/three", THREE_SOUND, ui->countDownTextLabel, "3",
        [&](QParallelAnimationGroup *g) {
            qDebug() << "Setting m_cdThreeCallout";
            m_cdThreeCallout = g;
        });
    initAnimatedSoundEffect(m_two, "resource/sounds/two", "sounds/two", TWO_SOUND,  ui->countDownTextLabel, "2",
        [&](QParallelAnimationGroup *g) {
            qDebug() << "Setting m_cdTwoCallout";
            m_cdTwoCallout = g;
        });
    initAnimatedSoundEffect(m_one, "resource/sounds/one", "sounds/one", ONE_SOUND, ui->countDownTextLabel, "1",
        [&](QParallelAnimationGroup *g) {
            qDebug() << "Setting m_cdOneCallout";
            m_cdOneCallout = g;
        });
    initAnimatedSoundEffect(m_fight, "resource/sounds/fight", "sounds/fight", FIGHT_SOUND, ui->countDownTextLabel, "FIGHT!!!",
        [&](QParallelAnimationGroup *g) {
            qDebug() << "Setting m_cdFightCallout";
            m_cdFightCallout = g;
        });
    initAnimatedSoundEffect(m_go, "resource/sounds/go", "sounds/go", GO_SOUND, ui->countDownTextLabel, "GO!!!",
        [&](QParallelAnimationGroup *g) {
            qDebug() << "Setting m_cdGoCallout";
            m_cdGoCallout = g;
        });
}


static const char *GREEN_BG_STYLE_SHEET = "background-color:green;";
static const char *RED_BG_STYLE_SHEET = "background-color:red;";

void MediaDialog::dmprUpdateP1ReadyText(QString arg) {
    ui->dmprP1ReadyLabel->setText(QString("Player One: %1").arg(arg));
    if(m_state->data()->deathMatchPlayerOneReady()->playerReady()) {
        ui->dmprP1ReadyWidget->setStyleSheet(GREEN_BG_STYLE_SHEET);
    } else {
        ui->dmprP1ReadyWidget->setStyleSheet(RED_BG_STYLE_SHEET);
    }
}

void MediaDialog::dmprUpdateP2ReadyText(QString arg) {
    ui->dmprP2ReadyLabel->setText(QString("Player Two: %1").arg(arg));
    if(m_state->data()->deathMatchPlayerTwoReady()->playerReady()) {
        ui->dmprP2ReadyWidget->setStyleSheet(GREEN_BG_STYLE_SHEET);
    } else {
        ui->dmprP2ReadyWidget->setStyleSheet(RED_BG_STYLE_SHEET);
    }
}

void MediaDialog::dmprUpdateP1DoorText(QString arg) {
    ui->dmprP1DoorLabel->setText(QString("Door: %1").arg(arg));
    if(m_state->data()->deathMatchPlayerOneReady()->doorClosed()) {
        ui->dmprP1DoorWidget->setStyleSheet(GREEN_BG_STYLE_SHEET);
    } else {
        ui->dmprP1DoorWidget->setStyleSheet(RED_BG_STYLE_SHEET);
    }
}

void MediaDialog::dmprUpdateP2DoorText(QString arg) {
    ui->dmprP2DoorLabel->setText(QString("Door: %1").arg(arg));
    if(m_state->data()->deathMatchPlayerTwoReady()->doorClosed()) {
        ui->dmprP2DoorWidget->setStyleSheet(GREEN_BG_STYLE_SHEET);
    } else {
        ui->dmprP2DoorWidget->setStyleSheet(RED_BG_STYLE_SHEET);
    }
}

void MediaDialog::initializeDMPRScreen() {
    // Connecting to the display
    connect(m_state->data()->deathMatchPlayerOneReady(), &DeathMatchPlayerReadyModel::readyTextChanged,
            this, &MediaDialog::dmprUpdateP1ReadyText);
    connect(m_state->data()->deathMatchPlayerTwoReady(), &DeathMatchPlayerReadyModel::readyTextChanged,
            this, &MediaDialog::dmprUpdateP2ReadyText);

    connect(m_state->data()->deathMatchPlayerOneReady(), &DeathMatchPlayerReadyModel::doorTextChanged,
            this, &MediaDialog::dmprUpdateP1DoorText);
    connect(m_state->data()->deathMatchPlayerTwoReady(), &DeathMatchPlayerReadyModel::doorTextChanged,
            this, &MediaDialog::dmprUpdateP2DoorText);

}

void MediaDialog::initSoundEffect(SoundEffectMedia *effect,
                                  const char* resourceFilePathKey,
                                  const char* fsSettingsKey,
                                  const char* relativePath) {
    connect(this, &MediaDialog::volumeChanged,
            effect, &SoundEffectMedia::setVolume);
    QString fsPath = m_data->getSetting(QString(fsSettingsKey), QString(RESOURCE_LOCATION) + "/" + relativePath);
    QString resourcePath = m_data->getSetting(QString(resourceFilePathKey), QString(RESOURCE_ROOT) + "/" + relativePath);
    effect->initialize(fsPath, resourcePath);
}

void MediaDialog::initAnimatedSoundEffect(SoundEffectMedia *effect,
                                          const char* resourceKey,
                                          const char* fsSettingsKey,
                                          const char* relativePath,
                                          QLabel *toUpdate,
                                          QString text,
                                          Callback cb) {

    // Connecting
    connect(this, &MediaDialog::volumeChanged,
            effect, &SoundEffectMedia::setVolume);
    QString fsPath = m_data->getSetting(QString(fsSettingsKey), QString(RESOURCE_LOCATION) + "/" + relativePath);
    QString resourcePath = m_data->getSetting(QString(resourceKey), QString(RESOURCE_ROOT) + "/" + relativePath);
    connect(effect, &SoundEffectMedia::ready,
            [=](qint64 dur) {
        QParallelAnimationGroup *group = new QParallelAnimationGroup(this);
        {
            QPropertyAnimation *a = new QPropertyAnimation(m_cdEff, "opacity");
            a->setDuration(1000);
            a->setStartValue(0);
            a->setEndValue(1);
            a->setEasingCurve(QEasingCurve::InBack);
            connect(a, &QPropertyAnimation::stateChanged,
                    [=](QAbstractAnimation::State newState, QAbstractAnimation::State) {
                if(newState == QAbstractAnimation::State::Running) {
                    toUpdate->setStyleSheet("QLabel { font-size: 300px;}");
                    toUpdate->setText(text);
                }
            });
            group->addAnimation(a);
        }
        if (dur > 1000) {
            dur = 0;
        } else {
            dur = 1000 - dur;
        }

        // Setting up sound effect playback
        {
            auto *a = new TriggeringAnimation(this);
            a->setDuration(dur);
            connect(a, &QPropertyAnimation::stateChanged,
                    [=](QAbstractAnimation::State newState,
                        QAbstractAnimation::State oldState) {
                if(newState == QAbstractAnimation::State::Stopped
                        && oldState ==  QAbstractAnimation::State::Running) {
                    effect->play();
                }
            });
            group->addAnimation(a);
        }

        cb(group);
    });
    effect->initialize(fsPath, resourcePath);
}

void MediaDialog::init() {
#define SCREEN_SWITCH_CONNECT(SIG_SLOT_NAME)\
    connect(mainWindow(), &BattleBoxMainWindow::SIG_SLOT_NAME,\
            this, &MediaDialog::SIG_SLOT_NAME)
    SCREEN_SWITCH_CONNECT(DMCDstart3);
    SCREEN_SWITCH_CONNECT(DMCDstart2);
    SCREEN_SWITCH_CONNECT(DMCDstart1);
    SCREEN_SWITCH_CONNECT(DMCDstartFight);
#undef SCREEN_SWITCH_CONNECT

#define SCREEN_SWITCH_CONNECT(SIG_SLOT_NAME)\
    connect(m_state->screen(), &Screen::SIG_SLOT_NAME,\
            this, &MediaDialog::SIG_SLOT_NAME)

    SCREEN_SWITCH_CONNECT(enterGameSelectScreen);
    SCREEN_SWITCH_CONNECT(leaveGameSelectScreen);

    SCREEN_SWITCH_CONNECT(enterDMConfigScreen);
    SCREEN_SWITCH_CONNECT(leaveDMConfigScreen);

    SCREEN_SWITCH_CONNECT(enterDMCountDownScreen);
    SCREEN_SWITCH_CONNECT(leaveDMCountDownScreen);

    SCREEN_SWITCH_CONNECT(enterDMPlayersReadyScreen);
    SCREEN_SWITCH_CONNECT(leaveDMPlayersReadyScreen);

    SCREEN_SWITCH_CONNECT(enterDMRunningScreen);
    SCREEN_SWITCH_CONNECT(leaveDMRunningScreen);

    SCREEN_SWITCH_CONNECT(enterDMWinnerDisplayScreen);
    SCREEN_SWITCH_CONNECT(leaveDMWinnerDisplayScreen);

    SCREEN_SWITCH_CONNECT(enterSoccerConfigScreen);
    SCREEN_SWITCH_CONNECT(leaveSoccerConfigScreen);

    SCREEN_SWITCH_CONNECT(leaveSoccerPlayersReadyScreen);
    SCREEN_SWITCH_CONNECT(enterSoccerPlayersReadyScreen);

    SCREEN_SWITCH_CONNECT(enterSoccerRunningScreen);
    SCREEN_SWITCH_CONNECT(leaveSoccerRunningScreen);

    SCREEN_SWITCH_CONNECT(enterSoccerCountDownScreen);
    SCREEN_SWITCH_CONNECT(leaveSoccerCountDownScreen);

    SCREEN_SWITCH_CONNECT(enterSoccerGameOverScreen);
    SCREEN_SWITCH_CONNECT(leaveSoccerGameOverScreen);
#undef SCREEN_SWITCH_CONNECT
    initialzieDeathMatchRunning();
    initializeDMPRScreen();
}

void MediaDialog::initialzieDeathMatchRunning() {
    connect(m_data->deathMatchRuntime(), &DeathMatchRuntime::timeRemainingChanged,
            this, &MediaDialog::updateDMRRemainingTime);
    connect(m_data->deathMatchRuntime(), &DeathMatchRuntime::doorDropTimeRemainingChanged,
            this, &MediaDialog::updateDMRDoorDropTime);
    connect(m_data->deathMatchRuntime(), &DeathMatchRuntime::staringMatch,
            this, &MediaDialog::staringDMR);
}

BattleBoxMainWindow *MediaDialog::mainWindow() const {
    return qobject_cast<BattleBoxMainWindow *>(parent());
}

void MediaDialog::enterGameSelectScreen() {
    qDebug() << "Entering game selection screen";
    ui->mainDisplay->setCurrentWidget(ui->gameSelectPage);
    m_champCoin->start();
}

void MediaDialog::leaveGameSelectScreen() {
    qDebug() << "Leaving game selection screen";
    m_champCoin->stop();
}

void MediaDialog::enterDMConfigScreen() {
    qDebug() << "Entering dm config";
    m_deathMatch->play();
    ui->mainDisplay->setCurrentWidget(ui->deathMatchPage);
}

void MediaDialog::leaveDMConfigScreen() {
    qDebug() << "leaving dm config";

}

void MediaDialog::enterDMCountDownScreen() {
    qDebug() << "Entering DM count down";
    ui->mainDisplay->setCurrentWidget(ui->countDownScreen);
}

void MediaDialog::DMCDstart3() {
    qDebug() << "Called MediaDialog::DMCDstart3!";
    m_cdThreeCallout->start();
    qDebug() << "Called Finished call to m_cdThreeCallout->start";
}

void MediaDialog::DMCDstart2() {
    m_cdTwoCallout->start();
}

void MediaDialog::DMCDstart1() {
    m_cdOneCallout->start();
}

void MediaDialog::DMCDstartFight() {
    m_cdFightCallout->start();
}


void MediaDialog::leaveDMCountDownScreen() {
    qDebug() << "Leaving DM count down";
    stopAnimations();
}

void MediaDialog::enterDMPlayersReadyScreen() {
    qDebug() << "Entering DM players ready";
    ui->mainDisplay->setCurrentWidget(ui->deathMatchPlayersReadyPage);
    ui->deathMatchPlayersReadyPage->show();

}

void MediaDialog::leaveDMPlayersReadyScreen() {
    qDebug() << "Leaving DM players ready";
}

void MediaDialog::enterDMRunningScreen() {
    qDebug() << "Entering DM running Screen";
    ui->mainDisplay->setCurrentWidget(ui->deathMatchRunningPage);
}

void MediaDialog::leaveDMRunningScreen() {
    qDebug() << "Leaving DM running Screen";
}

void MediaDialog::enterDMWinnerDisplayScreen(QString playerName) {
    qDebug() << "Entering DM Winner screen";
    this->showWinnerScreen("confetti/main.qml", playerName);
    ui->mainDisplay->setCurrentWidget(ui->deathMatchWinnerPage);
}

void MediaDialog::leaveDMWinnerDisplayScreen() {
    qDebug() << "Leaving DM Winner screen";
}

void MediaDialog::enterSoccerConfigScreen() {
    qDebug() << "Entering Soccer config";
    ui->mainDisplay->setCurrentWidget(ui->soccerPage);
    m_soccer->play();
}

void MediaDialog::leaveSoccerConfigScreen() {
    qDebug() << "Leaving Soccer config";
}

void MediaDialog::enterSoccerPlayersReadyScreen() {
    qDebug() << "Entering Soccer players ready";
    ui->mainDisplay->setCurrentWidget(ui->soccerPlayersReadyPage);
}

void MediaDialog::leaveSoccerPlayersReadyScreen() {
    qDebug() << "Leaving Soccer players ready";
}

void MediaDialog::enterSoccerRunningScreen() {
    qDebug() << "Entering Soccer Running Screen";
    ui->mainDisplay->setCurrentWidget(ui->soccerRunningPage);
}

void MediaDialog::leaveSoccerRunningScreen() {
    qDebug() << "Leaving Soccer Running Screen";
}

void MediaDialog::enterSoccerCountDownScreen() {
    qDebug() << "Enter Soccer Countdown Screen";
    ui->mainDisplay->setCurrentWidget(ui->countDownScreen);
}

void MediaDialog::leaveSoccerCountDownScreen() {
    qDebug() << "Leaving Soccer Countdown Screen";
    stopAnimations();
}

void MediaDialog::enterSoccerGameOverScreen() {
    qDebug() << "Enter Soccer game over screen";
    ui->mainDisplay->setCurrentWidget(ui->soccerGameOverPage);
}

void MediaDialog::leaveSoccerGameOverScreen() {
    qDebug() << "Leaving Soccer game over screen";
    stopAnimations();
}

void MediaDialog::updateDMRRemainingTime(int value) {
    ui->dmrTimeRemaining->setText(msToTimeRep(value));
}

void MediaDialog::updateDMRDoorDropTime(int value) {
    ui->dmrDDTimeRemaining->setText(msToTimeRep(value));
    // Convert time to MS and subtract the current value
    // because that the amount remaining.
    int ddTime = m_data->deathMatchConfig()->doorDropTime() * 1000;
    int timeElapsed = ddTime - value;
    float result = float(timeElapsed) / float(ddTime);
    ui->dmrDDProgessBar->setValue(int(result * 100));
}

void MediaDialog::staringDMR(int duration, bool needsDoorDropTimer, int doorDropTime) {
    ui->dmrDDTimeRemaining->show();
    if(needsDoorDropTimer) {
        ui->dmrDDTimeRemaining->setText(msToTimeRep(doorDropTime));
        ui->dmrDDTimeRemaining->show();
        ui->dmrDDProgessBar->show();
        ui->dmrDDProgessBar->setValue(0);
        ui->dmrDDtimeLabel->show();
    } else {
        ui->dmrDDTimeRemaining->hide();
        ui->dmrDDProgessBar->hide();
        ui->dmrDDtimeLabel->hide();
    }
    ui->dmrTimeRemaining->setText(msToTimeRep(duration));
}

void MediaDialog::showWinnerScreen(QString q, QString winningPlayer) {
    ui->mainDisplay->setCurrentWidget(ui->deathMatchWinnerPage);
    ui->dmWinnerWidget->setSource(q);
    ui->dmWinnerWidget->setWinner(winningPlayer);
    ui->dmWinnerWidget->startCelibration();
}

void MediaDialog::stopAnimations() {
    m_cdThreeCallout->stop();
    m_cdTwoCallout->stop();
    m_cdOneCallout->stop();
    m_cdFightCallout->stop();
    m_cdGoCallout->stop();
}
