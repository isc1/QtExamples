#include <QDebug>
#include <QMutexLocker>
#include <QRandomGenerator>
#include <QTime>
#include <QTimer>
#include <QThread>

#include "appthread.h"
#include "square.h"

extern QVector< QVector<Square> > gSquaresVector;
extern int squaresnumberofrows;
extern int squaresnumberofcolumns;
extern int squaresrectsize;
extern bool readytorun;

AppThread::AppThread()
    : mAppThreadTickInterval(5)

{
    moveToThread(&m_thread);
    m_thread.start();
}

void AppThread::startAppThreadTimer()
{
    // associate the signal timeout() to the slot gameTick(), and start our update timer
    QObject::connect(&mAppThreadTimer, SIGNAL(timeout()), this, SLOT(appThreadTick()));
    mAppThreadTimer.start(mAppThreadTickInterval);
}

void AppThread::appThreadTick()
{
    if (readytorun)
    {
        updateSquaresVector();
    }

    // terrainmap vector processing:
}

void AppThread::updateSquaresVector()
{
    for (int x=0; x < squaresnumberofcolumns; x++)
        for (int y=0; y < squaresnumberofrows; y++)
        {
            // qrand()%2 is the "old" way, apparently QRandomGenerator::global()->bounded(2) is the "new" way
            // comment one or the other of the following two lines out to see the difference between the two PRNGs
            // (can only have one line uncommented at a time)
//            int newredvalue = gSquaresVector[x][y].redvalue + 1;
            int newredvalue = gSquaresVector[x][y].redvalue + qrand()%2+1;
//            int newredvalue = gSquaresVector[x][y].redvalue + QRandomGenerator::global()->bounded(2)+1;

            if (newredvalue > 245) newredvalue = 100;
            if (newredvalue < 100) newredvalue = 245;
            // avoid out of bounds values (from multi-threading) by making assignment
            // happen AFTER bounds checking
            gSquaresVector[x][y].redvalue = newredvalue;
        }
}
