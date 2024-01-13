#ifndef CYLONCONFIGWIDGET_H
#define CYLONCONFIGWIDGET_H

#include <QWidget>
#include "app_state/led/ledalgoconfig/cylonconfig.h"
#include "screens/configuration/defaultvaluemacros.h"

namespace Ui {
class CylonConfigWidget;
}

class CylonConfigWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int durationDefault READ durationDefault WRITE setDurationDefault NOTIFY durationDefaultChanged FINAL)
    Q_PROPERTY(UnificationKindObject::Kind unificationKindDefault READ unificationKindDefault WRITE setUnificationKindDefault NOTIFY unificationKindDefaultChanged FINAL)
    Q_PROPERTY(int eyeLengthDefault READ eyeLengthDefault WRITE setEyeLengthDefault NOTIFY eyeLengthDefaultChanged FINAL)

    Q_PROPERTY(Interpolation::Curve p1CurveDefault READ p1CurveDefault WRITE setP1CurveDefault NOTIFY p1CurveDefaultChanged FINAL)
    Q_PROPERTY(QColor p1EyeColorDefault READ p1EyeColorDefault WRITE setP1EyeColorDefault NOTIFY p1EyeColorDefaultChanged FINAL)
    Q_PROPERTY(QColor p1BackgroundColorDefault READ p1BackgroundColorDefault WRITE setP1BackgroundColorDefault NOTIFY p1BackgroundColorDefaultChanged FINAL)
    Q_PROPERTY(int p1BrightnessDefault READ p1BrightnessDefault WRITE setP1BrightnessDefault NOTIFY p1BrightnessDefaultChanged FINAL)

    Q_PROPERTY(Interpolation::Curve p2CurveDefault READ p2CurveDefault WRITE setP2CurveDefault NOTIFY p2CurveDefaultChanged FINAL)
    Q_PROPERTY(QColor p2EyeColorDefault READ p2EyeColorDefault WRITE setP2EyeColorDefault NOTIFY p2EyeColorDefaultChanged FINAL)
    Q_PROPERTY(QColor p2BackgroundColorDefault READ p2BackgroundColorDefault WRITE setP2BackgroundColorDefault NOTIFY p2BackgroundColorDefaultChanged FINAL)
    Q_PROPERTY(int p2BrightnessDefault READ p2BrightnessDefault WRITE setP2BrightnessDefault NOTIFY p2BrightnessDefaultChanged FINAL)

public:
    explicit CylonConfigWidget(QWidget *parent = nullptr);
    ~CylonConfigWidget();

    bool hasChanges() const;
public slots:
    void init(CylonConfig *config);
    void restorePreviousValue();
    void restoreDefaultValue();
    void save();
signals:
    void durationDefaultChanged(int value);
    void unificationKindDefaultChanged(UnificationKindObject::Kind value);
    void eyeLengthDefaultChanged(int value);

    void p1CurveDefaultChanged(Interpolation::Curve value);
    void p1EyeColorDefaultChanged(QColor value);
    void p1BackgroundColorDefaultChanged(QColor value);
    void p1BrightnessDefaultChanged(int value);

    void p2CurveDefaultChanged(Interpolation::Curve value);
    void p2EyeColorDefaultChanged(QColor value);
    void p2BackgroundColorDefaultChanged(QColor value);
    void p2BrightnessDefaultChanged(int value);

    void changesWereMade();
public:
    // Using macros to define all of the default value related functions
    PROPERTY_DECL_HELPER(int, durationDefault, setDurationDefault)
    PROPERTY_DECL_HELPER(UnificationKindObject::Kind, unificationKindDefault, setUnificationKindDefault)
    PROPERTY_DECL_HELPER(int, eyeLengthDefault, setEyeLengthDefault)

    PROPERTY_DECL_HELPER(Interpolation::Curve, p1CurveDefault, setP1CurveDefault)
    PROPERTY_DECL_HELPER(QColor, p1EyeColorDefault, setP1EyeColorDefault)
    PROPERTY_DECL_HELPER(QColor, p1BackgroundColorDefault, setP1BackgroundColorDefault)
    PROPERTY_DECL_HELPER(int, p1BrightnessDefault, setP1BrightnessDefault)

    PROPERTY_DECL_HELPER(Interpolation::Curve, p2CurveDefault, setP2CurveDefault)
    PROPERTY_DECL_HELPER(QColor, p2EyeColorDefault, setP2EyeColorDefault)
    PROPERTY_DECL_HELPER(QColor, p2BackgroundColorDefault, setP2BackgroundColorDefault)
    PROPERTY_DECL_HELPER(int, p2BrightnessDefault, setP2BrightnessDefault)
private:
    Ui::CylonConfigWidget *ui;
    CylonConfig *m_config = nullptr;
};

#endif // CYLONCONFIGWIDGET_H
