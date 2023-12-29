#ifndef COLORSELECTIONWIDGET_H
#define COLORSELECTIONWIDGET_H

#include <QWidget>
#include <QColorDialog>
#include "colorobject.h"
#include "defaultrestorable.h"

namespace Ui {
class ColorSelectionWidget;
}

class ColorSelectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ColorSelectionWidget(QWidget *parent = nullptr);
    ~ColorSelectionWidget();
    bool hasChanges() const;
public slots:
    void init(ColorObject *color);
    void restorePreviousValue();
    void restoreDefaultValue();
    void save();
//signals:
//    void colorChanged(QColor newColor);
private:
    Ui::ColorSelectionWidget *ui;
    DefaultRestorableQColor m_value;
    ColorObject *m_settingObject = nullptr;
};

#endif // COLORSELECTIONWIDGET_H
