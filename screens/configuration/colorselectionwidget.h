#ifndef COLORSELECTIONWIDGET_H
#define COLORSELECTIONWIDGET_H

#include <QWidget>
#include <QColorDialog>

namespace Ui {
class ColorSelectionWidget;
}

class ColorSelectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ColorSelectionWidget(QWidget *parent = nullptr);
    ~ColorSelectionWidget();

    QColor getColor() const;
public slots:
    void setColor(QColor color);
signals:
    void colorChanged(QColor newColor);
private:
    Ui::ColorSelectionWidget *ui;
    QColor m_currentColor;
};

#endif // COLORSELECTIONWIDGET_H
