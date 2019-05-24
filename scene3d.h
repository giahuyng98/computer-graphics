#ifndef SCENE3D_H
#define SCENE3D_H

#include <QWidget>
#include <QGraphicsScene>
#include "cube.h"
#include "sphere.h"
#include "apidrawer.h"

class Window;

class Scene3D : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene3D(QWidget *parent = nullptr);
    int getOffx() const;
    int getOffy() const;
    int getThickness() const;
    void setWindow(Window *value);
    void addCube(int x, int y, int z, int width, int height, int length);
    void addSphere(int x, int y, int z, int r);
    QPoint (*to2D)(int x, int y, int z) = Drawer::cavalier;
    void setMethod(bool method);

    void setThickness(int value);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
    int lenx, leny;
    int offx, offy;
    int thickness = 5;
    float projection = CAVALIER;
    Window *window;

};

#endif // SCENE3D_H
