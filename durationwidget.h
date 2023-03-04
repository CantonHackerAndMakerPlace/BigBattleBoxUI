#ifndef DURATIONWIDGET_H
#define DURATIONWIDGET_H

#include <QWidget>

namespace Ui {
class DurationWidget;
}

class DurationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DurationWidget(QWidget *parent = nullptr);
    ~DurationWidget();
public:
    int duration() const;

private slots:
    void on_plus1MinButton_clicked();
    void on_minus1minButton_clicked();
    void on_plus30SecondButton_clicked();
    void on_minus30SecondsButton_clicked();
    void on_plus1SecondButton_clicked();
    void on_minus1SecondButton_clicked();

public slots:
    void setDuration(int i);

signals:
    void durationChanged(int arg);
private:
    Ui::DurationWidget *ui;
};

#endif // DURATIONWIDGET_H
