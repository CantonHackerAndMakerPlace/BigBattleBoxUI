#ifndef BRIGHTNESSSELECTIONWIDGET_H
#define BRIGHTNESSSELECTIONWIDGET_H

#include <QWidget>
#include "defaultrestorable.h"
#include "integerobject.h"

class BrightnessRangeSlider;

namespace Ui {
class BrightnessSelectionWidget;
}

class BrightnessSelectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BrightnessSelectionWidget(QWidget *parent = nullptr);
    ~BrightnessSelectionWidget();

    DefaultRestorableInt const& minBrightness() const;
    DefaultRestorableInt const& maxBrightness() const;

public slots:
    void init(IntegerObject *minSetting, IntegerObject *maxSetting);
    void restorePreviousValue();
    void restoreDefaultValue();
    void save();

    void setMinValue(int value);
    void setMaxValue(int value);
signals:
    void minValueChanged(int value);
    void maxValueChanged(int value);
private:
    Ui::BrightnessSelectionWidget *ui;
    BrightnessRangeSlider *m_slider;
    DefaultRestorableInt m_min;
    DefaultRestorableInt m_max;
    IntegerObject *m_minSetting = nullptr;
    IntegerObject *m_maxSetting = nullptr;

};

#endif // BRIGHTNESSSELECTIONWIDGET_H
