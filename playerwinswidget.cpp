#include "playerwinswidget.h"
#include "ui_playerwinswidget.h"
#include <QQmlEngine>
#include <QQmlContext>

PlayerWinsWidget::PlayerWinsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlayerWinsWidget)
    , m_qmlToLoad("cannon/main.qml")
{
    ui->setupUi(this);
    connect(ui->testButton, &QPushButton::pressed,
            [&]{
                emit confetti();
            });
    const QUrl url(u"qrc:/qmlproject/qmlproject/main.qml"_qs);
    ui->scene->engine()->addImportPath("C:/Users/Brian/Desktop/projects/build-BigBattleBoxUI-Desktop_Qt_6_4_3_MinGW_64_bit-Debug/thirdparty/Box2DQML/bin/lib");
    ui->scene->rootContext()->setContextProperty("mainWidget", this);
    ui->scene->setSource(url);

}

//void PlayerWinsWidget::autocomputeSceneSize(const QList<QRectF>& region) { }

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
