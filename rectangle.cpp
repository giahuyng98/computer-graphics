#include "rectangle.h"
#include "scene.h"
#include "line.h"

Rectangle::Rectangle(const QPoint &topLeft, const QPoint &topRight, const QPoint &bottomLeft, const QPoint &bottomRight, Scene *scene, QGraphicsItem *parent)
    : Item(scene, parent),
      topLeft(topLeft), topRight(topRight), bottomLeft(bottomLeft), bottomRight(bottomRight)
{
    drawRectangle();
}

Rectangle::Rectangle(const QPoint &topLeft, const QSize &size, Scene *scene, QGraphicsItem *parent)
    : Item(scene, parent), topLeft(topLeft), topRight(topLeft.x() + size.width(), topLeft.y()),
      bottomLeft(topLeft.x(), topLeft.y() - size.height()),
      bottomRight(topLeft.x() + size.width(), topLeft.y() - size.height())
{
    drawRectangle();
}

QRectF Rectangle::boundingRect() const
{        
    const int thickness = this->scene->getThickness();
    int minX = std::min({topLeft.x(), topRight.x(), bottomLeft.x(), bottomRight.x()});
    int minY = std::min({topLeft.y(), topRight.y(), bottomLeft.y(), bottomRight.y()});
    int maxX = std::max({topLeft.x(), topRight.x(), bottomLeft.x(), bottomRight.x()});
    int maxY = std::max({topLeft.y(), topRight.y(), bottomLeft.y(), bottomRight.y()});
    return QRectF(toScenePos({minX, maxY}) - QPoint(thickness, thickness) * 2,
                  toScenePos({maxX, minY}) + QPoint(thickness, thickness) * 2);
}

QPainterPath Rectangle::shape() const{
    return path + fillPath;
}

void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    Q_UNUSED(option);
//    Q_UNUSED(widget);
//    painter->fillPath(path, brush);
    Item::paint(painter, option, widget);
    painter->fillPath(fillPath, fillColor);
}

void Rectangle::drawRectangle()
{
    for(const auto &point : Drawer::drawRect(topLeft, topRight, bottomLeft, bottomRight)){
        drawPixel(point);
    }
}

void Rectangle::fillRectangle()
{
    fillPath = QPainterPath();
    for(const auto &point : Drawer::floodFill(
             Drawer::drawRect(topLeft, topRight, bottomLeft, bottomRight), {(topLeft + bottomRight) / 2})){
        drawPixel(point, fillPath);
    }
}

void Rectangle::setFillColor(const QColor &value)
{
    fillColor = value;
    reDraw();
}

QPoint Rectangle::getBottomRight() const
{
    return bottomRight;
}

void Rectangle::setBottomRight(const QPoint &value)
{
    bottomRight = value;
}

int Rectangle::getWidth() const
{
    return std::abs(topRight.x() - topLeft.x());
}

int Rectangle::getHeight() const
{
    return std::abs(topLeft.y() - bottomLeft.y());
}

QPoint Rectangle::getBottomLeft() const
{
    return bottomLeft;
}

void Rectangle::setBottomLeft(const QPoint &value)
{
    bottomLeft = value;
}

QPoint Rectangle::getTopRight() const
{
    return topRight;
}

void Rectangle::setTopRight(const QPoint &value)
{
    topRight = value;
}

QPoint Rectangle::getTopLeft() const
{
    return topLeft;
}

void Rectangle::setTopLeft(const QPoint &value)
{
    topLeft = value;
}

void Rectangle::reDraw()
{    
    path = QPainterPath();    
    drawRectangle();
    if (fillColor != Qt::color0) fillRectangle();
    scene->update();
}

Item::Type Rectangle::getType() const
{
    return Type::RECT;
}

QColor Rectangle::getFillColor() const
{
    return fillColor;
}
