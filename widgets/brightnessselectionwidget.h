#ifndef BRIGHTNESSSELECTIONWIDGET_H
#define BRIGHTNESSSELECTIONWIDGET_H

#include <QWidget>
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

public slots:
    void setMinValue(int value);
    void setMaxValue(int value);
signals:
    void minValueChanged(int value);
    void maxValueChanged(int value);
private:
    Ui::BrightnessSelectionWidget *ui;
    BrightnessRangeSlider *m_slider;
};

#endif // BRIGHTNESSSELECTIONWIDGET_H
