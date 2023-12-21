#include "colorselectionwidget.h"
#include "ui_colorselectionwidget.h"
static constexpr const char* styleSheetToFmt
    = "border-style: outset;"
      "border-width: 1px;"
      "border-color: black;"
      "background-color: %1;";

ColorSelectionWidget::ColorSelectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorSelectionWidget),
    m_currentColor(QColor::fromRgb(255, 255, 255)) // Default color is white I guess.
{
    ui->setupUi(this);
    ui->colorWidgetDisplay->setStyleSheet(QString(styleSheetToFmt).arg(m_currentColor.name()));
    qDebug() << "Style sheet " << ui->colorWidgetDisplay->styleSheet();
    connect(ui->changeColorButton, &QPushButton::clicked,
            [&](bool) {
                auto newColor = QColorDialog::getColor(m_currentColor, this, "Select a color", QColorDialog::DontUseNativeDialog).convertTo(QColor::Spec::Rgb);
                qDebug() << "newColor = " << newColor.name();
                setColor(newColor);
            }
        );
}

ColorSelectionWidget::~ColorSelectionWidget() {
    delete ui;
}

QColor ColorSelectionWidget::getColor() const {
    return m_currentColor;
}

void ColorSelectionWidget::setColor(QColor color) {
    if (color != m_currentColor) {
        m_currentColor = color;
        ui->colorWidgetDisplay->setStyleSheet(QString(styleSheetToFmt).arg(m_currentColor.name()));
        emit colorChanged(m_currentColor);
    }
}
