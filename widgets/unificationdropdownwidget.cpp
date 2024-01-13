#include "unificationdropdownwidget.h"
#include "ui_unificationdropdownwidget.h"

UnificationDropDownWidget::UnificationDropDownWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UnificationDropDownWidget)
    , m_value(UnificationKindObject::Kind::BothSame)
{
    ui->setupUi(this);

    // Connecting signals and slots so that value within the drop down are in sync
    // with those within the default restorable value.
    connect(&m_value, &DefaultRestorableUnificationKind::valueChanged,
            [&](UnificationKindObject::Kind kind) {
                ui->unificationKindDropDown->setCurrentText(UnificationKindObject::getDisplayName(kind));
            });
    connect(&m_value, &DefaultRestorableUnificationKind::defaultValueChanged,
            this, &UnificationDropDownWidget::defaultValueChanged);
    connect(ui->unificationKindDropDown, &QComboBox::currentIndexChanged,
            [&](int index) {
                auto variant = ui->unificationKindDropDown->itemData(index);
                bool isOk = false;
                int selectionValue = variant.toInt(&isOk);
                if (!isOk) {
                    qWarning() << "Problem unable to get data for selection at index" << index;
                    return;
                }
                UnificationKindObject::Kind kind = UnificationKindObject::Kind::BothSame;
                switch(selectionValue) {
                case (int)UnificationKindObject::Kind::BothSame:
                    kind = UnificationKindObject::Kind::BothSame;
                    break;
                case (int)UnificationKindObject::Kind::Separate:
                    kind = UnificationKindObject::Kind::Separate;
                    break;
                case (int)UnificationKindObject::Kind::SuperStrip:
                    kind = UnificationKindObject::Kind::SuperStrip;
                    break;
                default:
                    qWarning() << "Problem unable to get data for selection at index" << index << "with value" << selectionValue;
                    return;
                }
                m_value.setValue(kind);
            });

    // Chain the value changed event emission.
    connect(&m_value, &DefaultRestorableUnificationKind::valueChanged,
            this, &UnificationDropDownWidget::unificationKindChanged);
    addKind(UnificationKindObject::Kind::BothSame);
    addKind(UnificationKindObject::Kind::Separate);
    addKind(UnificationKindObject::Kind::SuperStrip);

    m_value.setValue(UnificationKindObject::Kind::BothSame);
    m_value.setValue(UnificationKindObject::Kind::Separate);
    m_value.setValue(UnificationKindObject::Kind::BothSame);
}

UnificationDropDownWidget::~UnificationDropDownWidget() {
    delete ui;
}

UnificationKindObject::Kind UnificationDropDownWidget::getStyle() const {
    return m_value.value();
}

UnificationKindObject::Kind UnificationDropDownWidget::defaultValue() const {
    return m_value.defaultValue();
}

bool UnificationDropDownWidget::hasChanges() const{
    return m_value.hasChange();
}

void UnificationDropDownWidget::addKind(UnificationKindObject::Kind kind) {
    ui->unificationKindDropDown->addItem(
        UnificationKindObject::getDisplayName(kind),
        QVariant((int)kind)
    );
}

void UnificationDropDownWidget::init(UnificationKindObject *settingConfig) {
    assert(!m_settingConfig && "Cannot be initialized twice");
    m_settingConfig = settingConfig;
    connect(m_settingConfig, &UnificationKindObject::valueChanged,
            &m_value, &DefaultRestorableUnificationKind::setCurrentAndPreviousValue);
    m_value = *m_settingConfig;
}

void UnificationDropDownWidget::restorePreviousValue() {
    m_value.restorePreviousValue();
}

void UnificationDropDownWidget::restoreDefaultValue() {
    m_value.restoreDefaultValue();
}

void UnificationDropDownWidget::save() {
    if(!m_settingConfig) {
        return;
    }
    m_settingConfig->setValue(m_value.value());
}

void UnificationDropDownWidget::setDefaultValue(UnificationKindObject::Kind value) {
    m_value.setDefaultValue(value);
}
