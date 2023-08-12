#ifndef GENERALLEDCONFIGURATIONWIDGET_H
#define GENERALLEDCONFIGURATIONWIDGET_H

#include <QWidget>
class QButtonGroup;
class ApplicationState;

namespace Ui {
class GeneralLEDConfigurationWidget;
}

template<typename T>
class Restorable : public QObject{
public:
private:
};

class GeneralLEDConfigurationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralLEDConfigurationWidget(QWidget *parent = nullptr);
    ~GeneralLEDConfigurationWidget();

    void init(ApplicationState *state);
private:
    Ui::GeneralLEDConfigurationWidget *ui;
    QButtonGroup *m_p1Direction;
    QButtonGroup *m_p2Direction;
    ApplicationState *m_state;
    // Current values
    // Previous values.
    int m_p1CurrentPin;
    int m_p1PreviousPin;
};

#endif // GENERALLEDCONFIGURATIONWIDGET_H
