#ifndef BLINKCONFIGWIDGET_H
#define BLINKCONFIGWIDGET_H

#include <QWidget>
#include "app_state/led/ledalgoconfig/blinkconfig.h"

namespace Ui {
class BlinkConfigWidget;
}

class BlinkConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BlinkConfigWidget(QWidget *parent = nullptr);
    ~BlinkConfigWidget();
    bool hasChanges() const;
public slots:
    void init(BlinkConfig *config);
    void restorePreviousValue();
    void restoreDefaultValue();
    void save();
private:
    Ui::BlinkConfigWidget *ui;
    BlinkConfig *m_config = nullptr;
};

#endif // BLINKCONFIGWIDGET_H
