#ifndef SCREEN_H
#define SCREEN_H

#include <QObject>

class Screen : public QObject
{
    Q_OBJECT
public:
    enum ScreenKind {
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

    explicit Screen(QObject *parent = nullptr);
public:
    void changeScreen(Screen::ScreenKind newPage,
                      Screen::ScreenKind oldPage,
                      QString name = "");
private:
    void emitLeaveEvent(Screen::ScreenKind oldPage);
public:
    ScreenKind currentScreen() const;

public slots:
    void changeToConfigurationScreen();
    void changeToGameSelectScreen();
    void changeToDMConfigScreen();
    void changeToDMCountDownScreen();
    void changeToDMCDstartFight();
    void changeToDMPlayersReadyScreen();
    void changeToDMRunningScreen();
    void changeToDMWinnerDisplayScreen(QString playerName);
    void changeToSoccerConfigScreen();
    void changeToSoccerPlayersReadyScreen();
    void changeToSoccerRunningScreen();
    void changeToSoccerCountDownScreen();
    void changeToSoccerGameOverScreen();

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

    void enterSoccerPlayersReadyScreen();
    void leaveSoccerPlayersReadyScreen();

    void enterSoccerRunningScreen();
    void leaveSoccerRunningScreen();

    void enterSoccerCountDownScreen();
    void leaveSoccerCountDownScreen();

    void enterSoccerGameOverScreen();
    void leaveSoccerGameOverScreen();
private:
    ScreenKind m_currentScreen;
};

#endif // SCREEN_H
