#ifndef SOLIDCOLORPAGE_H
#define SOLIDCOLORPAGE_H

#include <QWidget>
#include "app_state/led/ledalgoconfig/solidcolorconfig.h"

namespace Ui {
class SolidColorPage;
}

class SolidColorPage : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
public:
    explicit SolidColorPage(QWidget *parent = nullptr);
    ~SolidColorPage();
    bool hasChanges() const;
    QString title() const;
public slots:
    void init(SolidColorConfig *config);
    void restorePreviousValue();
    void restoreDefaultValue();
    void save();
    void setTitle(QString value);
signals:
    void titleChanged(QString value);
private:
    Ui::SolidColorPage *ui;
};

#endif // SOLIDCOLORPAGE_H
