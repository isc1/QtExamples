#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QMainWindow>
#include <QTimer>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString mProgramName;

    // Graphics related
    QGraphicsScene *mGraphicsScene;
    QGraphicsView *mGraphicsView;


    int mWindowOriginX;
    int mWindowOriginY;
    int mWindowWidth;
    int mWindowHeight;
    int mWindowSceneXOffset;
    int mWindowSceneYOffset;
    int mWindowViewOffset;
    int mSceneWidth;
    int mSceneHeight;

    QTimer mEventLoopTimer;
    int mEventLoopUpdateInterval;

    void setupGUI();
    void drawGrid();
    void setupApp();

    void setupEventLoop();
    void startEventLoopTimer(); // runs from eventLoopTick() QTimer signal

private:
    QVector< QVector<QGraphicsRectItem*> > mRectItem2DVector;

private slots:
    void eventLoopTick();
};
#endif // MAINWINDOW_H
