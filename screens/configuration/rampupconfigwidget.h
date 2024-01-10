#ifndef RAMPUPCONFIGWIDGET_H
#define RAMPUPCONFIGWIDGET_H

#include <QWidget>
#include "app_state/led/ledalgoconfig/rampupconfig.h"

namespace Ui {
class RampUpConfigWidget;
}

class RampUpConfigWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool disableDuration READ disableDuration WRITE setDisableDuration NOTIFY disableDurationChanged FINAL)
public:
    explicit RampUpConfigWidget(QWidget *parent = nullptr);
    ~RampUpConfigWidget();

    bool disableDuration() const;
    bool hasChanges() const;
public slots:
    void init(RampUpConfig *config);
    void restorePreviousValue();
    void restoreDefaultValue();
    void save();
    void setDisableDuration(bool value);
signals:
    void disableDurationChanged(bool value);

private:
    Ui::RampUpConfigWidget *ui;
    RampUpConfig *m_config = nullptr;
};

#endif // RAMPUPCONFIGWIDGET_H
