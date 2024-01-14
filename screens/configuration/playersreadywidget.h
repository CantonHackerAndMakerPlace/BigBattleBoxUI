#ifndef PLAYERSREADYWIDGET_H
#define PLAYERSREADYWIDGET_H

#include <QWidget>
#include "app_state/led/playerreadyledlightconfiguration.h"

namespace Ui {
class PlayersReadyWidget;
}

class PlayersReadyWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
public:
    explicit PlayersReadyWidget(QWidget *parent = nullptr);
    ~PlayersReadyWidget();
    bool hasChanges() const;
    QString title() const;
public slots:
    void init(PlayerReadyLEDLightConfiguration *config);
    void setTitle(QString value);
signals:
    void titleChanged(QString value);
    void restorePreviousValue();
    void restoreDefaultValue();
    void save();

    void changesWereMade();
private:
    template<typename T>
    void listenForChanges(T* uiElement);
private:
    Ui::PlayersReadyWidget *ui;
    PlayerReadyLEDLightConfiguration *m_config = nullptr;
};

#endif // PLAYERSREADYWIDGET_H
