#include "cube.h"
#include "scene3d.h"
#include "line.h"
#include <QPainter>

Cube::Cube(int x, int y, int z, int width, int height, int length, Scene3D *scene, QGraphicsItem *parent)
    :QGraphicsItem(parent), x(x), y(y), z(z), width(width), height(height), length(length), scene(scene)
{
    drawLine(x, y, width, height);
}

QPainterPath Cube::shape() const
{
    return path;
}

QRectF Cube::boundingRect() const
{
    const int thickness = this->scene->getThickness();
    QPoint topLeft = toScenePos(QPoint(x, y));
    return QRectF({0, 0}, QSize(1200, 600));
}

void Cube::drawPixel(int x, int y)
{
    const int offx = this->scene->getOffx();
    const int offy = this->scene->getOffy();
    const int thickness = this->scene->getThickness();
    path.addRect((x + offx) * thickness, (offy - y) * thickness, thickness, thickness);
}

QPoint Cube::toScenePos(const QPoint &userPos) const
{
    const int offx = this->scene->getOffx();
    const int offy = this->scene->getOffy();
    const int thickness = this->scene->getThickness();
    return QPoint((userPos.x() + offx) * thickness, (offy - userPos.y()) * thickness);
}

void Cube::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->fillPath(path, brush);
}
void Cube::drawLine(int x1, int y1, int x2, int y2)
{
    if (std::abs(y2 - y1) < std::abs(x2 - x1)){
        if (x1 > x2)
            drawLineLow(x2, y2, x1, y1);
        else
            drawLineLow(x1, y1, x2, y2);
    } else if (y1 > y2){
        drawLineHigh(x2, y2, x1, y1);
    } else
        drawLineHigh(x1, y1, x2, y2);
}

void Cube::drawLineLow(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int ystep = 1;
    if (dy < 0){
        ystep = -1;
        dy = -dy;
    }
    int d = (dy << 1) - dx;
    for(int x = x1, y = y1; x <= x2; ++x){
        drawPixel(x, y);
        if (d > 0){
            y += ystep;
            d -= dx << 1;
        }
        d += dy << 1;
    }
}

void Cube::drawLineHigh(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int xstep = 1;
    if (dx < 0){
        xstep = -1;
        dx = -dx;
    }
    int d = (dx << 1) - dy;
    for(int x = x1, y = y1; y <= y2; ++y){
        drawPixel(x, y);
        if (d > 0){
            x += xstep;
            d -= dy << 1;
        }
        d += dx << 1;
    }
}
