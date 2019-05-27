#include "circle.h"
#include "scene.h"
#include <algorithm>
Circle::Circle(int x, int y, int r, Scene *scene, QGraphicsItem *parent)
:Item(scene, parent), x(x), y(y), r(r)
{
    drawCircle();
}

Item::Type Circle::getType() const
{
    return Type::CIRCLE;
}

QColor Circle::getFillColor() const
{
    return fillColor;
}

void Circle::drawCircle()
{
    for(const auto &point : Drawer::drawCircle({x, y}, r)){
        drawPixel(point);
    }
}

QRectF Circle::boundingRect() const
{
    const int thickness = this->scene->getThickness();
    const int sceneRadius = thickness * r;
    const QPoint topLeft = toScenePos({x, y}) - QPoint(sceneRadius, sceneRadius);
    return QRectF(topLeft, QSize(sceneRadius * 2, sceneRadius * 2)).adjusted(0, 0, thickness, thickness);
}

QPainterPath Circle::shape() const
{
    return path + fillPath;
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Item::paint(painter, option, widget);
    painter->fillPath(fillPath, fillColor);
}

void Circle::setFillColor(const QColor &value)
{
    fillColor = value;
    reDraw();
}

int Circle::getR() const
{
    return r;
}

void Circle::setR(int value)
{
    r = value;
}

QPoint Circle::getPoint() const
{
    return {x, y};
}

void Circle::setPoint(const QPoint &point)
{
    x = point.x();
    y = point.y();
}

void Circle::reDraw()
{
    Item::reDraw();
    path = QPainterPath();
    drawCircle();
    if (fillColor != Qt::color0) fillCircle();
    this->update();
    scene->update();
}

void Circle::fillCircle()
{    
    fillPath = QPainterPath();
    if (r == 0) return;
    for(const auto &point : Drawer::floodFill(Drawer::drawCircle({x, y}, r), {x, y})){
        drawPixel(point, fillPath);
    }
    scene->update();
}

int Circle::getY() const
{
    return y;
}

void Circle::setY(int value)
{
    y = value;
}

int Circle::getX() const
{
    return x;
}

void Circle::setX(int value)
{
    x = value;
}
