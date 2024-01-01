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
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QColor defaultValue READ defaultValue WRITE setDefaultValue NOTIFY defaultValueChanged)
public:
    explicit ColorSelectionWidget(QWidget *parent = nullptr);
    ~ColorSelectionWidget();
    bool hasChanges() const;
    QString title() const;
    QColor defaultValue() const;
public slots:
    void init(ColorObject *color);
    void restorePreviousValue();
    void restoreDefaultValue();
    void save();
    void setTitle(QString title);
    void setDefaultValue(QColor value);
signals:
    void titleChanged(QString title);
    void defaultValueChanged(QColor value);
private:
    Ui::ColorSelectionWidget *ui;
    DefaultRestorableQColor m_value;
    ColorObject *m_settingObject = nullptr;
};

#endif // COLORSELECTIONWIDGET_H
