#include "circle.h"
#include "scene.h"
#include <algorithm>
Circle::Circle(int x, int y, int r, Scene *scene, QGraphicsItem *parent)
:Item(scene, parent), x(x), y(y), r(r)
{
    circleBres();
}

Item::Type Circle::getType() const
{
    return Type::CIRCLE;
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
    path = QPainterPath();
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
    topLeft.setX(topLeft.x() - len - thickness);
    topLeft.setY(topLeft.y() - len - thickness);
    return QRectF(topLeft, QSize(len * 2 + thickness * 3, len * 2 + thickness * 3));
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

vector<vector<int> > Circle::getPoint()
{
    return {
        {x, y, 1}
    };
}

void Circle::setPoint(const vector<vector<int> > &mat)
{
    x = mat[0][0];
    y = mat[0][1];
}

void Circle::reDraw()
{
    circleBres();
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
