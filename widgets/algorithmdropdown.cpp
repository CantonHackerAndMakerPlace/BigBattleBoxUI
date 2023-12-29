    #include "algorithmdropdown.h"
#include "ui_algorithmdropdown.h"

#include <QVariant>


AlgorithmDropDown::AlgorithmDropDown(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AlgorithmDropDown)
    , m_value(AlgoKindObject::AlgoKind::Breath)
{
    ui->setupUi(this);


    // Adding selectable items to the drop down.
    addAlgorithm(AlgoKindObject::AlgoKind::Off);
    addAlgorithm(AlgoKindObject::AlgoKind::Blink);
    addAlgorithm(AlgoKindObject::AlgoKind::Breath);
    addAlgorithm(AlgoKindObject::AlgoKind::CountDown);
    addAlgorithm(AlgoKindObject::AlgoKind::Cylon);
    addAlgorithm(AlgoKindObject::AlgoKind::RampUp);
    addAlgorithm(AlgoKindObject::AlgoKind::Solid);

    // Connecting signals and slots so that value within the drop down are in sync
    // with those within the default restorable value.

    connect(&m_value, &DefaultRestorableAlgoKind::valueChanged,
            [&](AlgoKindObject::AlgoKind kind) {
                ui->algoDropDown->setCurrentText(AlgoKindObject::getDisplayName(kind));
            });
    connect(ui->algoDropDown, &QComboBox::currentIndexChanged,
            [&](int index) {
                auto variant = ui->algoDropDown->itemData(index);
                bool isOk = false;
                int selectionValue = variant.toInt(&isOk);
                if (!isOk) {
                    qWarning() << "Problem unable to get data for selection at index" << index;
                    return;
                }
                AlgoKindObject::AlgoKind algo = AlgoKindObject::AlgoKind::Off;
                switch(selectionValue) {
                    case (int)AlgoKindObject::AlgoKind::Off:
                    algo = AlgoKindObject::AlgoKind::Off;
                    break;
                    case (int)AlgoKindObject::AlgoKind::Blink:
                    algo = AlgoKindObject::AlgoKind::Blink;
                    break;
                    case (int)AlgoKindObject::AlgoKind::Breath:
                    algo = AlgoKindObject::AlgoKind::Breath;
                    break;
                    case (int)AlgoKindObject::AlgoKind::CountDown:
                    algo = AlgoKindObject::AlgoKind::CountDown;
                    break;
                    case (int)AlgoKindObject::AlgoKind::Cylon:
                    algo = AlgoKindObject::AlgoKind::Cylon;
                    break;
                    case (int)AlgoKindObject::AlgoKind::RampUp:
                    algo = AlgoKindObject::AlgoKind::RampUp;
                    break;
                    case (int)AlgoKindObject::AlgoKind::Solid:
                    algo = AlgoKindObject::AlgoKind::Solid;
                    break;
                    default:
                    qWarning() << "Problem unable to get data for selection at index" << index << "with value" << selectionValue;
                    return;
                }
                m_value.setValue(algo);
            });

    // Chain the value changed event emission.
    connect(&m_value, &DefaultRestorableAlgoKind::valueChanged,
            this, &AlgorithmDropDown::algorithmChanged);
    m_value.setValue(AlgoKindObject::AlgoKind::Breath);
    m_value.setValue(AlgoKindObject::AlgoKind::Off);
    m_value.setValue(AlgoKindObject::AlgoKind::Breath);
}

AlgorithmDropDown::~AlgorithmDropDown() {
    delete ui;
}

DefaultRestorableAlgoKind const& AlgorithmDropDown::getCurrentAlgorithm() const {
    return m_value;
}

bool AlgorithmDropDown::hasChanges() {
    return m_value.hasChange();
}

void AlgorithmDropDown::addAlgorithm(AlgoKindObject::AlgoKind kind) {
    ui->algoDropDown->addItem(
        AlgoKindObject::getDisplayName(kind),
        QVariant((int)kind)
    );
}

void AlgorithmDropDown::init(AlgoKindObject *settingConfig) {
    assert(!m_settingObject && "Cannot initialize settings twice");
    m_settingObject = settingConfig;
    connect(m_settingObject, &AlgoKindObject::valueChanged,
            &m_value, &DefaultRestorableAlgoKind::setCurrentAndPreviousValue);
    m_value = *m_settingObject;
}

void AlgorithmDropDown::restorePreviousValue() {
    m_value.restorePreviousValue();
}

void AlgorithmDropDown::restoreDefaultValue() {
    m_value.restoreDefaultValue();
}

void AlgorithmDropDown::save() {
    if(!m_settingObject) {
        return;
    }
    m_settingObject->setValue(m_value.value());
}
