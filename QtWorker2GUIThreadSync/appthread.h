#ifndef APPTHREAD_H
#define APPTHREAD_H

#include <QDebug>
#include <QTime>
#include <QThread>
#include <QMutexLocker>
#include <QTimer>

class AppThread : public QObject
{
    Q_OBJECT

    QThread m_thread;

public:
    AppThread();
    ~AppThread() {}

    long mAppThreadTickInterval;
    QTimer mAppThreadTimer;
    void startAppThreadTimer();
    void updateSquaresVector();

signals:

private:

private slots:
    void appThreadTick();

};

#endif // APPTHREAD_H
