#include "Qt5CameraContext.h"
#include <QDebug>
#include <QImage>

Qt5CameraContext::Qt5CameraContext(QObject *parent)
    : QObject{parent},
    device("/dev/video0")
{

    bool ok = connect(&fpsTimer, &QTimer::timeout, this, &Qt5CameraContext::slotCameraFrame);
    Q_ASSERT(ok);
}

void Qt5CameraContext::initCamera(const QString &device)
{
    capture= make_unique<VideoCapture>(device.toStdString());
}

bool Qt5CameraContext::startCamera()
{
    // capture.release();
    if (!capture->isOpened()) {
        qFatal("无法打开摄像头");
        return false;
    }
    capture->set(CAP_PROP_FRAME_WIDTH,1920);
    capture->set(CAP_PROP_FRAME_HEIGHT,1080);
    capture->set(CAP_PROP_FPS,60);

    //    #关闭白平衡，解决偏色问题
    capture->set(CAP_PROP_AUTO_WB,0);
    //    #设置曝光为手动模式
    capture->set(CAP_PROP_AUTO_EXPOSURE,1);
    //    #设置曝光的值为0
    capture->set(CAP_PROP_EXPOSURE,100);
    // 启动定时器，每 1000ms（1秒）触发一次 slotCameraFrame

    fpsTimer.start(1);
    return true;
}


void Qt5CameraContext::stopCamera()
{
    fpsTimer.stop();
}

void Qt5CameraContext::slotCameraFrame()
{
    Mat frame;
    if(!capture->read(frame)) {
        startCamera();
        return;
    };
    if(!frame.empty()){

        Mat hsvframe, mask;
        Scalar  lowerb=  Scalar(35, 43, 46);
        Scalar  upperb=  Scalar(155, 255, 255);
        hsvframe=InRangeHSV(frame,mask,lowerb,upperb);
        Mat matframe= Matting(frame,mask);
        QImage image= MattoImage(matframe);
        if(!image.isNull()){
            // image.scaled(size(), Qt::IgnoreAspectRatio);
            emit signalCameraImage(image);
        }
    }
}
Mat Qt5CameraContext::Matting(Mat frame, Mat mask)
{
    Mat dst = Mat::zeros(frame.size(), CV_8UC4);
    int dims =  dst.channels();
    //qDebug() << "######" << dims << "######";
    for (int i = 0; i < frame.rows; i++)
    {
        for (int j = 0; j < frame.cols; j++)
        {
            int p = mask.at<uchar>(i, j);  //传入的mask是张二值图,p为当前mask像素值

            if (p == 0)
            {   //代表mask此时为前景，将绿幕视频中的前景像素赋给dst
                dst.at<Vec4b>(i, j)[0] = frame.at<Vec3b>(i, j)[0];
                dst.at<Vec4b>(i, j)[1] = frame.at<Vec3b>(i, j)[1];
                dst.at<Vec4b>(i, j)[2] = frame.at<Vec3b>(i, j)[2];
                dst.at<Vec4b>(i, j)[3] = 255;
            } else if(p == 255){
                dst.at<Vec4b>(i, j) =  Vec4b(0, 0, 0,0);
            }
        }
    }

    return dst;
}
Mat Qt5CameraContext::InRangeHSV(const Mat &frame,Mat &mask,Scalar & lowerb,Scalar & upperb)
{
    Mat hsv;
    //将每一帧的图像转换到hsv空间
    cvtColor(frame, hsv, COLOR_BGR2HSV);
    //绿幕的颜色范围，将结果存在mask中
    // inRange(hsv, lowerb,upperb, mask);
    inRange(hsv, lowerb, upperb, mask);
    //对mask进行形态学操作
    //定义一个结构
    Mat k = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
    //对mask进行形态学闭操作
    morphologyEx(mask, mask, MORPH_CLOSE, k);
    erode(mask, mask, k);
    //高斯模糊
    GaussianBlur(mask, mask, Size(3, 3), 0, 0);
    return mask;
}
QImage Qt5CameraContext::MattoImage(const cv::Mat &inMat) {
    switch (inMat.type()) {
    // 8-bit, 4 channel
    case CV_8UC4: {
        QImage image(static_cast<uchar *>(inMat.data), inMat.cols, inMat.rows, static_cast<int>(inMat.step), QImage::Format_ARGB32);
        return image;
    }
        // 8-bit, 3 channel
    case CV_8UC3: {
        Mat dstMat;
        cvtColor(inMat,dstMat, COLOR_BGR2RGB);
        QImage image(static_cast<uchar *>(dstMat.data), dstMat.cols, dstMat.rows, static_cast<int>(dstMat.step), QImage::Format_RGB888);
        return image.rgbSwapped();
    }
        // 8-bit, 1 channel
    case CV_8UC1: {
        static QVector<QRgb> sColorTable;
        // only create our color table once
        if (sColorTable.isEmpty()) {
            for (int i = 0; i < 256; ++i) {
                sColorTable.push_back(qRgb(i, i, i));
            }
        }
        QImage image(static_cast<uchar *>(inMat.data), inMat.cols, inMat.rows, static_cast<int>(inMat.step), QImage::Format_Indexed8);
        image.setColorTable(sColorTable);
        return image;
    }
    default:
        break;
    }

    return QImage();
}
