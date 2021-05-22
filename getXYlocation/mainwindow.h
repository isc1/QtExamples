#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsEllipseItem>
#include <QGraphicsView>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QWidget *centralWidget;
    QGraphicsScene *mGraphicsScene;
    QGraphicsView *mGraphicsView;
    QGraphicsEllipseItem *mEllipseItem1, *mEllipseItem2;
    long mAppLoopUpdateInterval;
    QTimer mAppLoopTimer;
    void startAppLoopTimer();
    void updatecircle1();
    void updatecircle2();

private slots:
    void appLoopTick();

};
#endif // MAINWINDOW_H
