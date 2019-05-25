#ifndef SCENE3D_H
#define SCENE3D_H

#include "scene.h"
#include "cube.h"
#include "sphere.h"
#include "cylinder.h"
class Window;

class Scene3D : public Scene
{
    Q_OBJECT
public:
    explicit Scene3D(QWidget *parent = nullptr);

    void addCube(int x, int y, int z, int width, int height, int length);

    void addSphere(int x, int y, int z, int r);

    void addCylinder(int cx, int cy, int cz, int r, int h);

    QPoint (*to2D)(int x, int y, int z) = Drawer::cavalier;

    void setMethod(bool method);

    void setThickness(int value) override;

    void translateItem(Item *item, int dx, int dy) = delete;

    void rotateItem(Item *item, int x, int y, int angle) = delete;

    void scaleItem(Item *item, float sx, float sy) = delete;

    void reflectItem(Item *item, int x, int y) = delete;

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
    float projection = CAVALIER;

};

#endif // SCENE3D_H
