#ifndef CYLONCONFIGWIDGET_H
#define CYLONCONFIGWIDGET_H

#include <QWidget>
#include "app_state/led/generalledconfiguration.h"
#include "app_state/led/ledalgoconfig/cylonconfig.h"

namespace Ui {
class CylonConfigWidget;
}

class CylonConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CylonConfigWidget(QWidget *parent = nullptr);
    ~CylonConfigWidget();

    bool hasChanges() const;
public slots:
    void init(CylonConfig *config);
    void restorePreviousValue();
    void restoreDefaultValue();
    void save();

private:
    template<typename T>
    void connectToControlButtons(T *page);

    Ui::CylonConfigWidget *ui;
    CylonConfig *m_config = nullptr;
};

#endif // CYLONCONFIGWIDGET_H
