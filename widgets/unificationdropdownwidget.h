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

public:
    explicit UnificationDropDownWidget(QWidget *parent = nullptr);
    ~UnificationDropDownWidget();

    UnificationKindObject::Kind getStyle() const;

    bool hasChanges() const;
private:
    void addKind(UnificationKindObject::Kind kind);
public slots:
    void init(UnificationKindObject *settingConfig);
    void restorePreviousValue();
    void restoreDefaultValue();
    void save();
signals:
    void unificationKindChanged(UnificationKindObject::Kind kind);
private:
    Ui::UnificationDropDownWidget *ui;
    DefaultRestorableUnificationKind m_value;
    UnificationKindObject *m_settingConfig = nullptr;
};

#endif // UNIFICATIONDROPDOWNWIDGET_H
