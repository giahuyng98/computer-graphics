#include "line.h"
#include "scene.h"

Line::Line(Scene *scene, QGraphicsItem *parent)
    :Item(scene, parent)
{
}

Line::Line(int x1, int y1, int x2, int y2, Scene *scene, QGraphicsItem *parent)
    :Item(scene, parent), x1(x1), y1(y1), x2(x2), y2(y2)
{
    drawLine();
}

Line::Line(const QPoint &from, const QPoint &to, Scene *scene, QGraphicsItem *parent)
    : Line(from.x(), from.y(), to.x(), to.y(), scene, parent)
{
}

Item::Type Line::getType() const
{
    return Type::LINE;
}

QPoint Line::getPoint1() const
{
    return {
        x1, y1
    };
}

QPoint Line::getPoint2() const
{
    return {
        x2, y2
    };
}

void Line::setPoint1(const QPoint &point)
{
    x1 = point.x();
    y1 = point.y();
}

void Line::setPoint2(const QPoint &point)
{
    x2 = point.x();
    y2 = point.y();
}

QRectF Line::boundingRect() const
{
    const int offx = this->scene->getOffx();
    const int offy = this->scene->getOffy();
    const int thickness = this->scene->getThickness();
    return QRectF((std::min(x1, x2) + offx) * thickness, (offy - std::max(y1, y2)) * thickness,
                  (std::max(x1, x2) + offx) * thickness, (offy - std::min(y1, y2)) * thickness);
}

void Line::drawLine()
{
    for(const auto &point : Drawer::drawLine(x1, y1, x2, y2)){
        drawPixel(point);
    }
}


int Line::getY2() const
{
    return y2;
}

void Line::setY2(int value)
{
    y2 = value;
}

void Line::reDraw()
{
    path = QPainterPath();    
    drawLine();
    scene->update();
}

int Line::getX2() const
{
    return x2;
}

void Line::setX2(int value)
{
    x2 = value;
}

int Line::getY1() const
{
    return y1;
}

void Line::setY1(int value)
{
    y1 = value;
}

int Line::getX1() const
{
    return x1;
}

void Line::setX1(int value)
{
    x1 = value;
}
