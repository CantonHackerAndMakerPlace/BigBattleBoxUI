#ifndef COUNTDOWNCONFIGWIDGET_H
#define COUNTDOWNCONFIGWIDGET_H

#include <QWidget>
#include "app_state/led/ledalgoconfig/countdownfillconfig.h"

namespace Ui {
class CountDownConfigWidget;
}

class CountDownConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CountDownConfigWidget(QWidget *parent = nullptr);
    ~CountDownConfigWidget();

    bool hasChanges() const;
public slots:
    void init(CountDownFillConfig *config);
    void restorePreviousValue();
    void restoreDefaultValue();
    void save();
private:
    Ui::CountDownConfigWidget *ui;
    CountDownFillConfig *m_config = nullptr;
};

#endif // COUNTDOWNCONFIGWIDGET_H
