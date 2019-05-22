#ifndef SCENE3D_H
#define SCENE3D_H

#include <QWidget>
#include <QGraphicsScene>

class Window;

class Scene3D : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene3D(QWidget *parent = nullptr);

    void setWindow(Window *value);

private:
    int lenx, leny;
    int offx, offy;
    int thickness = 5;
    Window *window;

};

#endif // SCENE3D_H
