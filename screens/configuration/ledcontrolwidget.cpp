#include "ledcontrolwidget.h"
#include "ui_ledcontrolwidget.h"

enum Screens {
    General,
    Idle,
    DMConfig,
    DMPlayerReady,
    DMMatchLights,
    DMCountDownDoorDrop,
    DMDoorDrop,
    DMCountDownMatchOver,
    DMWinningPlayer,

    SoccerConfig,
    SoccerPlayerReady,
    SoccerCountDown,
    SoccerMatchLights,
    SoccerWinningPlayer,
};

LEDControlWidget::LEDControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LEDControlWidget)
{
    ui->setupUi(this);

    // Manually configuring tree selection because this is easier than using the
    // designer.q
    m_general = new QTreeWidgetItem(ui->treeWidget);
    m_general->setText(0, tr("General LED Configurations"));

    m_idleScreen = new QTreeWidgetItem(ui->treeWidget);
    m_idleScreen->setText(0, tr("Idle Screen"));

    m_deathMatch = new QTreeWidgetItem(ui->treeWidget);
    m_deathMatch->setText(0, tr("Death Match"));

    m_dmConfig = new QTreeWidgetItem(m_deathMatch);
    m_dmConfig->setText(0, tr("Configuration Lights"));
    m_dmPlayersReady = new QTreeWidgetItem(m_deathMatch);
    m_dmPlayersReady->setText(0, tr("Players Ready Lights"));

    m_dmCountDownToMatchStart = new QTreeWidgetItem(m_deathMatch);
    m_dmCountDownToMatchStart->setText(0, tr("Count Down To Match Start"));
    m_dmThree = new QTreeWidgetItem(m_dmCountDownToMatchStart);
    m_dmThree->setText(0, tr("Three"));
    m_dmTwo = new QTreeWidgetItem(m_dmCountDownToMatchStart);
    m_dmTwo->setText(0, tr("Two"));
    m_dmOne = new QTreeWidgetItem(m_dmCountDownToMatchStart);
    m_dmOne->setText(0, tr("One"));
    m_dmFight = new QTreeWidgetItem(m_dmCountDownToMatchStart);
    m_dmFight->setText(0, tr("FIGHT!!!"));

    m_dmRunningLights = new QTreeWidgetItem(m_deathMatch);
    m_dmRunningLights->setText(0, tr("Match Running Lights"));
    m_dmCountDownDoorDrop = new QTreeWidgetItem(m_deathMatch);
    m_dmCountDownDoorDrop->setText(0, tr("Count Down To Door Drop"));
    m_dmDoorDrop = new QTreeWidgetItem(m_deathMatch);
    m_dmDoorDrop->setText(0, tr("Door Drop Lights"));
    m_dmCountDownMatchOver = new QTreeWidgetItem(m_deathMatch);
    m_dmCountDownMatchOver->setText(0, tr("Count Down To Match Over"));
    m_dmPlayerWins = new QTreeWidgetItem(m_deathMatch);
    m_dmPlayerWins->setText(0, tr("Winner Screen"));

    m_soccer = new QTreeWidgetItem(ui->treeWidget);
    m_soccer->setText(0, tr("Soccer"));

    m_soccerConfig = new QTreeWidgetItem(m_soccer);
    m_soccerConfig->setText(0, tr("Configuration Lights"));
    m_soccerPlayerReady = new QTreeWidgetItem(m_soccer);
    m_soccerPlayerReady->setText(0, tr("Teams Ready Lights"));
    m_soccerRunningLights = new QTreeWidgetItem(m_soccer);
    m_soccerRunningLights->setText(0, tr("Match Lights"));
    m_soccerCountDownMatchOver = new QTreeWidgetItem(m_soccer);
    m_soccerCountDownMatchOver->setText(0, tr("Count Down To Game Over Lights"));
    m_soccerWinner = new QTreeWidgetItem(m_soccer);
    m_soccerWinner->setText(0, tr("Winning Team Lights"));

    m_itemToPage = {
        {m_general, ui->generalLedConfigurationWidget},
        {m_idleScreen, ui->idleScreenWidget},
        {m_dmConfig, ui->deathMatchConfigLightsWidget},
        {m_dmPlayersReady, ui->deathMatchPlayersReadyLightsWidget},
        {m_dmRunningLights, ui->deathMatchMatchLightsWidget},
        {m_dmCountDownDoorDrop, ui->deathMatchCountDownLightsWidget},
        {m_dmDoorDrop, ui->deathMatchDoorDropLightsWidget},
        {m_dmCountDownMatchOver, ui->deathMatchCountDownToGameOver},
        {m_dmPlayerWins, ui->deathMatchWinningPlayerLightsWidget},
        {m_soccerConfig, ui->soccerConfigLightsWidget},
        {m_soccerRunningLights, ui->soccerMatchLightsWidget},
        {m_soccerPlayerReady, ui->soccerPlayerReadyLightsWidget},
        {m_soccerCountDownMatchOver, ui->soccerCountDownLightsWidget},
        {m_soccerWinner, ui->soccerWinningPlayerLightsWidget},
        {m_dmThree, ui->deathMatchThree},
        {m_dmTwo, ui->deathMatchTwo},
        {m_dmOne, ui->deathMatchOne},
        {m_dmFight, ui->deathMatchFight},
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
    ui->idleScreenWidget->init(&m_state->ledConfig()->idleConfiguration()->algoConfig());
    ui->deathMatchConfigLightsWidget->init(m_state->ledConfig()->deathMatchConfiguration()->configurationScreenLights());
    // TODO: This may also need some kind of flag to prevent navigation in the
    // event that we have unsaved changes.

    // TODO: finish connecting the lights and other related physical
    // state information.
}

void LEDControlWidget::selectionChangedChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous) {
    if (current->parent()) {
        qDebug() << "Parent text: " << current->parent()->text(0);
    } else {
        qDebug() << "No parent";
    }
    qDebug() << "Selection changed to: " << current->text(0);
    auto iter = m_itemToPage.find(current);
    if (iter == m_itemToPage.end()) {
        return;
    }
    ui->lightConfigDisplay->setCurrentWidget(iter.value());

}

