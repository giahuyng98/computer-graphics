#include "rectangle.h"
#include "scene.h"
#include "line.h"

Rectangle::Rectangle(const QPoint &pos, const QSize &size, Scene *scene, QGraphicsItem *parent)
    : Item(scene, parent),
     line1(pos, QPoint(pos.x() + size.width(), pos.y()), scene, parent),
     line2(pos, QPoint(pos.x(), pos.y() - size.height()), scene, parent),
     line3(pos.x(), pos.y() - size.height(), pos.x() + size.width(), pos.y() - size.height(), scene, parent),
     line4(pos.x() + size.width(), pos.y(), pos.x() + size.width(), pos.y() - size.height(), scene, parent),
      pos(pos), size(size)
{
    path.addPath(line1.getPath());
    path.addPath(line2.getPath());
    path.addPath(line3.getPath());
    path.addPath(line4.getPath());
}

QRectF Rectangle::boundingRect() const
{
    const int thickness = this->scene->getThickness();
    return QRectF(toScenePos(pos), size * thickness);
}

void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->fillPath(path, QBrush(Qt::black));
}

QStringList Rectangle::getInfo() const
{

}
