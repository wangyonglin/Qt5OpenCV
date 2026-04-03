#include "ExampleWidget.h"
#include <QDebug>
#include <QKeyEvent>
#include <QResizeEvent>
#include <Qt5CameraPlayer>


ExampleWidget::ExampleWidget(QWidget *parent)
    : QWidget{parent}
{
    qDebug() << "ExampleWidget...";
   qt5CameraPlayer = new Qt5CameraPlayer(this);
    qt5CameraPlayer->play("/dev/video0");
}

void ExampleWidget::keyPressEvent(QKeyEvent *event)
{
    // 特殊处理
    if (event->key() == Qt::Key_F1)
    {
        qDebug() << "Key_F1 pressed - taking screenshot";

    }else if (event->key() == Qt::Key_F2)
    {
        qDebug() << "Key_F2 pressed - taking screenshot";
    }
}


void ExampleWidget::resizeEvent(QResizeEvent *event)
{
    qt5CameraPlayer->resize(event->size());
}
