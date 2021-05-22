#include "mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QLayout>
#include <QDebug>

extern qreal locx;
extern qreal locy;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , mGraphicsScene(nullptr)
    , mGraphicsView(nullptr)
    , mEllipseItem1(nullptr)
    , mEllipseItem2(nullptr)
    , mAppLoopUpdateInterval(1000)
{

    int mSceneWidth(1000), mSceneHeight(560);
    setGeometry(100,100,mSceneWidth, mSceneHeight);
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    mGraphicsScene = new QGraphicsScene(parent);
    mGraphicsView = new QGraphicsView(mGraphicsScene);
    mGraphicsView->setGeometry(0,0,mSceneWidth,mSceneHeight);

    QLayout *mylayout = new QHBoxLayout();
    centralWidget->setLayout(mylayout);
    mylayout->addWidget(mGraphicsView);

    // Retarded old way
    mEllipseItem1 = new QGraphicsEllipseItem(100,100,100,100);
    mGraphicsScene->addItem(mEllipseItem1);
    mEllipseItem1->setBrush(QBrush(QColor(200,0,0), Qt::SolidPattern));
    qDebug() << "Retarded circle's location: " << mEllipseItem1->pos();

    // Superfine new way
//    mEllipseItem2 = new QGraphicsEllipseItem(0,0,100,100);
    // ADD COMMENTARY EXPLAINING THAT YOU HAVE TO 1) ADD THE ITEM TO THE SCENE AND ***THEN**
    // 2) SetPos() ON THE ITEM OR ELSE THE ITEM DOES NOT LIVE IN ANY COORDINATE SYSTEM.
    // APPARENTLY.  SO SUCK ON THAT.
    mEllipseItem2 = new QGraphicsEllipseItem();
    mGraphicsScene->addItem(mEllipseItem2);
    mEllipseItem2->setRect(0,0,100,100);
    mEllipseItem2->setPos(400, 400);
    mEllipseItem2->setBrush(QBrush(QColor(0,200,0), Qt::SolidPattern));
    qDebug() << "Superfine circle's location: " << mEllipseItem2->pos();

    startAppLoopTimer();


//    mGraphicsScene->advance();
}

void MainWindow::startAppLoopTimer()
{
    // associate the signal timeout() to the slot appLoopTick(), and start our update timer
    QObject::connect(&mAppLoopTimer, SIGNAL(timeout()), this, SLOT(appLoopTick()));
    mAppLoopTimer.start(mAppLoopUpdateInterval);
    //qDebug() << __FUNCTION__ << "complete.";
}

void MainWindow::appLoopTick()
{
    updatecircle1();
    updatecircle2();
    mGraphicsScene->advance();
}

void MainWindow::updatecircle1()
{
    if (mEllipseItem1 == nullptr) return;

//    mEllipseItem2->setX(locx++);

    qDebug() << "mEllipseItem1->pos(): " << mEllipseItem1->pos();
    qDebug() << "mEllipseItem1->scenePos(): " << mEllipseItem1->scenePos();
    qDebug() << "mEllipseItem1->x(): " << mEllipseItem1->x();
    qDebug();

}

void MainWindow::updatecircle2()
{
    if (mEllipseItem2 == nullptr) return;

//    mEllipseItem2->setX(locx++);

    qDebug() << "mEllipseItem2->pos(): " << mEllipseItem2->pos();
    qDebug() << "mEllipseItem2->scenePos(): " << mEllipseItem2->scenePos();
    qDebug() << "mEllipseItem2->x(): " << mEllipseItem2->x();
    qDebug();

}

MainWindow::~MainWindow()
{
}

