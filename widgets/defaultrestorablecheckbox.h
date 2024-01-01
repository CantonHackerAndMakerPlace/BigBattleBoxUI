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
public:
    explicit DefaultRestorableCheckBox(QWidget *parent = nullptr);
    ~DefaultRestorableCheckBox();

    QString title() const;
    bool hasChanges() const;
    bool isChecked() const;
public slots:
    void setTitle(QString value);
    void init(BooleanObject *settingObject);
    void restorePreviousValue();
    void restoreDefaultValue();
    void save();
signals:
    void titleChanged(QString);
    void valueChanged(bool);
private:
    Ui::DefaultRestorableCheckBox *ui;
    DefaultRestorableBool m_value;
    BooleanObject *m_settingConfig = nullptr;
};

#endif // DEFAULTRESTORABLECHECKBOX_H
