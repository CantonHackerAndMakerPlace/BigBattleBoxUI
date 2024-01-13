#ifndef LEDCONTROLWIDGET_H
#define LEDCONTROLWIDGET_H

#include "qtreewidget.h"
#include <QWidget>
#include <app_state/applicationstate.h>
#include <QHash>

class QTreeWidgetItem;

namespace Ui {
class LEDControlWidget;
}

class LEDControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LEDControlWidget(QWidget *parent = nullptr);
    ~LEDControlWidget();

    void init(ApplicationState *state);

private slots:
    void selectionChangedChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
private:
//    void buildGeneral();
//    void buildIdle();
    void buildDeathMatch();
    void buildSoccer();
private:
    Ui::LEDControlWidget *ui;
    ApplicationState *m_state;
    QHash<QTreeWidgetItem*, QWidget*> m_itemToPage;
    QTreeWidgetItem *m_general = nullptr;
    QTreeWidgetItem *m_idleScreen = nullptr;
    QTreeWidgetItem *m_deathMatch = nullptr;
    QTreeWidgetItem *m_dmConfig = nullptr;
    QTreeWidgetItem *m_dmPlayersReady = nullptr;
    QTreeWidgetItem *m_dmRunningLights = nullptr;
    QTreeWidgetItem *m_dmCountDownDoorDrop = nullptr;
    QTreeWidgetItem *m_dmDoorDrop = nullptr;
    QTreeWidgetItem *m_dmCountDownMatchOver = nullptr;
    QTreeWidgetItem *m_dmPlayerWins = nullptr;
    QTreeWidgetItem *m_soccer = nullptr;
    QTreeWidgetItem *m_soccerConfig = nullptr;
    QTreeWidgetItem *m_soccerPlayerReady = nullptr;
    QTreeWidgetItem *m_soccerRunningLights = nullptr;
    QTreeWidgetItem *m_soccerCountDownMatchOver = nullptr;
    QTreeWidgetItem *m_soccerWinner = nullptr;
};

#endif // LEDCONTROLWIDGET_H
