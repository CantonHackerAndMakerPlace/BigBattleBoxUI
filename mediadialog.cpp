#include "mediadialog.h"
#include "ui_mediadialog.h"
#include "battleboxmainwindow.h"
#include "triggeringanimation.h"

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

// TODO: replace these with settings file.
constexpr const char* THREE_SOUND = "qrc:/battlebox/media/sounds/resources/sounds/Three.wav";
constexpr const char* TWO_SOUND = "qrc:/battlebox/media/sounds/resources/sounds/Two.wav";
constexpr const char* ONE_SOUND = "qrc:/battlebox/media/sounds/resources/sounds/One.wav";
constexpr const char* FIGHT_SOUND = "qrc:/battlebox/media/sounds/resources/sounds/Fight.wav";
constexpr const char* DEATHMATCH_SOUND = "qrc:/battlebox/media/sounds/resources/sounds/DeathMatch.wav";
constexpr const char* GO_SOUND = "qrc:/battlebox/media/sounds/resources/sounds/Go_Angry.wav";
constexpr const char* SOCCER_SOUND = "qrc:/battlebox/media/sounds/resources/sounds/Soccer.wav";

constexpr const char* THREE_SOUND_FILE = "/home/battlbox/Projects/BattleBox/resources/sounds/Three.wav";
constexpr const char* TWO_SOUND_FILE = "/home/battlbox/Projects/BattleBox/resources/sounds/Two.wav";
constexpr const char* ONE_SOUND_FILE = "/home/battlbox/Projects/BattleBox/resources/sounds/One.wav";
constexpr const char* FIGHT_SOUND_FILE = "/home/battlbox/Projects/BattleBox/resources/sounds/Fight.wav";
constexpr const char* GO_SOUND_FILE = "/home/battlbox/Projects/BattleBox/resources/sounds/Go_Angry.wav";

MediaDialog::MediaDialog(BattleBoxViewModel *data, BattleBoxMainWindow *parent)
    : QDialog(parent)
    , ui(new Ui::MediaDialog)
    , m_data(data)
    , m_champCoin(
          new QMovie(
              ":/battlebox/media/images/resources/SpinningCoin_50.gif",
              QByteArray(),
              this
              )
          )
    , m_out(new QAudioOutput(this))
    , m_deathMatch(new QSoundEffect(m_out->device(), this))
    , m_soccer(new QSoundEffect(m_out->device(), this))
    , m_three(new QSoundEffect(m_out->device(), this))
    , m_two(new QSoundEffect(m_out->device(), this))
    , m_one(new QSoundEffect(m_out->device(), this))
    , m_fight(new QSoundEffect(m_out->device(), this))
    , m_go(new QSoundEffect(m_out->device(), this))
{
    ui->setupUi(this);

    // Loading movies from contents.
    ui->coinDisplayLabel->setMovie(m_champCoin);
    ui->coinDisplayLabel->setScaledContents(true);
    m_champCoin->start();

    initSounds();
    initAnimations();
    init();
}

MediaDialog::~MediaDialog()
{
    delete ui;
}
void MediaDialog::initSounds() {
    initSoundEffect(m_deathMatch, DEATHMATCH_SOUND);
    initSoundEffect(m_soccer, SOCCER_SOUND);
    initSoundEffect(m_three, THREE_SOUND);
    initSoundEffect(m_two, TWO_SOUND);
    initSoundEffect(m_one, ONE_SOUND);
    initSoundEffect(m_fight, FIGHT_SOUND);
    initSoundEffect(m_go, GO_SOUND);
    setVolume(1.0f);
}

void MediaDialog::initSoundEffect(QSoundEffect *effect, const char* file) {

    connect(this, &MediaDialog::volumeChanged,
            effect, &QSoundEffect::setVolume);
    effect->setLoopCount(1);
    effect->setVolume(1.0f);
    effect->setSource(QUrl(file));
    assert(!effect->isLoaded());
    assert(!effect->isMuted());
}

