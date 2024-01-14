#ifndef RAMPUPPAGE_H
#define RAMPUPPAGE_H

#include <QWidget>
#include "app_state/led/ledalgoconfig/rampupconfig.h"
namespace Ui {
class RampUpPage;
}

class RampUpPage : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)

public:
    explicit RampUpPage(QWidget *parent = nullptr);
    ~RampUpPage();
    bool hasChanges() const;
    QString title() const;
public slots:
    void init(RampUpConfig *config);
    void restorePreviousValue();
    void restoreDefaultValue();
    void save();
    void setTitle(QString value);
signals:
    void titleChanged(QString value);
private:
    Ui::RampUpPage *ui;
};

#endif // RAMPUPPAGE_H
