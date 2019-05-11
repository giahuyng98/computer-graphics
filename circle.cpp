#include "circle.h"
#include "scene.h"


Circle::Circle(int x, int y, int r) : x(x), y(y), r(r)
{

}

QRectF Circle::boundingRect() const
{
    int offx = ((Scene*)this->scene())->getOffx();
    int offy = ((Scene*)this->scene())->getOffy();
    int thickness = ((Scene*)this->scene())->getThickness();
    return QRectF((x - r + offx) * thickness, (offy - y + r) * thickness,
                  (x + r + offx) * thickness, (offy - y - r) * thickness);
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}
