TARGET = example
TEMPLATE = app
# QT       += core gui opengl widgets multimedia
QT       += core gui multimedia opengl widgets

# greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# # In Qt6 to use QOpenglWidget, we need add QT += openglwidgets.
greaterThan(QT_MAJOR_VERSION, 5){
    message(Building with Qt6 or Higher)
    QT += openglwidgets
}
QMAKE_CXXFLAGS += -std=c++17 -fPIC
# DEFINES += QT_NO_DEBUG_OUTPUT
# QMAKE_CXXFLAGS += -D_GLIBCXX_USE_CXX11_ABI=1
# Default rules for deployment.

qnx: target.path = /tmp/bin
else: unix:!android: target.path = /usr/bin
!isEmpty(target.path): INSTALLS += target



INCLUDEPATH +=$$PWD/../include
LIBS += -L$$OUT_PWD/../src -lQt5OpenCV
LIBS += -L$$PWD/../lib -lopencv_core -lopencv_videoio -lopencv_highgui
SOURCES += \
    ExampleWidget.cpp \
    main.cpp

HEADERS += \
    ExampleWidget.h



