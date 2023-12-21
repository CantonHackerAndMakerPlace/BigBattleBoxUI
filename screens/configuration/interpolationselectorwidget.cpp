#include "interpolationselectorwidget.h"
#include "ui_interpolationselectorwidget.h"

InterpolationSelectorWidget::InterpolationSelectorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InterpolationSelectorWidget)
{
    // Setting the initial curve to select, this could change.
    ui->setupUi(this);
    for (auto &curveInfo : Interpolation::CurveData) {
        QIcon icon;
        icon.addFile(curveInfo.imageLocation, QSize(100, 100), QIcon::Normal, QIcon::Off);
        if (icon.isNull()) {
            qDebug() << "Failed to load image: "<< curveInfo.imageLocation;
        }
        auto item = new QListWidgetItem(ui->interpolationSelector);
        item->setIcon(icon);
        item->setText(curveInfo.name);
        item->setToolTip(curveInfo.description);
    }
    ui->interpolationSelector->setIconSize(QSize(100, 100));
}

InterpolationSelectorWidget::~InterpolationSelectorWidget()
{
    delete ui;
}

Interpolation::CurveInfo *InterpolationSelectorWidget::getCurveInfo() const {
    return Interpolation::getCurveInfoByCurve(m_selectedCurve);
}

Interpolation::Curve InterpolationSelectorWidget::getCurve() const {
    return m_selectedCurve;
}

void InterpolationSelectorWidget::setCurveSelection(Interpolation::CurveInfo *) {

}

void InterpolationSelectorWidget::setCurveSelection(Interpolation::Curve) {

}
