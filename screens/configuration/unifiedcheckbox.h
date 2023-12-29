#ifndef UNIFIEDCHECKBOX_H
#define UNIFIEDCHECKBOX_H

#include <QWidget>
#include "booleanobject.h"
#include "defaultrestorable.h"

namespace Ui {
class UnifiedCheckBox;
}

class UnifiedCheckBox : public QWidget
{
    Q_OBJECT

public:
    explicit UnifiedCheckBox(QWidget *parent = nullptr);
    ~UnifiedCheckBox();

    bool hasChanges() const;

    bool getValue() const;

public slots:
    void init(BooleanObject *settingObject);
    void restorePreviousValue();
    void restoreDefaultValue();
    void save();
signals:
    void valueChanged(bool value);
private:
    Ui::UnifiedCheckBox *ui;
    DefaultRestorableBool m_link;
    BooleanObject *m_settingObj = nullptr;
};

#endif // UNIFIEDCHECKBOX_H
