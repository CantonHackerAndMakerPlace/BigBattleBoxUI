#include "playerwinswidget.h"
#include "ui_playerwinswidget.h"
#include <QQmlEngine>
#include <QQmlContext>

PlayerWinsWidget::PlayerWinsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlayerWinsWidget)
    , m_qmlToLoad("cannon/main.qml")
    , m_winner("spongebob")
{
    ui->setupUi(this);
}

PlayerWinsWidget::~PlayerWinsWidget() {
    delete ui;
}

QString PlayerWinsWidget::source() {
    return m_qmlToLoad;
}

void PlayerWinsWidget::setSource(QString path) {
    if (path != m_qmlToLoad) {
        m_qmlToLoad = path;
        emit sourceChanged(m_qmlToLoad);
    }
}

QString PlayerWinsWidget::winner() {
    return m_winner;
}

void PlayerWinsWidget::setWinner(QString name) {
    m_winner = name;
    ui->titleLabel->setText(m_winner + "\n WINS!!!");
    emit winnerChanged(m_winner);
}

void PlayerWinsWidget::startCelibration() {
    emit restartConfetti();
}
