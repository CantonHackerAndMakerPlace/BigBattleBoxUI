#ifndef SOLIDCOLORCONFIGWIDGET_H
#define SOLIDCOLORCONFIGWIDGET_H

#include <QWidget>
#include "app_state/led/ledalgoconfig/solidcolorconfig.h"

namespace Ui {
class SolidColorConfigWidget;
}

class SolidColorConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SolidColorConfigWidget(QWidget *parent = nullptr);
    ~SolidColorConfigWidget();
    bool hasChanges() const;
public slots:
    void init(SolidColorConfig *config);
    void restorePreviousValue();
    void restoreDefaultValue();
    void save();
private:
    Ui::SolidColorConfigWidget *ui;
    SolidColorConfig *m_config = nullptr;
};

#endif // SOLIDCOLORCONFIGWIDGET_H
