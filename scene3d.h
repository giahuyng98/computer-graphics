#ifndef SCENE3D_H
#define SCENE3D_H

#include <QWidget>
#include <QGraphicsScene>
#include "cube.h"

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

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
    int lenx, leny;
    int offx, offy;
    int thickness = 5;
    Window *window;

};

#endif // SCENE3D_H
