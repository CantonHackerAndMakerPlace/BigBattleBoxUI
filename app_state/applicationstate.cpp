#include "applicationstate.h"

ApplicationState::ApplicationState(QObject *parent)
    : QObject{parent}
    , m_screen(new Screen(this))
{

}

Screen *ApplicationState::screen() const {
    return m_screen;
}
