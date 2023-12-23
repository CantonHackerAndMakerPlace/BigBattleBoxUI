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
    ui->interpolationSelector->item(0)->setSelected(true);
    connect(ui->interpolationSelector, &QListWidget::currentItemChanged,
            [&](QListWidgetItem *current, QListWidgetItem *){
                qDebug() << "Current item selection changed: "<< current->text();
                auto name = Interpolation::getByName(current->text());
                if (name.has_value()) {
                    emit curveSelectionChanged(name.value());
                } else {
                    qDebug() << "Received invalid interpolation selection";
                }
            });
}

InterpolationSelectorWidget::~InterpolationSelectorWidget() {
    delete ui;
}

Interpolation::CurveInfo *InterpolationSelectorWidget::getCurveInfo() const {
    auto info = Interpolation::getByName(ui->interpolationSelector->currentItem()->text());
    if(info.has_value()) {
        return Interpolation::getCurveInfoByCurve(info.value());
    } else {
        // Logically impossible.
        return nullptr;
    }

}

Interpolation::Curve InterpolationSelectorWidget::getCurve() const {
    return getCurveInfo()->value;
}

void InterpolationSelectorWidget::setCurveSelection(Interpolation::Curve curve) {
//    qDebug() << "Curve being requested!" << (int)curve;
//    auto info = Interpolation::getCurveInfoByCurve(curve);
//    if (!info ) {
//        assert(!"Info not set");
//    }
//    qDebug() << "Curve name: " << info;
    auto items = ui->interpolationSelector->findItems(Interpolation::getName(curve), Qt::MatchExactly);
    if (items.size() != 1) {
        assert(!"Big problem unable to locate curve");
    }
    items.front()->setSelected(true);
    qDebug() << "Selecting interpolation: " << items.front()->text();
}
