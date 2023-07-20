#ifndef APPLICATIONSTATE_H
#define APPLICATIONSTATE_H

#include <QObject>
#include "app_state/screen.h"

/// The goal of this class is to managed the global state of the program's UI
/// and any of the other state associated with it. The goal of this
/// refactoring is to ensure that all of the events go through a single place
/// that isn't part of a widget. This allows us to more easilly control
/// state by enfocing all changes go through the ApplicaitonState.
class ApplicationState : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationState(QObject *parent = nullptr);

    /// Returns the screen changing event structure. This keeps track of
    /// and emits events related too when we switch screens.
    Screen *screen() const;
private:
    Screen *m_screen;
};

#endif // APPLICATIONSTATE_H