void MediaDialog::initAnimations() {
    m_cdEff = new QGraphicsOpacityEffect(ui->countDownTextLabel);
    ui->countDownTextLabel->setGraphicsEffect(m_cdEff);
    buildCoundDownAnimation(
                ui->countDownTextLabel,
                "3",
                THREE_SOUND_FILE,
                m_three,
                [&](QParallelAnimationGroup *g){
        qDebug() << "Setting m_cdThreeCallout";
        m_cdThreeCallout = g;
    });
    buildCoundDownAnimation(
                ui->countDownTextLabel,
                "2",
                TWO_SOUND_FILE,
                m_two,
                [&](QParallelAnimationGroup *g){
        qDebug() << "Setting m_cdTwoCallout";
        m_cdTwoCallout = g;
    });
    buildCoundDownAnimation(
                ui->countDownTextLabel,
                "1",
                ONE_SOUND_FILE,
                m_one,
                [&](QParallelAnimationGroup *g){
        m_cdOneCallout = g;
        qDebug() << "Setting m_cdOneCallout";
    });

    buildCoundDownAnimation(
                ui->countDownTextLabel,
                "FIGHT!!!!",
                FIGHT_SOUND_FILE,
                m_fight,
                [&](QParallelAnimationGroup *g) {
        m_cdFightCallout = g;
        qDebug() << "Setting m_cdFightCallout";
    });
    buildCoundDownAnimation(
                ui->countDownTextLabel,
                "GO!!!!",
                GO_SOUND_FILE,
                m_go,
                [&](QParallelAnimationGroup *g){
        qDebug() << "Setting m_cdGoCallout";
        m_cdGoCallout = g;
    });
}

void MediaDialog::buildCoundDownAnimation(QLabel *toUpdate, QString text, const char* sound_file,
                                          QSoundEffect* effect, Callback cb) {
    auto *decoder = new QAudioDecoder(this);
    decoder->setSource(QUrl::fromLocalFile(sound_file));
    QAudioFormat format;
    format.setSampleRate(48000);
    format.setChannelCount(1);
    decoder->setAudioFormat(format);
    connect(decoder, &QAudioDecoder::durationChanged,
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
                    toUpdate->setText(text);
                }
            });
            group->addAnimation(a);
        }
        if (dur >1000) {
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
                    qDebug() << "Called TriggeringAnimation::Finished!";
                    effect->play();
                }
            });
            group->addAnimation(a);
        }

        cb(group);
    });

    using MFP = void(QAudioDecoder::*)(QAudioDecoder::Error);
    connect(decoder, MFP(&QAudioDecoder::error),
            [=](QAudioDecoder::Error error) {
        qDebug() << "Test " << error;
    });
    decoder->start();
}

void MediaDialog::init() {
#define SCREEN_SWITCH_CONNECT(SIG_SLOT_NAME)\
    connect(mainWindow(), &BattleBoxMainWindow::SIG_SLOT_NAME,\
            this, &MediaDialog::SIG_SLOT_NAME)

    SCREEN_SWITCH_CONNECT(enterGameSelectScreen);
    SCREEN_SWITCH_CONNECT(leaveGameSelectScreen);

    SCREEN_SWITCH_CONNECT(enterDMConfigScreen);
    SCREEN_SWITCH_CONNECT(leaveDMConfigScreen);

    SCREEN_SWITCH_CONNECT(enterDMCountDownScreen);
    SCREEN_SWITCH_CONNECT(DMCDstart3);
    SCREEN_SWITCH_CONNECT(DMCDstart2);
    SCREEN_SWITCH_CONNECT(DMCDstart1);
    SCREEN_SWITCH_CONNECT(DMCDstartFight);
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
//    qDebug() << "Druation: " << m_player->duration();
//    qDebug() << "Buffer progress: " << m_player->bufferProgress();
}

void MediaDialog::leaveDMConfigScreen() {
    qDebug() << "leaving dm config";

}

void MediaDialog::enterDMCountDownScreen() {
    qDebug() << "Entering DM count down";
    ui->mainDisplay->setCurrentWidget(ui->countDownScreen);
}

void MediaDialog::DMCDstart3() {
    m_cdThreeCallout->start();
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

void MediaDialog::stopAnimations() {
    m_cdThreeCallout->stop();
    m_cdTwoCallout->stop();
    m_cdOneCallout->stop();
    m_cdFightCallout->stop();
    m_cdGoCallout->stop();
}
