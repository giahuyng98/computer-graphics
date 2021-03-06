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
    const QPoint scenePos = toScenePos({x, y});
    const int thickness = this->scene->getThickness();
    if (scenePos.x() < 0 || scenePos.x() > this->scene->width() ||
        scenePos.y() < 0 || scenePos.y() > this->scene->height()) return;
    painterPath.addRect(QRect(scenePos, QSize(thickness, thickness)));
}

void Item::drawPixel(const QPoint &p, QPainterPath &painterPath)
{
    drawPixel(p.x(), p.y(), painterPath);
}

QPoint Item::toScenePos(const QPoint &userPos) const
{
    return scene->toScenePos(userPos);
}

void Item::setBrush(const QBrush &value)
{
    brush = value;
    scene->update();
}

QColor Item::getColor() const
{
    return brush.color();
}

Item::Item(Scene *scene, QGraphicsItem *parent)
    : QGraphicsItem(parent), scene(scene)
{
    setFlags(ItemIsSelectable | ItemSendsScenePositionChanges);
}

QColor Item::getFillColor() const
{
    return Qt::color0;
}

void Item::reDraw(){
    QGraphicsItem::prepareGeometryChange();
}

QPainterPath Item::shape() const{
    return path;
}

void Item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//    setSelected(true);
    QGraphicsItem::mousePressEvent(event);
}

void Item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->fillPath(path, brush);
    if (isSelected()) {
        painter->setPen(QPen(Qt::black, 1, Qt::DashLine));
        painter->setOpacity(0.5);
        painter->drawRect(boundingRect());
    }
}
