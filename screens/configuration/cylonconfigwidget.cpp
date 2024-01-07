#include "cylonconfigwidget.h"
#include "ui_cylonconfigwidget.h"

CylonConfigWidget::CylonConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CylonConfigWidget)
{
    ui->setupUi(this);
    connect(ui->unification, &UnificationDropDownWidget::unificationKindChanged,
            [&](UnificationKindObject::Kind kind) {
                switch(kind) {
                case UnificationKindObject::Kind::SuperStrip:
                    ui->p2BackgroundColor->setDisabled(true);
                    ui->p2Brightness->setDisabled(true);
                    ui->p2EyeColor->setDisabled(true);
                    ui->p2Interpolation->setDisabled(true);
                case UnificationKindObject::Kind::BothSame:
                    ui->p2BackgroundColor->setDisabled(true);
                    ui->p2Brightness->setDisabled(true);
                    ui->p2EyeColor->setDisabled(true);
                    ui->p2Interpolation->setDisabled(true);
                    break;
                case UnificationKindObject::Kind::Separate:
                    ui->p2BackgroundColor->setDisabled(false);
                    ui->p2Brightness->setDisabled(false);
                    ui->p2EyeColor->setDisabled(false);
                    ui->p2Interpolation->setDisabled(false);
                    break;
                }
            });
}

CylonConfigWidget::~CylonConfigWidget() {
    delete ui;
}

bool CylonConfigWidget::hasChanges() const {
    return false;
}

void CylonConfigWidget::init(CylonConfig *config) {
    assert(!m_config && "Cannot initialize twice");
    m_config = config;

    ui->duration->init(&m_config->cycleDuration());
    ui->eyeLength->init(&m_config->eyeLength());
    ui->unification->init(&m_config->unificationKind());

    ui->p1Brightness->init(&m_config->p1Brightness());
    ui->p1Interpolation->init(&m_config->p1Curve(), &m_config->p1CurveAmplitude());
    ui->p1EyeColor->init(&m_config->p1ForegroundColor());
    ui->p1BackgroundColor->init(&m_config->p1BackgroundColor());

    ui->p2Brightness->init(&m_config->p2Brightness());
    ui->p2BackgroundColor->init(&m_config->p2BackgroundColor());
    ui->p2EyeColor->init(&m_config->p2ForegroundColor());
    ui->p2Interpolation->init(&m_config->p2Curve(), &m_config->p2CurveAmplitude());

}

void CylonConfigWidget::restorePreviousValue() {
    ui->duration->restorePreviousValue();
    ui->eyeLength->restorePreviousValue();
    ui->unification->restorePreviousValue();
    ui->p1Brightness->restorePreviousValue();
    ui->p1Interpolation->restorePreviousValue();
    ui->p1EyeColor->restorePreviousValue();
    ui->p1BackgroundColor->restorePreviousValue();
    ui->p2Brightness->restorePreviousValue();
    ui->p2BackgroundColor->restorePreviousValue();
    ui->p2EyeColor->restorePreviousValue();
    ui->p2Interpolation->restorePreviousValue();
}

void CylonConfigWidget::restoreDefaultValue() {
    ui->duration->restoreDefaultValue();
    ui->eyeLength->restoreDefaultValue();
    ui->unification->restoreDefaultValue();
    ui->p1Brightness->restoreDefaultValue();
    ui->p1Interpolation->restoreDefaultValue();
    ui->p1EyeColor->restoreDefaultValue();
    ui->p1BackgroundColor->restoreDefaultValue();
    ui->p2Brightness->restoreDefaultValue();
    ui->p2BackgroundColor->restoreDefaultValue();
    ui->p2EyeColor->restoreDefaultValue();
    ui->p2Interpolation->restoreDefaultValue();
}

void CylonConfigWidget::save() {
    ui->duration->save();
    ui->eyeLength->save();
    ui->unification->save();
    ui->p1Brightness->save();
    ui->p1Interpolation->save();
    ui->p1EyeColor->save();
    ui->p1BackgroundColor->save();
    ui->p2Brightness->save();
    ui->p2BackgroundColor->save();
    ui->p2EyeColor->save();
    ui->p2Interpolation->save();
}
