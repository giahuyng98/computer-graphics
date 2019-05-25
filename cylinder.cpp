#include "cylinder.h"
#include "scene3d.h"
Cylinder::Cylinder(int cx, int cy, int cz, int r, int h, Scene3D *scene, QGraphicsItem *parent)
    :QGraphicsItem(parent), cx(cx), cy(cy), cz(cz), r(r), h(h), scene(scene)
{

}

QPainterPath Cylinder::shape() const
{
    return path;
}

QRectF Cylinder::boundingRect() const
{
    return QRectF(0, 0, scene->width(), scene->height());
}

void Cylinder::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    path = QPainterPath();
    drawCylinder();
    painter->fillPath(path, brush);
}

void Cylinder::drawPixel(const QPoint &point)
{
    const QPoint scenePos = scene->toScenePos(point);
    const int thickness = this->scene->getThickness();
    if (scenePos.x() < 0 || scenePos.x() > this->scene->width() ||
        scenePos.y() < 0 || scenePos.y() > this->scene->height()) return;
    path.addRect(QRect(scenePos, QSize(thickness, thickness)));
}

void Cylinder::drawCylinder()
{
    for(const auto &point : Drawer::drawCylinder(cx, cy, cz, r, h, scene->to2D)){
        drawPixel(point);
    }
}
