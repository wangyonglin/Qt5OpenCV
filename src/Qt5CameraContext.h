#ifndef QT5CAMERACONTEXT_H
#define QT5CAMERACONTEXT_H

#include <QObject>
#include <QTimer>

#include "Qt5CameraThread.h"
#include "Qt5CameraSettings.h"

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

using namespace cv;
using namespace std;

class Qt5CameraContext : public QObject
{
    Q_OBJECT
public:
    explicit Qt5CameraContext(QObject *parent = nullptr);
    void initCamera(const QString &device="/dev/video0");
    bool startCamera();
    void stopCamera();

    Mat InRangeHSV(const Mat &frame, Mat &mask, Scalar &lowerb, Scalar &upperb);
    Mat Matting(Mat frame, Mat mask);
    QImage MattoImage(const Mat &inMat);
private:
    QString device;
    QTimer fpsTimer;
    unique_ptr<VideoCapture> capture;
    Mat frame;

signals:
    void signalCameraImage(const QImage &image);
public slots:
     void slotCameraFrame();
};

#endif // QT5CAMERACONTEXT_H
