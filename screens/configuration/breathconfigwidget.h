#ifndef BREATHCONFIGWIDGET_H
#define BREATHCONFIGWIDGET_H

#include <QWidget>
#include "app_state/led/ledalgoconfig/breathconfig.h"
#include "screens/configuration/defaultvaluemacros.h"

namespace Ui {
class BreathConfigWidget;
}

class BreathConfigWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int durationDefault READ durationDefault WRITE setDurationDefault NOTIFY durationDefaultChanged FINAL)
    Q_PROPERTY(bool unificationDefault READ unificationDefault WRITE setUnificationDefault NOTIFY unificationDefaultChanged FINAL)

    Q_PROPERTY(int p1MinBrightnessDefault READ p1MinBrightnessDefault WRITE setP1MinBrightnessDefault NOTIFY p1MinBrightnessDefaultChanged FINAL)
    Q_PROPERTY(int p1MaxBrightnessDefault READ p1MaxBrightnessDefault WRITE setP1MaxBrightnessDefault NOTIFY p1MaxBrightnessDefaultChanged FINAL)
    Q_PROPERTY(QColor p1ColorDefault READ p1ColorDefault WRITE setP1ColorDefault NOTIFY p1ColorDefaultChanged FINAL)
    Q_PROPERTY(Interpolation::Curve p1CurveDefault READ p1CurveDefault WRITE setP1CurveDefault NOTIFY p1CurveDefaultChanged FINAL)

    Q_PROPERTY(int p2MinBrightnessDefault READ p2MinBrightnessDefault WRITE setP2MinBrightnessDefault NOTIFY p2MinBrightnessDefaultChanged FINAL)
    Q_PROPERTY(int p2MaxBrightnessDefault READ p2MaxBrightnessDefault WRITE setP2MaxBrightnessDefault NOTIFY p2MaxBrightnessDefaultChanged FINAL)
    Q_PROPERTY(QColor p2ColorDefault READ p2ColorDefault WRITE setP2ColorDefault NOTIFY p2ColorDefaultChanged FINAL)
    Q_PROPERTY(Interpolation::Curve p2CurveDefault READ p2CurveDefault WRITE setP2CurveDefault NOTIFY p2CurveDefaultChanged FINAL)

public:
    explicit BreathConfigWidget(QWidget *parent = nullptr);
    ~BreathConfigWidget();

    bool hasChanges() const;

signals:
    void durationDefaultChanged(int value);
    void unificationDefaultChanged(bool value);
    void p1MinBrightnessDefaultChanged(int value);
    void p1MaxBrightnessDefaultChanged(int value);
    void p1ColorDefaultChanged(QColor value);
    void p1CurveDefaultChanged(Interpolation::Curve value);
    void p2MinBrightnessDefaultChanged(int value);
    void p2MaxBrightnessDefaultChanged(int value);
    void p2ColorDefaultChanged(QColor value);
    void p2CurveDefaultChanged(Interpolation::Curve value);

    void changesWereMade();
public slots:
    void init(BreathConfig *config);
    void restorePreviousValue();
    void restoreDefaultValue();
    void save();
    // Using macros to define all of the default value related functions
    PROPERTY_DECL_HELPER(int, durationDefault, setDurationDefault)
    PROPERTY_DECL_HELPER(bool, unificationDefault, setUnificationDefault)

    PROPERTY_DECL_HELPER(Interpolation::Curve, p1CurveDefault, setP1CurveDefault)
    PROPERTY_DECL_HELPER(QColor, p1ColorDefault, setP1ColorDefault)
    PROPERTY_DECL_HELPER(int, p1MinBrightnessDefault, setP1MinBrightnessDefault)
    PROPERTY_DECL_HELPER(int, p1MaxBrightnessDefault, setP1MaxBrightnessDefault)

    PROPERTY_DECL_HELPER(Interpolation::Curve, p2CurveDefault, setP2CurveDefault)
    PROPERTY_DECL_HELPER(QColor, p2ColorDefault, setP2ColorDefault)
    PROPERTY_DECL_HELPER(int, p2MinBrightnessDefault, setP2MinBrightnessDefault)
    PROPERTY_DECL_HELPER(int, p2MaxBrightnessDefault, setP2MaxBrightnessDefault)

private:
    Ui::BreathConfigWidget *ui;
    BreathConfig *m_config = nullptr;
};

#endif // BREATHCONFIGWIDGET_H
