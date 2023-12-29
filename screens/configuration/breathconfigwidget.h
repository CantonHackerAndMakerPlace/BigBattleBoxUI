#ifndef BREATHCONFIGWIDGET_H
#define BREATHCONFIGWIDGET_H

#include <QWidget>
#include "app_state/led/ledalgoconfig/breathconfig.h"

namespace Ui {
class BreathConfigWidget;
}

class BreathConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BreathConfigWidget(QWidget *parent = nullptr);
    ~BreathConfigWidget();

    bool hasChanges() const;
public slots:
    void init(BreathConfig *config);
    void restorePreviousValue();
    void restoreDefaultValue();
    void save();
private:
    Ui::BreathConfigWidget *ui;
    BreathConfig *m_config = nullptr;
};

#endif // BREATHCONFIGWIDGET_H
