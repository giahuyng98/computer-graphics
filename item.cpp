#include "item.h"
#include "scene.h"

void Item::drawPixel(int x, int y)
{
    const int offx = this->scene->getOffx();
    const int offy = this->scene->getOffy();
    const int thickness = this->scene->getThickness();
    QPainterPath tmp;
    tmp.addRect((x + offx) * thickness, (offy - y) * thickness, thickness, thickness);
    path = path.united(tmp);

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
