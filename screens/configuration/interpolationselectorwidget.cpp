#include "interpolationselectorwidget.h"
#include "ui_interpolationselectorwidget.h"

InterpolationSelectorWidget::InterpolationSelectorWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::InterpolationSelectorWidget)
    , m_curve(Interpolation::Curve::Linear)
    , m_amplitude(1.0)
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
    ui->selectionLabel->setText(QString("Selected: %1").arg(ui->interpolationSelector->item(0)->text()));
    connect(ui->interpolationSelector, &QListWidget::currentItemChanged,
            [&](QListWidgetItem *current, QListWidgetItem *){
                auto name = Interpolation::getByName(current->text());
                if (name.has_value()) {
                    ui->selectionLabel->setText(QString("Selected: %1").arg(current->text()));
                    setCurveSelection(name.value());
                } else {
                    qWarning() << "Received invalid interpolation selection";
                }
            });
}

InterpolationSelectorWidget::~InterpolationSelectorWidget() {
    delete ui;
}

DefaultRestorableCurve const& InterpolationSelectorWidget::getCurve() const {
    return m_curve;
}

DefaultRestorableQReal const& InterpolationSelectorWidget::getAmplitude() const {
    return m_amplitude;
}

bool InterpolationSelectorWidget::hasChanges() const {
    return m_curve.hasChange()
           || m_amplitude.hasChange();
}

void InterpolationSelectorWidget::init(InterpolationCurveObject *curveObj, QRealObject *amplitudeObj) {
    assert(!m_curveSetting && "Cannot be initialized twice");
    assert(!m_amplitudeSetting && "Cannot be initialized twice");
    m_curveSetting = curveObj;
    m_amplitudeSetting = amplitudeObj;

    connect(m_curveSetting, &InterpolationCurveObject::valueChanged,
            &m_curve, &DefaultRestorableCurve::setCurrentAndPreviousValue);

    connect(m_amplitudeSetting, &QRealObject::valueChanged,
            &m_amplitude, &DefaultRestorableQReal::setCurrentAndPreviousValue);
    m_curve = *m_curveSetting;
    m_amplitude = *m_amplitudeSetting;
}

void InterpolationSelectorWidget::restorePreviousValue() {
    m_amplitude.restorePreviousValue();
    m_curve.restorePreviousValue();
}

void InterpolationSelectorWidget::restoreDefaultValue() {
    m_amplitude.restoreDefaultValue();
    m_curve.restoreDefaultValue();
}

void InterpolationSelectorWidget::save() {
    if(!m_curveSetting || !m_amplitudeSetting) {
        return;
    }
    m_curveSetting->setValue(m_curve.value());
    m_amplitudeSetting->setValue(m_amplitude.value());
}

void InterpolationSelectorWidget::setCurveSelection(Interpolation::Curve curve) {
    auto items = ui->interpolationSelector->findItems(Interpolation::getName(curve), Qt::MatchExactly);
    if (items.size() != 1) {
        assert(!"Big problem unable to locate curve");
    }
    ui->interpolationSelector->setCurrentItem(items.front());
    qDebug() << "Selecting interpolation: " << items.front()->text();
    m_curve.setValue(curve);
}
