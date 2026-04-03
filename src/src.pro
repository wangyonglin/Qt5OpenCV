TARGET = Qt5OpenCV
TEMPLATE = lib
QT += core opengl multimedia widgets


# Default rules for deployment.
qnx: target.path = /tmp/lib
else: unix:!android: target.path = /usr/lib
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH +=$$PWD/../include

HEADERS += \
    Qt5CameraContext.h \
    Qt5CameraPlayer.h \
    Qt5CameraRender.h \
    Qt5CameraSettings.h \
    Qt5CameraThread.h

SOURCES += \
    Qt5CameraContext.cpp \
    Qt5CameraPlayer.cpp \
    Qt5CameraRender.cpp \
    Qt5CameraSettings.cpp \
    Qt5CameraThread.cpp

DISTFILES += \
    ../include /Qt5OpenCV
