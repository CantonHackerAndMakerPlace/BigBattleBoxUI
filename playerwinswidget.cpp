#include "playerwinswidget.h"
#include "ui_playerwinswidget.h"
#include <QQmlEngine>
//#include "confettigi.h"
//#include <QtMath>

//static constexpr int ConfettiCount = 10;

PlayerWinsWidget::PlayerWinsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlayerWinsWidget)
//    , m_timer(new QTimer(this))
{
    ui->setupUi(this);
    const QUrl url(u"qrc:/qmlproject/qmlproject/main.qml"_qs);
//    const QUrl url(u"qrc:/Confetti/confetti.qml"_qs);
//    qDebug() << "QML_BOX2D_PLUGIN_DIR" << QML_BOX2D_PLUGIN_DIR;
    ui->scene->engine()->addImportPath("C:/Users/Brian/Desktop/projects/build-BigBattleBoxUI-Desktop_Qt_6_4_3_MinGW_64_bit-Debug/thirdparty/Box2DQML/bin/lib");
    ui->scene->setSource(url);
//    m_scene = new QGraphicsScene(this);
//    m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
//    ui->graphicsView->setScene(m_scene);

//    // Configuring physics for all objects.
//    b2Vec2 gravity(0.0f, -10.0f);
//    m_world = new b2World(gravity);

//    // Defining the ground body.
//    b2BodyDef groundBodyDef;
//    groundBodyDef.position.Set(0.0f, -10.0f);

//    m_groundBody = m_world->CreateBody(&groundBodyDef);

//    // Sets the shape of the ground.
//    b2PolygonShape groundBox;
//    groundBox.SetAsBox(50.0f, 10.0f);

//    // If we were to set the material of the body we'd need to do that here.
//    m_groundBody->CreateFixture(&groundBox, 0.0f);

//    QGraphicsRectItem *groundShape = new QGraphicsRectItem(QRectF(0.0f, 1080.0f/2, 1920.0f/2, 20.0f));
//    groundShape->setBrush(QBrush(QColorConstants::Red));

//    // Attempting to set up the QGraphicScene.
//    m_scene->addItem(groundShape);
//    constexpr size_t ConfettiCount = 10;
//    for (int i = 0; i < ConfettiCount; ++i) {
//        ConfettiGI *confetti = new ConfettiGI;
//        confetti->setPos(::sin((i * 6.28) / ConfettiCount) * 200,
//                         ::cos((i * 6.28) / ConfettiCount) * 200);
//        m_scene->addItem(confetti);
//    }
//    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
//    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
//    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
//    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
//    ui->graphicsView->setScene(m_scene);
//    ui->graphicsView->setInteractive(false);
//    ui->graphicsView->setResizeAnchor(QGraphicsView::AnchorViewCenter);
//    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
//    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    connect(m_scene, &QGraphicsScene::changed, this, &PlayerWinsWidget::autocomputeSceneSize);
//    // Update the scene using the timer.
//    connect(m_timer, &QTimer::timeout, m_scene, &QGraphicsScene::advance);
}

void PlayerWinsWidget::autocomputeSceneSize(const QList<QRectF>& region)
{
//    Q_UNUSED(region);

//    // Widget viewport recangle
//    QRectF widget_rect_in_scene(ui->graphicsView->mapToScene(-20, -20), ui->graphicsView->mapToScene(rect().bottomRight() + QPoint(20, 20)));

//    // Copy the new size from the old one
//    QPointF new_top_left(ui->graphicsView->sceneRect().topLeft());
//    QPointF new_bottom_right(ui->graphicsView->sceneRect().bottomRight());

//    // Check that the scene has a bigger limit in the top side
//    if (ui->graphicsView->sceneRect().top() > widget_rect_in_scene.top())
//        new_top_left.setY(widget_rect_in_scene.top());

//    // Check that the scene has a bigger limit in the bottom side
//    if (ui->graphicsView->sceneRect().bottom() < widget_rect_in_scene.bottom())
//        new_bottom_right.setY(widget_rect_in_scene.bottom());

//    // Check that the scene has a bigger limit in the left side
//    if (ui->graphicsView->sceneRect().left() > widget_rect_in_scene.left())
//        new_top_left.setX(widget_rect_in_scene.left());

//    // Check that the scene has a bigger limit in the right side
//    if (ui->graphicsView->sceneRect().right() < widget_rect_in_scene.right())
//        new_bottom_right.setX(widget_rect_in_scene.right());

//    // Set new scene size
//    ui->graphicsView->setSceneRect(QRectF(new_top_left, new_bottom_right));
}

PlayerWinsWidget::~PlayerWinsWidget() {
    delete ui;
}

void PlayerWinsWidget::start() {
//    m_timer->start(1000 / 33);
}

void PlayerWinsWidget::stop() {
//    m_timer->stop();
}
