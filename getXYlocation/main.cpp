#include "mainwindow.h"

#include <QApplication>

extern qreal locx;
extern qreal locy;
qreal locx = 0;
qreal locy = 0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
