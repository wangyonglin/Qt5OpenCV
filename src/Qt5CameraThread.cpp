#include "Qt5CameraThread.h"
#include <QDebug>
#include <QDateTime>

Qt5CameraThread::Qt5CameraThread(QObject *parent)
    : QThread{parent}
    , stopFlag(true)  // 初始为true，表示未启动Qt5ThreadObject
    , pauseFlag(false)
    ,timeout(100)
{
}


void Qt5CameraThread::start(Priority pri)
{
    QMutexLocker locker(&mutex);
    if(!QThread::isRunning()){
        stopFlag.store(false);
        pauseFlag.store(true);
        QThread::start(pri);
    }

}

void Qt5CameraThread::stop()
{
    QMutexLocker locker(&mutex);
    stopFlag.store(true);
    pauseFlag.store(false);
    // 唤醒所有等待的线程
    waitFlag.wakeAll();

    // 等待线程结束
    if (QThread::isRunning()) {
        quit();
        wait(1000);
    }
}


void Qt5CameraThread::pause()
{
    QMutexLocker locker(&mutex);
    pauseFlag.store(true);
}

void Qt5CameraThread::resume()
{
    QMutexLocker locker(&mutex);
    pauseFlag.store(false);
}

bool Qt5CameraThread::state()
{
    return (QThread::isRunning()&& !stopFlag.load() && !pauseFlag.load());
}



void Qt5CameraThread::reset()
{
    if(QThread::isRunning()){
        QMutexLocker locker(&mutex);
        stopFlag.store(false);
        pauseFlag.store(true);
        waitFlag.wakeAll();
    }
}

void Qt5CameraThread::run()
{
    while (!stopFlag.load()) {
        if(pauseFlag.load()){
            QMutexLocker locker(&mutex);
            waitFlag.wait(&mutex, timeout);
        }else{
            thread();
        }
    }
    reset();
    qDebug() << QThread::currentThreadId();
}
