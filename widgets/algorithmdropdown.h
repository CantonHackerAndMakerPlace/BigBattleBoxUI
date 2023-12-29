#ifndef ALGORITHMDROPDOWN_H
#define ALGORITHMDROPDOWN_H

#include <QWidget>
#include "algokindobject.h"
#include "defaultrestorable.h"

namespace Ui {
class AlgorithmDropDown;
}

class AlgorithmDropDown : public QWidget
{
    Q_OBJECT

public:
    explicit AlgorithmDropDown(QWidget *parent = nullptr);
    ~AlgorithmDropDown();

    DefaultRestorableAlgoKind const& getCurrentAlgorithm() const;
    bool hasChanges();
private:
    void addAlgorithm(AlgoKindObject::AlgoKind kind);
public slots:
    void init(AlgoKindObject *settingConfig);
    void restorePreviousValue();
    void restoreDefaultValue();
    void save();
signals:
    void algorithmChanged(AlgoKindObject::AlgoKind kind);
private:
    Ui::AlgorithmDropDown *ui;
    DefaultRestorableAlgoKind m_value;
    AlgoKindObject *m_settingObject = nullptr;
};

#endif // ALGORITHMDROPDOWN_H
