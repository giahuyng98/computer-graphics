#include "circle.h"
#include "scene.h"


Circle::Circle(int x, int y, int r) : x(x), y(y), r(r)
{

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
    int tx = 0, ty = r;
    int d = 3 - 2 * r;
    drawCircle(x, y, tx, ty);
    while(ty >= tx)
    {
        ++tx;
        if(d > 0)
        {
            --ty;
            d = d + 4 * (tx - ty) + 10;
        }
        else d = d + 4 * tx + 6;
        drawCircle(x, y, tx, ty);
    }
}

QRectF Circle::boundingRect() const
{
//    int offx = ((Scene*)this->scene())->getOffx();
//    int offy = ((Scene*)this->scene())->getOffy();
//    int thickness = ((Scene*)this->scene())->getThickness();
//    return QRectF((x - r + offx) * thickness, (offy - y + r) * thickness,
//                  (x + r + offx) * thickness, (offy - y - r) * thickness);
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}
