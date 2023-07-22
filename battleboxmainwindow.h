#ifndef BATTLEBOXMAINWINDOW_H
#define BATTLEBOXMAINWINDOW_H

#include <QMainWindow>
#include <QAbstractAnimation>
#include <QMetaMethod>

class QPushButton;
class BattleBoxViewModel;
class SoccerMatch;
class DeathMatchConfig;
class QSequentialAnimationGroup;
class QFileSystemWatcher;
class MediaDialog;
class BattleBoxPhysicalState;
class PhysicalButton;

QT_BEGIN_NAMESPACE
namespace Ui { class BattleBoxMainWindow; }
QT_END_NAMESPACE



class BattleBoxMainWindow : public QMainWindow
{
    Q_OBJECT
    Q_ENUMS(Screen)
public:
    BattleBoxMainWindow(QWidget *parent = nullptr);
    ~BattleBoxMainWindow();

    void connectPlayerName();

    enum Screen {
        /// Used as the initial screen's old screen.
        InitialLoad,
        ConfigurationScreen,
        GameSelectionScreen,
        DMConfigScreen,
        DMCountDownScreen,
        DMPlayersReadyScreen,
        DMRunningScreen,
        DMWinnerDisplayScreen,
        SoccerConfigScreen,
        SoccerPlayersReadyScreen,
        SoccerRunningScreen,
        SoccerGameOverScreen,
        SoccerCountDownScreen,
    };
public:
    DeathMatchConfig *deathMatchConfig() const;
private:
    void initSettings();

    void attachSettingToSwitch(PhysicalButton *button, const char* settingsKey);

    // Initializing the battle box external state.
    void initBattleBoxState();

    void initializeSystemConfigurationScreen();

    // Media initialization
    void initMediaDialog();


    // multiscreen initializations
    void initQuickSelectWidgets();

    // Game selection screen initializations
    void initGameSelectScreen();

    // Deathmatch init
    void initDeathMatchConfigScreen();
    void initDeathMatchCountDownScreen();
    void initDeathMatchPlayersReadyScreen();
    void initDeathMatchRunningScreen();
    void initDeathMatchWinnerScreen();

    // Soccer Configuration
    void initSoccerConfigScreen();
    void initSoccerPlayersReadyScreen();
    void initSoccerCountDownScreen();
    void initSoccerRunningScreen();
    void initSoccerGameOverScreen();

    // Selection Screen slots
    void on_soccerConfigButton_clicked();

    // Death match configuration screen slots
    void on_dmCfgSaveButton_clicked();
    void on_dmCfgLoadButton_clicked();

    // Death match player ready screen slots
    void on_dmprPlayerOneReadyButton_clicked();
    void on_dmprPlayerTwoReadyButton_clicked();

    void on_soccerCfgSaveButton_clicked();
    void on_soccerCfgLoadButton_clicked();

    // Screen switching with signal emitting and this is to make it easier to
    // navigate between screens.
    void changeScreen(BattleBoxMainWindow::Screen newPage,
                      BattleBoxMainWindow::Screen oldPage);
    Screen currentScreen() const;

    void loadQuickLoadFiles(QString dir);
private slots:
    void setCurrentScreen(BattleBoxMainWindow::Screen newScreen);

public slots:
    void receivedError(QString msg);
private:

signals:
    // Configuration screen buttons.
    void enterConfigurationScreen();
    void leaveConfigurationScreen();

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


private slots:
    void dmprUpdateP1ReadyText(QString arg);
    void dmprUpdateP2ReadyText(QString arg);
    void dmprUpdateP1DoorText(QString arg);
    void dmprUpdateP2DoorText(QString arg);

    // Soccer team(player) ready
    void sprUpdateT1ReadyText(QString arg);
    void sprUpdateT2ReadyText(QString arg);

    void updateQuickLoadFiles(QString dir);


private:
    Ui::BattleBoxMainWindow *ui;
    BattleBoxPhysicalState *m_boxState;

    BattleBoxViewModel *m_data;
    QSequentialAnimationGroup *m_dmcdAnimationGroup;
    QSequentialAnimationGroup *m_scdAnimationGroup;
    Screen m_currentScreen;
    QFileSystemWatcher *m_dirWatcher;

    MediaDialog *m_mediaScreen;

};
#endif // BATTLEBOXMAINWINDOW_H
