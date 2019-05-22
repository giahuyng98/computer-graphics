#include "circle.h"
#include "scene.h"
Circle::Circle(int x, int y, int r, Scene *scene, QGraphicsItem *parent)
:Item(scene, parent), x(x), y(y), r(r)
{
    circleBres();
}

void Circle::drawCircle(int xc, int yc, int x, int y)
{
    drawPixel(xc + x, yc + y);
    drawPixel(xc - x, yc + y);
    drawPixel(xc + x, yc - y);
    drawPixel(xc - x, yc - y);

    drawPixel(xc + y, yc + x);
    drawPixel(xc - y, yc + x);
    drawPixel(xc + y, yc - x);
    drawPixel(xc - y, yc - x);
}

void Circle::circleBres()
{
    int p = 0, q = r;
    int d = 3 - 2 * r;

    drawCircle(x, y, p, q);
    while(q >= p)
    {

        ++p;
        if(d <= 0) d = d + 4*p + 6;
        else
        {
            --q;
            d = d + 4 * (p - q) + 10;
        }
        drawCircle(x, y, p, q);
    }

}

QRectF Circle::boundingRect() const
{
    const int thickness = this->scene->getThickness();
    const int len = thickness * r;
    QPoint topLeft = toScenePos({x, y});
    topLeft.setX(topLeft.x() - len * 2 - thickness * 2);
    topLeft.setY(topLeft.y() - len * 2 - thickness * 2);
    return QRectF(topLeft, QSize(len * 4 + thickness * 2, len * 4 + thickness * 2));
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->fillPath(path, brush);
}

int Circle::getR() const
{
    return r;
}

void Circle::setR(int value)
{
    r = value;
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
