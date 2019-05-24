#include "cube.h"
#include "scene3d.h"
#include "line.h"
#include <QPainter>
#include <cmath>

Cube::Cube(int x, int y, int z, int width, int height, int length, Scene3D *scene, QGraphicsItem *parent)
    :QGraphicsItem(parent), x(x), y(y), z(z), width(width), height(height), length(length), scene(scene)
{
//    drawCube();
}

QPainterPath Cube::shape() const
{
    return path;
}

QRectF Cube::boundingRect() const
{
    const int thickness = this->scene->getThickness();
    QPoint botLeft = scene->toScenePos(scene->to2D(x, y, z));
    botLeft.setX(botLeft.x() - width * thickness - thickness * 2);
    botLeft.setY(botLeft.y() - height * thickness - thickness * 2);
    return QRectF(botLeft, QSize((length + width) * thickness + thickness * 4, (height + width) * thickness + thickness * 4));
}

void Cube::drawPixel(const QPoint &point)
{
    const QPoint scenePos = scene->toScenePos(point);
    const int thickness = this->scene->getThickness();
    if (scenePos.x() < 0 || scenePos.x() > this->scene->width() ||
        scenePos.y() < 0 || scenePos.y() > this->scene->height()) return;
    path.addRect(QRect(scenePos, QSize(thickness, thickness)));
}

void Cube::drawCube()
{
    for(const auto &point : Drawer::drawCube(x, y, z, width, height, length, scene->to2D)){
        drawPixel(point);
    }
}

void Cube::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    path = QPainterPath();
    drawCube();
    painter->fillPath(path, brush);
}
