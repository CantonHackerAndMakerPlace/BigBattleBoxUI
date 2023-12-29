#include "colorselectionwidget.h"
#include "ui_colorselectionwidget.h"
static constexpr const char* styleSheetToFmt
    = "border-style: outset;"
      "border-width: 1px;"
      "border-color: black;"
      "background-color: %1;";

ColorSelectionWidget::ColorSelectionWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ColorSelectionWidget)
    , m_value(Qt::white)
{
    ui->setupUi(this);
    ui->colorWidgetDisplay->setStyleSheet(QString(styleSheetToFmt).arg(m_value.value().name()));
    connect(ui->changeColorButton, &QPushButton::clicked,
            [&](bool) {
                auto newColor = QColorDialog::getColor(m_value.value(), this, "Select a color", QColorDialog::DontUseNativeDialog).convertTo(QColor::Spec::Rgb);
                ui->colorWidgetDisplay->setStyleSheet(QString(styleSheetToFmt).arg(m_value.value().name()));
                m_value.setValue(newColor);
            }
        );
}

ColorSelectionWidget::~ColorSelectionWidget() {
    delete ui;
}

bool ColorSelectionWidget::hasChanges() const {
    return m_value.hasChange();
}

void ColorSelectionWidget::init(ColorObject *settingObject) {
    qDebug() << "Initialzing color thingy!";
    assert(!m_settingObject && "Must not be initialized twice");
    m_settingObject = settingObject;
    connect(m_settingObject, &ColorObject::valueChanged,
            &m_value, &DefaultRestorableQColor::setCurrentAndPreviousValue);
    m_value = *m_settingObject;
    ui->colorWidgetDisplay->setStyleSheet(QString(styleSheetToFmt).arg(m_value.value().name()));
}

void ColorSelectionWidget::restorePreviousValue() {
    m_value.restorePreviousValue();
}

void ColorSelectionWidget::restoreDefaultValue() {
    m_value.restoreDefaultValue();
}

void ColorSelectionWidget::save() {
    if(!m_settingObject) {
        return;
    }
    m_settingObject->setValue(m_value.value());
}

//QColor ColorSelectionWidget::getColor() const {
//    return m_currentColor;
//}

//void ColorSelectionWidget::setColor(QColor color) {
//    if (color != m_currentColor) {
//        m_currentColor = color;
//        ui->colorWidgetDisplay->setStyleSheet(QString(styleSheetToFmt).arg(m_currentColor.name()));
//        emit colorChanged(m_currentColor);
//    }
//}
