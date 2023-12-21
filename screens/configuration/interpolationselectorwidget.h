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

public slots:
    void setCurveSelection(Interpolation::CurveInfo *);
    void setCurveSelection(Interpolation::Curve);

signals:
    void curveSelectionChanged(Interpolation::CurveInfo *);

private:
    Ui::InterpolationSelectorWidget *ui;
    Interpolation::Curve m_defaultCurve = Interpolation::Curve::Linear;
    Interpolation::Curve m_selectedCurve = m_defaultCurve;
};

#endif // INTERPOLATIONSELECTORWIDGET_H
