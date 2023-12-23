#ifndef INTERPOLATIONSELECTORWIDGET_H
#define INTERPOLATIONSELECTORWIDGET_H

#include <QWidget>
#include "app_state/led/interpolation.h"

namespace Ui {
class InterpolationSelectorWidget;
}

class InterpolationSelectorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InterpolationSelectorWidget(QWidget *parent = nullptr);
    ~InterpolationSelectorWidget();

    Interpolation::CurveInfo *getCurveInfo() const;
    Interpolation::Curve getCurve() const;
    void init();
public slots:
    void setCurveSelection(Interpolation::Curve);

signals:
    void curveSelectionChanged(Interpolation::Curve);

private:
    Ui::InterpolationSelectorWidget *ui;
};

#endif // INTERPOLATIONSELECTORWIDGET_H
