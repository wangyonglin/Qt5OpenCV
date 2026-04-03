#ifndef EXAMPLEWIDGET_H
#define EXAMPLEWIDGET_H

#include <QWidget>
#include <Qt5CameraPlayer>
class ExampleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ExampleWidget(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    Qt5CameraPlayer *qt5CameraPlayer;
};

#endif // EXAMPLEWIDGET_H
