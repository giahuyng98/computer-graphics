#include "ellipse.h"
#include "scene.h"

Ellipse::Ellipse(int x, int y, int xRadius, int yRadius, Scene *scene, QGraphicsItem *parent)
:Item(scene, parent), x(x), y(y), xRadius(xRadius), yRadius(yRadius)
{
    drawEllipse();
}

void Ellipse::drawEllipse()
{
    for(const auto &point : Drawer::drawEllipse({x, y}, xRadius, yRadius)){
        drawPixel(point);
    }
}

QRectF Ellipse::boundingRect() const
{
    const int thickness = this->scene->getThickness();
    const int sceneXRadius = thickness * xRadius;
    const int sceneYRadius = thickness * yRadius;
    const QPoint topLeft = toScenePos(QPoint(x, y)) - QPoint(sceneXRadius, sceneYRadius);
    return QRectF(topLeft, QSize(sceneXRadius * 2, sceneYRadius * 2)).adjusted(0, 0, thickness, thickness);
}

QPainterPath Ellipse::shape() const{
    return path + fillPath;
}

void Ellipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Item::paint(painter, option, widget);
    painter->fillPath(fillPath, fillColor);
}

void Ellipse::setFillColor(const QColor &value)
{
    fillColor = value;
    reDraw();
}

int Ellipse::getYRadius() const
{
    return yRadius;
}

void Ellipse::setYRadius(int value)
{
    yRadius = value;
}

void Ellipse::fillEllipse()
{
    fillPath = QPainterPath();
    if (xRadius == 0 || yRadius == 0) return;
    for(const auto &point : Drawer::floodFill(Drawer::drawEllipse({x, y}, xRadius, yRadius), {x, y})){
        drawPixel(point, fillPath);
    }
}

int Ellipse::getXRadius() const
{
    return xRadius;
}

void Ellipse::setXRadius(int value)
{
    xRadius = value;
}

int Ellipse::getY() const
{
    return y;
}

void Ellipse::setY(int value)
{
    y = value;
}

int Ellipse::getX() const
{
    return x;
}

void Ellipse::setX(int value)
{
    x = value;
}

Item::Type Ellipse::getType() const
{
    return Type::ELLIPSE;
}

QColor Ellipse::getFillColor() const
{
    return fillColor;
}

void Ellipse::reDraw()
{
    path = QPainterPath();
    drawEllipse();
    if (fillColor != Qt::color0) fillEllipse();
    scene->update();
}

QPoint Ellipse::getPoint() const
{
    return {
        x, y
    };
}

void Ellipse::setPoint(const QPoint &point)
{
    x = point.x();
    y = point.y();
}
