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

    connectToControlButtons(ui->p2BackgroundColor);
    connectToControlButtons(ui->p2Brightness);
    connectToControlButtons(ui->p1Interpolation);
    connectToControlButtons(ui->eyeLength);
    connectToControlButtons(ui->unification);
    connectToControlButtons(ui->p1BackgroundColor);
    connectToControlButtons(ui->p1EyeColor);
    connectToControlButtons(ui->p2EyeColor);
    connectToControlButtons(ui->p1Brightness);
    connectToControlButtons(ui->p2Interpolation);
    connectToControlButtons(ui->duration);
}

CylonConfigWidget::~CylonConfigWidget() {
    delete ui;
}

template<typename T>
void CylonConfigWidget::connectToControlButtons(T *page) {
    connect(this, &CylonConfigWidget::save, page, &T::save);
    connect(this, &CylonConfigWidget::restorePreviousValue, page, &T::restorePreviousValue);
    connect(this, &CylonConfigWidget::restoreDefaultValue, page, &T::restoreDefaultValue);
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

void CylonConfigWidget::restorePreviousValue() { }

void CylonConfigWidget::restoreDefaultValue() {}

void CylonConfigWidget::save() {}
