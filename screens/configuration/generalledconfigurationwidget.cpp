#include "generalledconfigurationwidget.h"
#include "ui_generalledconfigurationwidget.h"
#include <QButtonGroup>

GeneralLEDConfigurationWidget::GeneralLEDConfigurationWidget(QWidget *parent)
    :QWidget(parent)
    , ui(new Ui::GeneralLEDConfigurationWidget)
    , m_p1Direction(new QButtonGroup(this))
    , m_p2Direction(new QButtonGroup(this))
{
    ui->setupUi(this);
    // TODO: Finish configuring the UI here and make sure that we properly set
    // default values. Figure out how to correctly handle the saved state flag.
}

GeneralLEDConfigurationWidget::~GeneralLEDConfigurationWidget() {
    delete ui;
}

void GeneralLEDConfigurationWidget::init(ApplicationState *state) {
    // TODO: Make sure to load/save default values into the state so we can
    // keep them around.
}
