#include <QApplication>
#include <QDebug>
#include <QDateTime>
#include <QTimer>
#include <istream>
#include <QGuiApplication>
#include <QScreen>
#include "ExampleWidget.h"

// 基本遍历方式

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    // 获取屏幕尺寸
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();

    ExampleWidget example;
    example.resize(screenGeometry.size());
    example.showFullScreen();

    return app.exec();
}
