#include "mainwindow.h"
#include "square.h"
#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QRandomGenerator>

extern QVector< QVector<Square> > gSquaresVector;
extern int squaresnumberofrows;
extern int squaresnumberofcolumns;
extern int squaresrectsize;
extern bool readytorun;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

    , mProgramName("QtApp2GUIThreadSync")
    , mGraphicsScene(Q_NULLPTR)
    , mGraphicsView(Q_NULLPTR)
    , mWindowOriginX(0) // 56
    , mWindowOriginY(0) // 100
    , mWindowWidth(squaresrectsize*squaresnumberofcolumns+squaresrectsize)
    , mWindowHeight(squaresrectsize*squaresnumberofrows+squaresrectsize)
    , mWindowSceneXOffset(0) // 60
    , mWindowSceneYOffset(0) // 100
    , mWindowViewOffset(0) // 10
    , mSceneWidth(squaresrectsize*squaresnumberofcolumns)
    , mSceneHeight(squaresrectsize*squaresnumberofrows)
    , mEventLoopUpdateInterval(10)
{
    qDebug() << mProgramName << __FUNCTION__ << " Started";

    setupGUI();
    setupApp();
    startEventLoopTimer(); // fires eventLoopTick()
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupGUI()
{
    qDebug() << "2dsim07 " << __FUNCTION__ << " Started";

    setGeometry(mWindowOriginX, mWindowOriginY, mWindowWidth, mWindowHeight);
//    QWidget *centralWidget = new QWidget(this);

    // set up the scene & view
    mGraphicsScene  = new QGraphicsScene(0, 0, mSceneWidth, mSceneHeight);
    mGraphicsView = new QGraphicsView(mGraphicsScene, nullptr);
    mGraphicsView->setGeometry(20,20, mSceneWidth, mSceneHeight);

    this->setCentralWidget(mGraphicsView);
//    setCentralWidget(centralWidget);

//    mWindowWidth = geometry().width();
//    mWindowHeight = geometry().height();
//    mGraphicsView->centerOn(mSceneWidth/2, mSceneHeight/2);
}

void MainWindow::setupApp()
{
    // apparently we're not supposed to use qrand() anymore, but rather get random numbers this way as of Qt5 or so
    //    quint32 r1 = QRandomGenerator::global()->generate();
    //    int r2 = QRandomGenerator::global()->bounded(1000);

    qDebug() << mProgramName << __FUNCTION__ << " Started";

    // setupSpazArray();

    qDebug() << mProgramName << __FUNCTION__ << "mSceneWidth,mSceneHeight " << mSceneWidth << "," << mSceneHeight;
    qDebug() << mProgramName << __FUNCTION__ << "mWindowOriginX,mWindowOriginY " << mWindowOriginX << "," << mWindowOriginY;
    qDebug() << mProgramName << __FUNCTION__ << "mWindowWidth,mWindowHeight " << mWindowWidth << "," << mWindowHeight;
    qDebug() << mProgramName << __FUNCTION__ << "mWindowSceneXOffset,mWindowSceneYOffset " << mWindowSceneXOffset << "," << mWindowSceneYOffset;
    qDebug() << mProgramName << __FUNCTION__ << "mWindowViewOffset" << mWindowViewOffset;

    QPen mypen;
    QBrush mybrush;
    mypen.setColor(QColor(Qt::transparent));
    mybrush.setColor(QColor(255,0,0));
    //    mypen.setStyle(Qt::PenStyle(1)); // 4REF

    int squarecount=0;

    for (int x=0; x < squaresnumberofcolumns; x++)
    {
        gSquaresVector.push_back(*new QVector<Square>);
        mRectItem2DVector.push_back(*new QVector<QGraphicsRectItem*>);
        for (int y=0; y < squaresnumberofrows; y++)
        {
            Square mysquare;
            gSquaresVector[x].push_back(mysquare);
//            int newredvalue = QRandomGenerator::global()->bounded(255);
            int newredvalue = 0;
            gSquaresVector[x][y].redvalue = newredvalue;
            mRectItem2DVector[x].push_back(new QGraphicsRectItem(QRect(0,0,squaresrectsize,squaresrectsize)));
            mRectItem2DVector[x][y]->setPos((x*squaresrectsize+5), (y*squaresrectsize+5));
            mRectItem2DVector[x][y]->setBrush(QColor(gSquaresVector[x][y].redvalue,0,0));
            mRectItem2DVector[x][y]->setPen(mypen);
            mRectItem2DVector[x][y]->setZValue(50);
            mGraphicsScene->addItem(mRectItem2DVector[x][y]);
            squarecount++;
        }
    }

    readytorun = true;
    qDebug() << mProgramName << " " << __FUNCTION__ << "squarecount: " << squarecount;
}

void MainWindow::startEventLoopTimer()
{
    // associate the signal timeout() to the slot gameTick(), and start our update timer
    QObject::connect(&mEventLoopTimer, SIGNAL(timeout()), this, SLOT(eventLoopTick()));
    mEventLoopTimer.start(mEventLoopUpdateInterval);
}

void MainWindow::eventLoopTick()
{
    // qDebug() << mProgramName << " " << __FUNCTION__ << " Started";

    for (int x=0; x < squaresnumberofcolumns; x++)
    {
        for (int y=0; y < squaresnumberofrows; y++)
        {
            mRectItem2DVector[x][y]->setBrush(QColor(gSquaresVector[x][y].redvalue,0,0));
        }
    }

    mGraphicsScene->advance();
}

