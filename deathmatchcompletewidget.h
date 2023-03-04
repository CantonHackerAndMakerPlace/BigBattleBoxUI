#ifndef DEATHMATCHCOMPLETEWIDGET_H
#define DEATHMATCHCOMPLETEWIDGET_H

#include <QWidget>

namespace Ui {
class DeathMatchCompleteWidget;
}

class DeathMatchCompleteWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DeathMatchCompleteWidget(QWidget *parent = nullptr);
    ~DeathMatchCompleteWidget();

private:
    Ui::DeathMatchCompleteWidget *ui;
};

#endif // DEATHMATCHCOMPLETEWIDGET_H
