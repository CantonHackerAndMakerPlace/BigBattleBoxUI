#ifndef MEDIADIALOG_H
#define MEDIADIALOG_H

#include <QDialog>
#include <QHash>
#include <QLabel>
#include <functional>
#include <battleboxviewmodel.h>

class BattleBoxMainWindow;
class SoundEffectMedia;

class QAudioOutput;
class QMediaPlayer;
class QMovie;
class QParallelAnimationGroup;
class QGraphicsOpacityEffect;
class QSoundEffect;
class QAudioDevice;

namespace Ui {
class MediaDialog;
}

class MediaDialog : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(float volume READ volume WRITE setVolume NOTIFY volumeChanged)
public:
    explicit MediaDialog(BattleBoxViewModel *data, BattleBoxMainWindow *parent = nullptr);
    ~MediaDialog();

private:

    void initSoundEffect(SoundEffectMedia *effect,
                         const char* resourceFilePathKey,
                         const char* fsSettingsKey,
                         const char* relativePath);
    using Callback = std::function<void(QParallelAnimationGroup *)>;
    void initAnimatedSoundEffect(SoundEffectMedia *effect,
                                 const char* resourceKey,
                                 const char* fsSettingsKey,
                                 const char* relativePath,
                          QLabel *toUpdate, QString text,
                         Callback cb);


    void init();
    BattleBoxMainWindow *mainWindow() const;

    void initialzieDeathMatchRunning();
public:
    void loadSettingsDependentResources();
    float volume() const { return m_volume; }
public slots:
    void setVolume(float vol) {
        if (m_volume != vol) {
            m_volume = vol;
            emit volumeChanged(m_volume);
        }
    }
public slots:
    // All of the signals for screen switching.
    void enterGameSelectScreen();
    void leaveGameSelectScreen();

    void enterDMConfigScreen();
    void leaveDMConfigScreen();

    void enterDMCountDownScreen();
    void DMCDstart3();
    void DMCDstart2();
    void DMCDstart1();
    void DMCDstartFight();
    void leaveDMCountDownScreen();

    void enterDMPlayersReadyScreen();
    void leaveDMPlayersReadyScreen();

    void enterDMRunningScreen();
    void leaveDMRunningScreen();

    void enterDMWinnerDisplayScreen(QString playerName);
    void leaveDMWinnerDisplayScreen();

    void enterSoccerConfigScreen();
    void leaveSoccerConfigScreen();

    void leaveSoccerPlayersReadyScreen();
    void enterSoccerPlayersReadyScreen();

    void enterSoccerRunningScreen();
    void leaveSoccerRunningScreen();

    void enterSoccerCountDownScreen();
    void leaveSoccerCountDownScreen();

    void enterSoccerGameOverScreen();
    void leaveSoccerGameOverScreen();

    void updateDMRRemainingTime(int var);
    void updateDMRDoorDropTime(int var);
    void staringDMR(int duration, bool needsDoorDropTimer, int doorDropTime);

    void showWinnerScreen(QString path, QString winningPlayer);
signals:
    void volumeChanged(float);
private:
    void stopAnimations();
private:
    Ui::MediaDialog *ui;
    BattleBoxViewModel *m_data;
    float m_volume;
    QMovie *m_champCoin;
    QAudioOutput *m_out;
//    SoundEffectMedia *m_deathMatchSound;
    SoundEffectMedia *m_deathMatch;
    SoundEffectMedia *m_soccer;
    SoundEffectMedia *m_three;
    SoundEffectMedia *m_two;
    SoundEffectMedia *m_one;
    SoundEffectMedia *m_fight;
    SoundEffectMedia *m_go;
    QGraphicsOpacityEffect *m_cdEff;
    QParallelAnimationGroup *m_cdThreeCallout;
    QParallelAnimationGroup *m_cdTwoCallout;
    QParallelAnimationGroup *m_cdOneCallout;
    QParallelAnimationGroup *m_cdFightCallout;
    QParallelAnimationGroup *m_cdGoCallout;
};

#endif // MEDIADIALOG_H
