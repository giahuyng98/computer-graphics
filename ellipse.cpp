#include "ellipse.h"
#include "scene.h"

Ellipse::Ellipse(int x, int y, int xRadius, int yRadius, Scene *scene, QGraphicsItem *parent)
:Item(scene, parent), x(x), y(y), xRadius(xRadius), yRadius(yRadius)
{
    ellipseMidpoint(x, y, xRadius, yRadius);
}

void Ellipse::drawEllipse(int xs, int ys, int x, int y)
{
    drawPixel(xs + x, ys + y);
    drawPixel(xs - x, ys - y);
    drawPixel(xs + x, ys - y);
    drawPixel(xs - x, ys + y);
}

void Ellipse::ellipseMidpoint(int xc, int yc, int rx, int ry)
{
    double dx, dy, d1, d2, tx, ty;
    tx = 0;
    ty = ry;
    d1 = (ry * ry) - (rx * rx * ry) + (0.25 * rx * rx);
    dx = 2 * ry * ry * tx;
    dy = 2 * rx * rx * ty;
    while(dx < dy)
    {
        drawEllipse(xc, yc, tx, ty);
        if(d1 < 0)
        {
            ++tx;
            dx = dx + (2 * ry * ry);
            d1 = d1 + dx + (ry * ry);
        }
        else
        {
            ++tx;
            --ty;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d1 = d1 + dx - dy + (ry * ry);
        }
    }
    d2 = ((ry * ry) * ((tx + 0.5) * (tx + 0.5))) +
         ((rx * rx) * ((ty - 1) * (ty - 1))) -
         (rx * rx * ry * ry);
    while(ty >= 0)
    {
        drawEllipse(xc, yc, tx, ty);
        if(d2 > 0)
        {
            --ty;
            dy = dy - (2 * rx * rx);
            d2 = d2 + (rx * rx) - dy;
        }
        else
        {
            --ty;
            ++tx;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d2 = d2 + dx - dy + (rx * rx);
        }
    }
    std::sort(points.begin(), points.end(), [](const QPoint &p1, const QPoint &p2){
        return std::make_pair(p1.x(), p1.y()) < std::make_pair(p2.x(), p2.y());}
              );
    points.resize(std::unique(points.begin(), points.end())- points.begin());
    for(auto &p : points){
        Item::drawPixel(p.x(), p.y());
    }
}

void Ellipse::drawPixel(int x, int y)
{
    points.push_back({x, y});
}

QRectF Ellipse::boundingRect() const
{
    const int thickness = this->scene->getThickness();
    QPoint topLeft = toScenePos(QPoint(x, y));
    topLeft.setX(topLeft.x() - thickness * xRadius - thickness);
    topLeft.setY(topLeft.y() - thickness * yRadius - thickness);
    return QRectF(topLeft, QSize(xRadius * thickness * 2 + thickness * 2, yRadius * thickness * 2 + thickness * 2));
}

void Ellipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
      painter->fillPath(path, brush);
}
