#ifndef QT5CAMERASETTINGS_H
#define QT5CAMERASETTINGS_H

#include <QObject>
#include <QSettings>

class Qt5CameraSettings : public QObject
{
    Q_OBJECT
public:
    explicit Qt5CameraSettings(const QString &organization,
                               const QString &application = QString(),QObject *parent = nullptr);
    void initSettings();

private:
    QSettings *m_settings=nullptr;
    QString m_camera_device;
    double m_camera_width;
    double m_camera_height;
};

#endif // QT5CAMERASETTINGS_H
