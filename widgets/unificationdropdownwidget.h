#ifndef UNIFICATIONDROPDOWNWIDGET_H
#define UNIFICATIONDROPDOWNWIDGET_H

#include <QWidget>
#include "unificationkindobject.h"
#include "defaultrestorable.h"

namespace Ui {
class UnificationDropDownWidget;
}

class UnificationDropDownWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(UnificationKindObject::Kind defaultValue READ defaultValue WRITE setDefaultValue NOTIFY defaultValueChanged FINAL)
public:
    explicit UnificationDropDownWidget(QWidget *parent = nullptr);
    ~UnificationDropDownWidget();

    UnificationKindObject::Kind getStyle() const;

    UnificationKindObject::Kind defaultValue() const;
    bool hasChanges() const;
private:
    void addKind(UnificationKindObject::Kind kind);
public slots:
    void init(UnificationKindObject *settingConfig);
    void restorePreviousValue();
    void restoreDefaultValue();
    void save();
    void setDefaultValue(UnificationKindObject::Kind value);
signals:
    void unificationKindChanged(UnificationKindObject::Kind kind);
    void defaultValueChanged(UnificationKindObject::Kind value);
private:
    Ui::UnificationDropDownWidget *ui;
    DefaultRestorableUnificationKind m_value;
    UnificationKindObject *m_settingConfig = nullptr;
};

#endif // UNIFICATIONDROPDOWNWIDGET_H
