#include "ledcontrolwidget.h"
#include "ui_ledcontrolwidget.h"

LEDControlWidget::LEDControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LEDControlWidget)
{
    ui->setupUi(this);
    m_itemToPage = {
        {"General LED Configurations", ui->generalLedConfigurationWidget},
        {"Idle Screen", ui->idleScreenWidget},
        {"Death Match Configuration Lights", ui->deathMatchConfigLightsWidget},
        {"Death Match Players Ready Lights", ui->deathMatchPlayersReadyLightsWidget},
        {"Death Match Count Down Lights", ui->deathMatchCountDownLightsWidget},
        {"Death Match Door Drop Lights", ui->deathMatchDoorDropLightsWidget},
        {"Death Match Match Lights", ui->deathMatchMatchLightsWidget},
        {"Death Match Winning Player Lights",  ui->deathMatchWinningPlayerLightsWidget},
        {"Soccer Configuration Lights", ui->soccerConfigLightsWidget},
        {"Soccer Players Ready Lights", ui->soccerPlayerReadyLightsWidget},
        {"Soccer Count Down Lights", ui->soccerCountDownLightsWidget},
        {"Soccer Match Lights", ui->soccerMatchLightsWidget},
        {"Soccer Winning Player Lights", ui->soccerWinningPlayerLightsWidget},
    };

    connect(ui->treeWidget, &QTreeWidget::currentItemChanged,
            this, &LEDControlWidget::selectionChangedChanged);
}

LEDControlWidget::~LEDControlWidget() {
    delete ui;
}

void LEDControlWidget::init(ApplicationState *state) {
    m_state = state;
    ui->generalLedConfigurationWidget->init(m_state);
    ui->idleScreenWidget->init(m_state);
    // TODO: This may also need some kind of flag to prevent navigation in the
    // event that we have unsaved changes.

    // TODO: finish connecting the lights and other related physical
    // state information.
}

void LEDControlWidget::selectionChangedChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous) {
    qDebug() << "Selection changed to: " << current->text(0);
    auto selectedWidget = m_itemToPage[current->text(0)];
    ui->lightConfigDisplay->setCurrentWidget(selectedWidget);
}

