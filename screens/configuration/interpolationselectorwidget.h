#ifndef INTERPOLATIONSELECTORWIDGET_H
#define INTERPOLATIONSELECTORWIDGET_H

#include <QWidget>
#include "app_state/led/interpolation.h"
#include "defaultrestorable.h"
#include "qrealobject.h"
#include "interpolationcurveobject.h"

namespace Ui {
class InterpolationSelectorWidget;
}

class InterpolationSelectorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InterpolationSelectorWidget(QWidget *parent = nullptr);
    ~InterpolationSelectorWidget();

    DefaultRestorableCurve const& getCurve() const;
    DefaultRestorableQReal const& getAmplitude() const;
    bool hasChanges() const;
public:
    void init(InterpolationCurveObject *curveObj, QRealObject *amplitudeObj);
    void restorePreviousValue();
    void restoreDefaultValue();
    void save();
private slots:
    void setCurveSelection(Interpolation::Curve);
signals:
    void curveSelectionChanged(Interpolation::Curve);

private:
    Ui::InterpolationSelectorWidget *ui;
    DefaultRestorableCurve m_curve;
    DefaultRestorableQReal m_amplitude;
    InterpolationCurveObject *m_curveSetting = nullptr;
    QRealObject *m_amplitudeSetting = nullptr;
};

#endif // INTERPOLATIONSELECTORWIDGET_H
