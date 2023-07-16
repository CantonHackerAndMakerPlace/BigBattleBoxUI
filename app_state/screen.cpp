#include "screen.h"

Screen::Screen(QObject *parent)
    : QObject{parent}
    , m_currentScreen(Screen::InitialLoad)
{ }

void Screen::emitLeaveEvent(Screen::ScreenKind oldPage) {
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
        emit leaveDMCountDownScreen();
        break;

    case DMPlayersReadyScreen:
        emit leaveDMPlayersReadyScreen();
        break;

    case DMRunningScreen:
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
        emit leaveSoccerRunningScreen();
        break;

    case SoccerGameOverScreen:
        emit leaveSoccerGameOverScreen();
        break;

    case SoccerCountDownScreen:
        emit leaveSoccerCountDownScreen();
        break;
    }
}

void Screen::changeScreen(Screen::ScreenKind newPage,
                          Screen::ScreenKind oldPage,
                          QString name) {

    emitLeaveEvent(oldPage);
    // Enter signals.
    switch(newPage) {
        // Do nothing because we can never enter this screen.
        case InitialLoad: break;
        case ConfigurationScreen:
            emit enterConfigurationScreen();
            break;

        case GameSelectionScreen:
            emit enterGameSelectScreen();
            break;

        case DMConfigScreen:
            emit enterDMConfigScreen();
            break;

        case DMCountDownScreen:
            emit enterDMCountDownScreen();
            break;

        case DMPlayersReadyScreen:
            emit enterDMPlayersReadyScreen();
            break;

        case DMRunningScreen:
            emit enterDMRunningScreen();
            break;

        case DMWinnerDisplayScreen:
            emit enterDMWinnerDisplayScreen(name);
            break;

        case SoccerConfigScreen:
            emit enterSoccerConfigScreen();
            break;

        case SoccerPlayersReadyScreen:
            emit enterSoccerPlayersReadyScreen();
            break;

        case SoccerRunningScreen:
            emit enterSoccerRunningScreen();
            break;

        case SoccerGameOverScreen:
            emit enterSoccerGameOverScreen();
            break;

        case SoccerCountDownScreen:
            emit enterSoccerCountDownScreen();
            break;
    }
}

Screen::ScreenKind Screen::currentScreen() const {
    return m_currentScreen;
}

void Screen::changeToConfigurationScreen() {
    changeScreen(ConfigurationScreen, m_currentScreen);
}

void Screen::changeToGameSelectScreen() {
    changeScreen(GameSelectionScreen, m_currentScreen);
}

void Screen::changeToDMConfigScreen() {
    changeScreen(DMConfigScreen, m_currentScreen);
}

void Screen::changeToDMCountDownScreen() {
    changeScreen(DMCountDownScreen, m_currentScreen);
}

void Screen::changeToDMPlayersReadyScreen() {
    changeScreen(DMPlayersReadyScreen, m_currentScreen);
}

void Screen::changeToDMRunningScreen() {
    changeScreen(DMRunningScreen, m_currentScreen);
}

void Screen::changeToDMWinnerDisplayScreen(QString playerName) {
    changeScreen(DMWinnerDisplayScreen, m_currentScreen, playerName);
}

void Screen::changeToSoccerConfigScreen() {
    changeScreen(SoccerConfigScreen, m_currentScreen);
}

void Screen::changeToSoccerPlayersReadyScreen() {
    changeScreen(SoccerPlayersReadyScreen, m_currentScreen);
}

void Screen::changeToSoccerRunningScreen() {
    changeScreen(SoccerRunningScreen, m_currentScreen);
}

void Screen::changeToSoccerCountDownScreen() {
    changeScreen(SoccerCountDownScreen, m_currentScreen);
}

void Screen::changeToSoccerGameOverScreen() {
    changeScreen(SoccerGameOverScreen, m_currentScreen);
}
