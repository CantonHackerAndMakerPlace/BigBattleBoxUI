#ifndef COUNTDOWNPAGE_H
#define COUNTDOWNPAGE_H

#include <QWidget>
#include <app_state/led/ledalgoconfig/countdownfillconfig.h>

namespace Ui {
class CountDownPage;
}

class CountDownPage : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
public:
    explicit CountDownPage(QWidget *parent = nullptr);
    ~CountDownPage();
    bool hasChanges() const;
    QString title() const;
public slots:
    void init(CountDownFillConfig *config);
    void restorePreviousValue();
    void restoreDefaultValue();
    void save();
    void setTitle(QString value);
signals:
    void titleChanged(QString value);
private:
    Ui::CountDownPage *ui;
    CountDownFillConfig *m_config;
};

#endif // COUNTDOWNPAGE_H
