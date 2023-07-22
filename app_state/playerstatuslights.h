#ifndef PLAYERSTATUSLIGHTS_H
#define PLAYERSTATUSLIGHTS_H

#include <QWidget>
#include "stateindicatorwidget.h"

namespace Ui {
class PlayerStatusLights;
}

class PlayerStatusLights : public QWidget
{
    Q_OBJECT
//    Q_PROPERTY(/*type*/ name READ name WRITE setName NOTIFY nameChanged)
public:
    explicit PlayerStatusLights(QWidget *parent = nullptr);
    ~PlayerStatusLights();

    StateIndicatorWidget *readyState() const;
    StateIndicatorWidget *readyState();

    StateIndicatorWidget *doorState() const;
    StateIndicatorWidget *doorState();

    StateIndicatorWidget *trapDoorState() const;
    StateIndicatorWidget *trapDoorState();

    StateIndicatorWidget *conceedState() const;
    StateIndicatorWidget *conceedState();
private:
    Ui::PlayerStatusLights *ui;
};

#endif // PLAYERSTATUSLIGHTS_H
