#include "Qt5CameraPlayer.h"
#include <QDebug>

Qt5CameraPlayer::Qt5CameraPlayer(QWidget *parent)
    : Qt5CameraRender{parent}
{
    qt5CameraSettings = new Qt5CameraSettings("wangyonglin","qloongify",this);
    qt5CameraContext= new Qt5CameraContext(this);

    connect(qt5CameraContext,&Qt5CameraContext::signalCameraImage,this,&Qt5CameraPlayer::slotCameraImage);
}

void Qt5CameraPlayer::play(const QString &device)
{

    qt5CameraContext->initCamera(device);
    qt5CameraContext->startCamera();

}

void Qt5CameraPlayer::stop()
{
    qt5CameraContext->stopCamera();
}

void Qt5CameraPlayer::slotCameraImage(const QImage &image)
{
    displayImage(image);
    update();
}


