#ifndef BUTTONCONFIGWIDGET_H
#define BUTTONCONFIGWIDGET_H

#include <QWidget>
#include "physical_state/physicalbutton.h"

namespace Ui {
class ButtonConfigWidget;
}

class ButtonConfigWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(PhysicalButton::SwitchConfig switchKind READ switchKind WRITE setSwitchKind NOTIFY switchKindChanged)
public:
    explicit ButtonConfigWidget(QWidget *parent = nullptr);
    ~ButtonConfigWidget();

    PhysicalButton::SwitchConfig switchKind() const;
public slots:
    void setSwitchKind(PhysicalButton::SwitchConfig kind);
signals:
    void switchKindChanged(PhysicalButton::SwitchConfig kind);
private:
    Ui::ButtonConfigWidget *ui;
    PhysicalButton::SwitchConfig m_kind;

};

#endif // BUTTONCONFIGWIDGET_H
