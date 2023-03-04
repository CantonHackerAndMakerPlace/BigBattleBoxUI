#ifndef SOCCERGAMEOVERWIDGET_H
#define SOCCERGAMEOVERWIDGET_H

#include <QWidget>

namespace Ui {
class SoccerGameOverWidget;
}

class SoccerGameOverWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SoccerGameOverWidget(QWidget *parent = nullptr);
    ~SoccerGameOverWidget();

private:
    Ui::SoccerGameOverWidget *ui;
};

#endif // SOCCERGAMEOVERWIDGET_H
