#include "mainwindow.h"

#include <QApplication>
#include "appthread.h"
#include "square.h"

extern QVector< QVector<Square> > gSquaresVector;
QVector< QVector<Square> > gSquaresVector = *new QVector< QVector<Square> >;
extern int squaresnumberofcolumns;
int squaresnumberofcolumns = 100;
extern int squaresnumberofrows;
int squaresnumberofrows = 50;
extern int squaresrectsize;
int squaresrectsize = 5;
extern bool readytorun;
bool readytorun = false;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    AppThread* thisappthread = new AppThread();
    thisappthread->startAppThreadTimer();
    return a.exec();
}
