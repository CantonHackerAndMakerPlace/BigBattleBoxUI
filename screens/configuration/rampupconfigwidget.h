#ifndef RAMPUPCONFIGWIDGET_H
#define RAMPUPCONFIGWIDGET_H

#include <QWidget>
#include "app_state/led/ledalgoconfig/rampupconfig.h"
#include "screens/configuration/defaultvaluemacros.h"

namespace Ui {
class RampUpConfigWidget;
}

class RampUpConfigWidget : public QWidget
{

    Q_OBJECT
    Q_PROPERTY(bool disableDuration READ disableDuration WRITE setDisableDuration NOTIFY disableDurationChanged FINAL)

    Q_PROPERTY(int durationDefault READ durationDefault WRITE setDurationDefault NOTIFY durationDefaultChanged FINAL)
    Q_PROPERTY(bool unificationDefault READ unificationDefault WRITE setUnificationDefault NOTIFY unificationDefaultChanged FINAL)
    Q_PROPERTY(bool loopDefault READ loopDefault WRITE setLoopDefault NOTIFY loopDefaultChanged FINAL)

    Q_PROPERTY(int p1MinBrightnessDefault READ p1MinBrightnessDefault WRITE setP1MinBrightnessDefault NOTIFY p1MinBrightnessDefaultChanged FINAL)
    Q_PROPERTY(int p1MaxBrightnessDefault READ p1MaxBrightnessDefault WRITE setP1MaxBrightnessDefault NOTIFY p1MaxBrightnessDefaultChanged FINAL)
    Q_PROPERTY(QColor p1ColorDefault READ p1ColorDefault WRITE setP1ColorDefault NOTIFY p1ColorDefaultChanged FINAL)
    Q_PROPERTY(Interpolation::Curve p1CurveDefault READ p1CurveDefault WRITE setP1CurveDefault NOTIFY p1CurveDefaultChanged FINAL)

    Q_PROPERTY(int p2MinBrightnessDefault READ p2MinBrightnessDefault WRITE setP2MinBrightnessDefault NOTIFY p2MinBrightnessDefaultChanged FINAL)
    Q_PROPERTY(int p2MaxBrightnessDefault READ p2MaxBrightnessDefault WRITE setP2MaxBrightnessDefault NOTIFY p2MaxBrightnessDefaultChanged FINAL)
    Q_PROPERTY(QColor p2ColorDefault READ p2ColorDefault WRITE setP2ColorDefault NOTIFY p2ColorDefaultChanged FINAL)
    Q_PROPERTY(Interpolation::Curve p2CurveDefault READ p2CurveDefault WRITE setP2CurveDefault NOTIFY p2CurveDefaultChanged FINAL)
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
    void changesWereMade();
    void disableDurationChanged(bool value);

    void durationDefaultChanged(int value);
    void unificationDefaultChanged(bool value);
    void loopDefaultChanged(bool value);

    void p1MinBrightnessDefaultChanged(int value);
    void p1MaxBrightnessDefaultChanged(int value);
    void p1ColorDefaultChanged(QColor value);
    void p1CurveDefaultChanged(Interpolation::Curve value);

    void p2MinBrightnessDefaultChanged(int value);
    void p2MaxBrightnessDefaultChanged(int value);
    void p2ColorDefaultChanged(QColor value);
    void p2CurveDefaultChanged(Interpolation::Curve value);
public:
    // Using macros to define all of the default value related functions
    PROPERTY_DECL_HELPER(int, durationDefault, setDurationDefault)
    PROPERTY_DECL_HELPER(bool, unificationDefault, setUnificationDefault)
    PROPERTY_DECL_HELPER(bool, loopDefault, setLoopDefault)

    PROPERTY_DECL_HELPER(Interpolation::Curve, p1CurveDefault, setP1CurveDefault)
    PROPERTY_DECL_HELPER(QColor, p1ColorDefault, setP1ColorDefault)
    PROPERTY_DECL_HELPER(int, p1MinBrightnessDefault, setP1MinBrightnessDefault)
    PROPERTY_DECL_HELPER(int, p1MaxBrightnessDefault, setP1MaxBrightnessDefault)

    PROPERTY_DECL_HELPER(Interpolation::Curve, p2CurveDefault, setP2CurveDefault)
    PROPERTY_DECL_HELPER(QColor, p2ColorDefault, setP2ColorDefault)
    PROPERTY_DECL_HELPER(int, p2MinBrightnessDefault, setP2MinBrightnessDefault)
    PROPERTY_DECL_HELPER(int, p2MaxBrightnessDefault, setP2MaxBrightnessDefault)
private:
    Ui::RampUpConfigWidget *ui;
    RampUpConfig *m_config = nullptr;
};

#endif // RAMPUPCONFIGWIDGET_H
