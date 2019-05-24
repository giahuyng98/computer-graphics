#include "item.h"
#include "scene.h"

void Item::drawPixel(int x, int y)
{
    drawPixel(x, y, path);
}

void Item::drawPixel(const QPoint &p)
{
    drawPixel(p.x(), p.y(), path);
}

void Item::drawPixel(int x, int y, QPainterPath &painterPath)
{
    const int offx = this->scene->getOffx();
    const int offy = this->scene->getOffy();
    const int thickness = this->scene->getThickness();
    painterPath.addRect((x + offx) * thickness, (offy - y) * thickness, thickness, thickness);
}

void Item::drawPixel(const QPoint &p, QPainterPath &painterPath)
{
    const int offx = this->scene->getOffx();
    const int offy = this->scene->getOffy();
    const int thickness = this->scene->getThickness();
    painterPath.addRect((p.x() + offx) * thickness, (offy - p.y()) * thickness, thickness, thickness);
}

QPoint Item::toScenePos(const QPoint &userPos) const
{
    const int offx = this->scene->getOffx();
    const int offy = this->scene->getOffy();
    const int thickness = this->scene->getThickness();
    return QPoint((userPos.x() + offx) * thickness, (offy - userPos.y()) * thickness);
}

void Item::setBrush(const QBrush &value)
{
    brush = value;
    update();
}

QPainterPath Item::getPath() const
{
    return path;
}

Item::Item(Scene *scene, QGraphicsItem *parent)
    : QGraphicsItem(parent), scene(scene)
{
    setFlag(ItemIsSelectable);
}

Item::Type Item::getType() const
{
    return NULL_TYPE;
}

//QStringList Item::getInfo() const
//{
//    return QStringList();
//}

QPainterPath Item::shape() const{
    return path;
}

void Item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->fillPath(path, brush);
}
