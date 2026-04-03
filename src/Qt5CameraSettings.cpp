#include "Qt5CameraSettings.h"

Qt5CameraSettings::Qt5CameraSettings(const QString &organization,
                                     const QString &application ,QObject *parent)
    : QObject{parent}
{
 m_settings = new QSettings(QSettings::NativeFormat, QSettings::UserScope, organization, application);
}

void Qt5CameraSettings::initSettings()
{

    m_settings->beginGroup("camera");
    m_camera_device=m_settings->value("device", "").toString();
    m_camera_width=m_settings->value("width", 1024).toDouble();
    m_camera_height=m_settings->value("height", 800).toDouble();
    m_settings->endGroup();
}
