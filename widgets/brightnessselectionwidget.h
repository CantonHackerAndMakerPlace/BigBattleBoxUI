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
    Q_PROPERTY(int defaultMinimum READ defaultMinimum WRITE setDefaultMinimum NOTIFY defaultMinimumChanged)
    Q_PROPERTY(int defaultMaximum READ defaultMaximum WRITE setDefaultMaximum NOTIFY defaultMaximumChanged)
public:
    explicit BrightnessSelectionWidget(QWidget *parent = nullptr);
    ~BrightnessSelectionWidget();

    DefaultRestorableInt const& minBrightness() const;
    DefaultRestorableInt const& maxBrightness() const;

    int defaultMinimum() const;
    int defaultMaximum() const;

    bool hasChanges() const;
public slots:
    void init(IntegerObject *minSetting, IntegerObject *maxSetting);
    void restorePreviousValue();
    void restoreDefaultValue();
    void save();

    void setMinValue(int value);
    void setMaxValue(int value);

    void setDefaultMinimum(int value);
    void setDefaultMaximum(int value);
signals:
    void minValueChanged(int value);
    void maxValueChanged(int value);

    void defaultMinimumChanged(int value);
    void defaultMaximumChanged(int value);
private:
    Ui::BrightnessSelectionWidget *ui;
    BrightnessRangeSlider *m_slider;
    DefaultRestorableInt m_min;
    DefaultRestorableInt m_max;
    IntegerObject *m_minSetting = nullptr;
    IntegerObject *m_maxSetting = nullptr;

};

#endif // BRIGHTNESSSELECTIONWIDGET_H
