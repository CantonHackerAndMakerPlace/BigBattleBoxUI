#ifndef BLINKCONFIGWIDGET_H
#define BLINKCONFIGWIDGET_H

#include <QWidget>
#include "app_state/led/ledalgoconfig/blinkconfig.h"
#include "screens/configuration/defaultvaluemacros.h"

namespace Ui {
class BlinkConfigWidget;
}

class BlinkConfigWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool unificationDefault READ unificationDefault WRITE setUnificationDefault NOTIFY unificationDefaultChanged FINAL)
    Q_PROPERTY(int onDurationDefault READ onDurationDefault WRITE setOnDurationDefault NOTIFY onDurationDefaultChanged FINAL)
    Q_PROPERTY(int offDurationDefault READ offDurationDefault WRITE setOffDurationDefault NOTIFY offDurationDefaultChanged FINAL)
    Q_PROPERTY(int numberOfBlinksDefault READ numberOfBlinksDefault WRITE setNumberOfBlinksDefault NOTIFY numberOfBlinksDefaultChanged FINAL)

    Q_PROPERTY(QColor p1OnColorDefault READ p1OnColorDefault WRITE setP1OnColorDefault NOTIFY p1OnColorDefaultChanged FINAL)
    Q_PROPERTY(int p1OnBrightnessDefault READ p1OnBrightnessDefault WRITE setP1OnBrightnessDefault NOTIFY p1OnBrightnessDefaultChanged FINAL)
    Q_PROPERTY(QColor p1OffColorDefault READ p1OffColorDefault WRITE setP1OffColorDefault NOTIFY p1OffColorDefaultChanged FINAL)
    Q_PROPERTY(int p1OffBrightnessDefault READ p1OffBrightnessDefault WRITE setP1OffBrightnessDefault NOTIFY p1OffBrightnessDefaultChanged FINAL)

    Q_PROPERTY(QColor p2OnColorDefault READ p2OnColorDefault WRITE setP2OnColorDefault NOTIFY p2OnColorDefaultChanged FINAL)
    Q_PROPERTY(int p2OnBrightnessDefault READ p2OnBrightnessDefault WRITE setP2OnBrightnessDefault NOTIFY p2OnBrightnessDefaultChanged FINAL)
    Q_PROPERTY(QColor p2OffColorDefault READ p2OffColorDefault WRITE setP2OffColorDefault NOTIFY p2OffColorDefaultChanged FINAL)
    Q_PROPERTY(int p2OffBrightnessDefault READ p2OffBrightnessDefault WRITE setP2OffBrightnessDefault NOTIFY p2OffBrightnessDefaultChanged FINAL)

public:
    explicit BlinkConfigWidget(QWidget *parent = nullptr);
    ~BlinkConfigWidget();
    bool hasChanges() const;
public slots:
    void init(BlinkConfig *config);
    void restorePreviousValue();
    void restoreDefaultValue();
    void save();
signals:
    void changesWereMade();
    void unificationDefaultChanged(bool value);

    void onDurationDefaultChanged(int value);
    void offDurationDefaultChanged(int value);
    void numberOfBlinksDefaultChanged(int value);

    void p1OnColorDefaultChanged(QColor value);
    void p1OnBrightnessDefaultChanged(int value);
    void p1OffColorDefaultChanged(QColor value);
    void p1OffBrightnessDefaultChanged(int value);
    void p2OnColorDefaultChanged(QColor value);
    void p2OnBrightnessDefaultChanged(int value);
    void p2OffColorDefaultChanged(QColor value);
    void p2OffBrightnessDefaultChanged(int value);
public:

    // Using macros to define all of the default value related functions
    PROPERTY_DECL_HELPER(bool, unificationDefault, setUnificationDefault)
    PROPERTY_DECL_HELPER(int, onDurationDefault, setOnDurationDefault)
    PROPERTY_DECL_HELPER(int, offDurationDefault, setOffDurationDefault)
    PROPERTY_DECL_HELPER(int, numberOfBlinksDefault, setNumberOfBlinksDefault)

    PROPERTY_DECL_HELPER(QColor, p1OnColorDefault, setP1OnColorDefault)
    PROPERTY_DECL_HELPER(int, p1OnBrightnessDefault, setP1OnBrightnessDefault)
    PROPERTY_DECL_HELPER(QColor, p1OffColorDefault, setP1OffColorDefault)
    PROPERTY_DECL_HELPER(int, p1OffBrightnessDefault, setP1OffBrightnessDefault)

    PROPERTY_DECL_HELPER(QColor, p2OnColorDefault, setP2OnColorDefault)
    PROPERTY_DECL_HELPER(int, p2OnBrightnessDefault, setP2OnBrightnessDefault)
    PROPERTY_DECL_HELPER(QColor, p2OffColorDefault, setP2OffColorDefault)
    PROPERTY_DECL_HELPER(int, p2OffBrightnessDefault, setP2OffBrightnessDefault)
private:
    Ui::BlinkConfigWidget *ui;
    BlinkConfig *m_config = nullptr;
};

#endif // BLINKCONFIGWIDGET_H
