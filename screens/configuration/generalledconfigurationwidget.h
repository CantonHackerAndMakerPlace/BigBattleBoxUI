#ifndef GENERALLEDCONFIGURATIONWIDGET_H
#define GENERALLEDCONFIGURATIONWIDGET_H

#include <QWidget>
#include <defaultrestorable.h>
#include <app_state/led/generalledconfiguration.h>

class QButtonGroup;
class ApplicationState;
class QSpinBox;

namespace Ui {
class GeneralLEDConfigurationWidget;
}

class GeneralLEDConfigurationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralLEDConfigurationWidget(QWidget *parent = nullptr);
    ~GeneralLEDConfigurationWidget();

    /// Indicates if there were changes made to this
    bool hasChanges() const;
private:

    // UI connecting functions
    void attachPlayerOne();
    void attachPlayerTwo();
    void attachSpinBox(DefaultRestorableInt *localValue, QSpinBox *sb);
    void attachButtonGroup(DefaultRestorableInt *localValue, QButtonGroup *bg);

    // Init functions.
    void attachPlayerOneAppState();
    void attachPlayerTwoAppState();
    void connectAppState(DefaultRestorableInt *localValue, IntegerObject* configuredValue);
public slots:
    void init(ApplicationState *state);
    void save();
    void cancel();
    void revertToDefault();
signals:
    void needsSaveOrCancel(bool value);

private:
    Ui::GeneralLEDConfigurationWidget *ui;
    ApplicationState *m_state = nullptr;
    GeneralLEDConfiguration *m_generalConfig = nullptr;
    QButtonGroup *m_p1Direction;
    QButtonGroup *m_p2Direction;
    QButtonGroup *m_ledOrderGroup;

    // Form controlled values.
    DefaultRestorableInt m_p1Pin;
    DefaultRestorableInt m_p1LEDCount;
    DefaultRestorableInt m_p1DirSelection;

    DefaultRestorableInt m_p2Pin;
    DefaultRestorableInt m_p2LEDCount;
    DefaultRestorableInt m_p2DirSelection;

    DefaultRestorableInt m_order;
};

#endif // GENERALLEDCONFIGURATIONWIDGET_H
