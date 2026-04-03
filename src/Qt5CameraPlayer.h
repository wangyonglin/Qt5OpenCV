#ifndef QT5CAMERAPLAYER_H
#define QT5CAMERAPLAYER_H

#include <QWidget>
#include "Qt5CameraSettings.h"
#include "Qt5CameraRender.h"
#include "Qt5CameraContext.h"
class Qt5CameraPlayer : public Qt5CameraRender
{
    Q_OBJECT
public:
    explicit Qt5CameraPlayer(QWidget *parent = nullptr);
    void play(const QString &device=QString());
    void stop();
private:
    Qt5CameraContext * qt5CameraContext;
    Qt5CameraSettings *qt5CameraSettings;
public slots:
    void slotCameraImage(const QImage & image);
};

#endif // QT5CAMERAPLAYER_H
