#ifndef DEFAULTRESTORABLESPINBOX_H
#define DEFAULTRESTORABLESPINBOX_H

#include <QWidget>
#include "integerobject.h"
#include "defaultrestorable.h"

namespace Ui {
class DefaultRestorableSpinBox;
}

class DefaultRestorableSpinBox : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(int minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(int maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(int defaultValue READ defaultValue WRITE setDefaultValue NOTIFY defaultValueChanged)

public:
    explicit DefaultRestorableSpinBox(QWidget *parent = nullptr);
    ~DefaultRestorableSpinBox();

    DefaultRestorableInt const& value() const;

    QString title() const;
    int minimum() const;
    int maximum() const;
    int defaultValue() const;
    bool hasChanges() const;
public slots:
    void init(IntegerObject *settingConfig);
    void restorePreviousValue();
    void restoreDefaultValue();
    void save();
    void setValue(int value);
    void setTitle(QString value);
    void setMinimum(int value);
    void setMaximum(int value);
    void setDefaultValue(int value);
signals:
    void valueChanged(int value);
    void defaultValueChanged(int value);
private:
    Ui::DefaultRestorableSpinBox *ui;
    DefaultRestorableInt m_value;
    IntegerObject *m_settingObject = nullptr;
};

#endif // DEFAULTRESTORABLESPINBOX_H
