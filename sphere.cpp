#include "sphere.h"
#include "scene3d.h"
#include <QPainter>
#include <cmath>


Sphere::Sphere(int x, int y, int z, int r, Scene3D *scene, QGraphicsItem *parent)
    :QGraphicsItem(parent), x(x), y(y), z(z), r(r), scene(scene)
{

}

QPainterPath Sphere::shape() const
{
    return path;
}

QRectF Sphere::boundingRect() const
{
    const int thickness = this->scene->getThickness();
    const int len = thickness * r;
    QPoint topLeft = toScenePos(scene->to2D(x, y, z));
    topLeft.setX(topLeft.x() - len - thickness);
    topLeft.setY(topLeft.y() - len - thickness);
    return QRectF(topLeft, QSize(len * 2 + thickness * 3, len * 2 + thickness * 3));
}

void Sphere::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    path = QPainterPath();
    drawSphere();
    painter->fillPath(path, brush);
}

void Sphere::drawPixel(const QPoint &point)
{
    const int offx = this->scene->getOffx();
    const int offy = this->scene->getOffy();
    const int thickness = this->scene->getThickness();
    path.addRect((point.x() + offx) * thickness, (offy - point.y()) * thickness, thickness, thickness);
}

void Sphere::drawSphere()
{
    for(const auto &point : Drawer::drawSphere(x, y, z, r, scene->to2D)){
        drawPixel(point);
    }
}

QPoint Sphere::toScenePos(const QPoint &userPos) const
{
    const int offx = this->scene->getOffx();
    const int offy = this->scene->getOffy();
    const int thickness = this->scene->getThickness();
    return QPoint((userPos.x() + offx) * thickness, (offy - userPos.y()) * thickness);
}
