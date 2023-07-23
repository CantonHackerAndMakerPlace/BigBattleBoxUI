#include "screen.h"

Screen::Screen(QObject *parent)
    : QObject{parent}
    , m_currentScreen(Screen::ScreenKind::InitialLoad)
{ }

void Screen::emitLeaveEvent(Screen::ScreenKind oldPage) {
    // Leaving signals.
    switch(oldPage) {
    // Do nothing here.
    case ScreenKind::InitialLoad: break;
    case ScreenKind::ConfigurationScreen:
        emit leaveConfigurationScreen();
        break;

    case ScreenKind::GameSelectionScreen:
        emit leaveGameSelectScreen();
        break;

    case ScreenKind::DMConfigScreen:
        emit leaveDMConfigScreen();
        break;

    case ScreenKind::DMCountDownScreen:
        emit leaveDMCountDownScreen();
        break;

    case ScreenKind::DMPlayersReadyScreen:
        emit leaveDMPlayersReadyScreen();
        break;

    case ScreenKind::DMRunningScreen:
        emit leaveDMRunningScreen();
        break;

    case ScreenKind::DMWinnerDisplayScreen:
        emit leaveDMWinnerDisplayScreen();
        break;

    case ScreenKind::SoccerConfigScreen:
        emit leaveSoccerConfigScreen();
        break;

    case ScreenKind::SoccerPlayersReadyScreen:
        emit leaveSoccerPlayersReadyScreen();
        break;

    case ScreenKind::SoccerRunningScreen:
        emit leaveSoccerRunningScreen();
        break;

    case ScreenKind::SoccerGameOverScreen:
        emit leaveSoccerGameOverScreen();
        break;

    case ScreenKind::SoccerCountDownScreen:
        emit leaveSoccerCountDownScreen();
        break;
    }
}

void Screen::setCurrentScreen(ScreenKind newScreen) {
    if(newScreen != currentScreen()) {
        std::swap(m_currentScreen, newScreen);
        changeScreen(currentScreen(), newScreen);
    }
}

void Screen::changeScreen(Screen::ScreenKind newPage,
                          Screen::ScreenKind oldPage,
                          QString name) {

    emitLeaveEvent(oldPage);
    // Enter signals.
    switch(newPage) {
        // Do nothing because we can never enter this screen.
        case ScreenKind::InitialLoad: break;
        case ScreenKind::ConfigurationScreen:
            emit enterConfigurationScreen();
            break;

        case ScreenKind::GameSelectionScreen:
            emit enterGameSelectScreen();
            break;

        case ScreenKind::DMConfigScreen:
            emit enterDMConfigScreen();
            break;

        case ScreenKind::DMCountDownScreen:
            emit enterDMCountDownScreen();
            emit postEnterDMCountDownScreen();
            break;

        case ScreenKind::DMPlayersReadyScreen:
            emit enterDMPlayersReadyScreen();
            break;

        case ScreenKind::DMRunningScreen:
            emit enterDMRunningScreen();
            break;

        case ScreenKind::DMWinnerDisplayScreen:
            emit enterDMWinnerDisplayScreen(name);
            break;

        case ScreenKind::SoccerConfigScreen:
            emit enterSoccerConfigScreen();
            break;

        case ScreenKind::SoccerPlayersReadyScreen:
            emit enterSoccerPlayersReadyScreen();
            break;

        case ScreenKind::SoccerRunningScreen:
            emit enterSoccerRunningScreen();
            break;

        case ScreenKind::SoccerGameOverScreen:
            emit enterSoccerGameOverScreen();
            break;

        case ScreenKind::SoccerCountDownScreen:
            emit enterSoccerCountDownScreen();
            break;
    }
}

Screen::ScreenKind Screen::currentScreen() const {
    return m_currentScreen;
}

void Screen::changeToConfigurationScreen() {
    changeScreen(ScreenKind::ConfigurationScreen, m_currentScreen);
}

void Screen::changeToGameSelectScreen() {
    changeScreen(ScreenKind::GameSelectionScreen, m_currentScreen);
}

void Screen::changeToDMConfigScreen() {
    changeScreen(ScreenKind::DMConfigScreen, m_currentScreen);
}

void Screen::changeToDMCountDownScreen() {
    changeScreen(ScreenKind::DMCountDownScreen, m_currentScreen);
}

void Screen::changeToDMPlayersReadyScreen() {
    changeScreen(ScreenKind::DMPlayersReadyScreen, m_currentScreen);
}

void Screen::changeToDMRunningScreen() {
    changeScreen(ScreenKind::DMRunningScreen, m_currentScreen);
}

void Screen::changeToDMWinnerDisplayScreen(QString playerName) {
    changeScreen(ScreenKind::DMWinnerDisplayScreen, m_currentScreen, playerName);
}

void Screen::changeToSoccerConfigScreen() {
    changeScreen(ScreenKind::SoccerConfigScreen, m_currentScreen);
}

void Screen::changeToSoccerPlayersReadyScreen() {
    changeScreen(ScreenKind::SoccerPlayersReadyScreen, m_currentScreen);
}

void Screen::changeToSoccerRunningScreen() {
    changeScreen(ScreenKind::SoccerRunningScreen, m_currentScreen);
}

void Screen::changeToSoccerCountDownScreen() {
    changeScreen(ScreenKind::SoccerCountDownScreen, m_currentScreen);
}

void Screen::changeToSoccerGameOverScreen() {
    changeScreen(ScreenKind::SoccerGameOverScreen, m_currentScreen);
}
