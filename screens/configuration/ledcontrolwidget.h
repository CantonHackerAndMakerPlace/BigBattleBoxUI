#ifndef LEDCONTROLWIDGET_H
#define LEDCONTROLWIDGET_H

#include "qtreewidget.h"
#include <QWidget>
#include <app_state/applicationstate.h>
#include <QHash>

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
    Ui::LEDControlWidget *ui;
    ApplicationState *m_state;
    QHash<QString, QWidget*> m_itemToPage;
};

#endif // LEDCONTROLWIDGET_H
