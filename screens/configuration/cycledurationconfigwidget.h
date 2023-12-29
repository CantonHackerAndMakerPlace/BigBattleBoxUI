#ifndef CYCLEDURATIONCONFIGWIDGET_H
#define CYCLEDURATIONCONFIGWIDGET_H

#include <QWidget>
#include "defaultrestorable.h"
#include "integerobject.h"


namespace Ui {
class CycleDurationConfigWidget;
}

class CycleDurationConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CycleDurationConfigWidget(QWidget *parent = nullptr);
    ~CycleDurationConfigWidget();

    DefaultRestorableInt const& getDuration() const;
    bool hasChanges();
public slots:
    void init(IntegerObject *settingConfig);
    void restorePreviousValue();
    void restoreDefaultValue();
    void save();
private:
    Ui::CycleDurationConfigWidget *ui;
    DefaultRestorableInt m_duration;
    IntegerObject *m_settingObject = nullptr;
};

#endif // CYCLEDURATIONCONFIGWIDGET_H
