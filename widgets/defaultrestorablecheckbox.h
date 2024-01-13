#ifndef DEFAULTRESTORABLECHECKBOX_H
#define DEFAULTRESTORABLECHECKBOX_H

#include <QWidget>
#include "defaultrestorable.h"
#include "booleanobject.h"

namespace Ui {
class DefaultRestorableCheckBox;
}

class DefaultRestorableCheckBox : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged DESIGNABLE true)
    Q_PROPERTY(bool defaultValue READ defaultValue WRITE setDefaultValue NOTIFY defaultValueChanged FINAL)
public:
    explicit DefaultRestorableCheckBox(QWidget *parent = nullptr);
    ~DefaultRestorableCheckBox();

    QString title() const;
    bool hasChanges() const;
    bool isChecked() const;
    bool defaultValue() const {return m_value.defaultValue(); }
public slots:
    void setTitle(QString value);
    void init(BooleanObject *settingObject);
    void restorePreviousValue();
    void restoreDefaultValue();
    void save();
    void setDefaultValue(bool value){
        if (value != m_value.defaultValue()) {
            m_value.setDefaultValue(value);
            emit defaultValueChanged(value);
        }
    }
signals:
    void titleChanged(QString);
    void valueChanged(bool);
    void defaultValueChanged(bool value);
private:
    Ui::DefaultRestorableCheckBox *ui;
    DefaultRestorableBool m_value;
    BooleanObject *m_settingConfig = nullptr;
};

#endif // DEFAULTRESTORABLECHECKBOX_H
