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
    Q_PROPERTY(bool defaultValue READ defaultValue WRITE setDefaultValue NOTIFY defaultValueChanged FINAL)
public:
    explicit UnifiedCheckBox(QWidget *parent = nullptr);
    ~UnifiedCheckBox();

    bool hasChanges() const;

    bool getValue() const;
    bool defaultValue() const;
public slots:
    void init(BooleanObject *settingObject);
    void restorePreviousValue();
    void restoreDefaultValue();
    void save();
    void setValue(bool value);
    void setDefaultValue(bool value);
signals:
    void valueChanged(bool value);
    void defaultValueChanged(bool value);
private:
    Ui::UnifiedCheckBox *ui;
    DefaultRestorableBool m_link;
    BooleanObject *m_settingObj = nullptr;
};

#endif // UNIFIEDCHECKBOX_H
