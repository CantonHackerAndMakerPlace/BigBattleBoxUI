#ifndef SOLIDCOLORCONFIGWIDGET_H
#define SOLIDCOLORCONFIGWIDGET_H

#include <QWidget>
#include "app_state/led/ledalgoconfig/solidcolorconfig.h"
#include "screens/configuration/defaultvaluemacros.h"

namespace Ui {
class SolidColorConfigWidget;
}

class SolidColorConfigWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool unificationDefault READ unificationDefault WRITE setUnificationDefault NOTIFY unificationDefaultChanged FINAL)
    Q_PROPERTY(int p1BrightnessDefault READ p1BrightnessDefault WRITE setP1BrightnessDefault NOTIFY p1BrightnessDefaultChanged FINAL)
    Q_PROPERTY(QColor p1ColorDefault READ p1ColorDefault WRITE setP1ColorDefault NOTIFY p1ColorDefaultChanged FINAL)
    Q_PROPERTY(int p2BrightnessDefault READ p2BrightnessDefault WRITE setP2BrightnessDefault NOTIFY p2BrightnessDefaultChanged FINAL)
    Q_PROPERTY(QColor p2ColorDefault READ p2ColorDefault WRITE setP2ColorDefault NOTIFY p2ColorDefaultChanged FINAL)
public:
    explicit SolidColorConfigWidget(QWidget *parent = nullptr);
    ~SolidColorConfigWidget();
    bool hasChanges() const;
public slots:
    void init(SolidColorConfig *config);
    void restorePreviousValue();
    void restoreDefaultValue();
    void save();
signals:
    void changesWereMade();
    void unificationDefaultChanged(bool value);
    void p1BrightnessDefaultChanged(int value);
    void p1ColorDefaultChanged(QColor value);
    void p2BrightnessDefaultChanged(int value);
    void p2ColorDefaultChanged(QColor value);
public:
    PROPERTY_DECL_HELPER(bool, unificationDefault, setUnificationDefault)

    PROPERTY_DECL_HELPER(QColor, p1ColorDefault, setP1ColorDefault)
    PROPERTY_DECL_HELPER(int, p1BrightnessDefault, setP1BrightnessDefault)

    PROPERTY_DECL_HELPER(QColor, p2ColorDefault, setP2ColorDefault)
    PROPERTY_DECL_HELPER(int, p2BrightnessDefault, setP2BrightnessDefault)


private:
    Ui::SolidColorConfigWidget *ui;
    SolidColorConfig *m_config = nullptr;
};

#endif // SOLIDCOLORCONFIGWIDGET_H
