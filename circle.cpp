#include "circle.h"
#include "scene.h"
#include <algorithm>
Circle::Circle(int x, int y, int r, Scene *scene, QGraphicsItem *parent)
:Item(scene, parent), x(x), y(y), r(r)
{
    circleBres();
}

void Circle::drawPixel(int x, int y)
{
    points.push_back({x, y});
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
    points.clear();
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

    std::sort(points.begin(), points.end(), [](const QPoint &p1, const QPoint &p2){
        return std::make_pair(p1.x(), p1.y()) < std::make_pair(p2.x(), p2.y());}
              );
    points.resize(std::unique(points.begin(), points.end())- points.begin());
    for(auto &p : points){
        Item::drawPixel(p.x(), p.y());
    }
}

QRectF Circle::boundingRect() const
{
    const int thickness = this->scene->getThickness();
    const int len = thickness * r;
    QPoint topLeft = toScenePos({x, y});
    topLeft.setX(topLeft.x() - len - thickness * 2);
    topLeft.setY(topLeft.y() - len - thickness * 2);
    return QRectF(topLeft, QSize(len * 2 + thickness * 4, len * 2 + thickness * 4));
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->fillPath(path, brush);
}
