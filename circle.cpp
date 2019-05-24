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

void Circle::drawCircle()
{
    for(const auto &point : Drawer::drawCircle({x, y}, r)){
        drawPixel(point);
    }
}

QRectF Circle::boundingRect() const
{
    const int thickness = this->scene->getThickness();
    const int len = thickness * r;
    QPoint topLeft = toScenePos({x, y});
    topLeft.setX(topLeft.x() - len - thickness);
    topLeft.setY(topLeft.y() - len - thickness);
    return QRectF(topLeft, QSize(len * 2 + thickness * 3, len * 2 + thickness * 3));
}

QPainterPath Circle::shape() const
{
    return path + fillPath;
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->fillPath(path, brush);
    painter->fillPath(fillPath, fillColor);
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
    path = QPainterPath();
    drawCircle();
    if (fillColor != Qt::color0) fill(fillColor);
    scene->update();
}

void Circle::fill(const QColor &color)
{
    fillColor = color;
    fillPath = QPainterPath();
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
