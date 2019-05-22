#include "ellipse.h"
#include "scene.h"

Ellipse::Ellipse(int x, int y, int xRadius, int yRadius, Scene *scene, QGraphicsItem *parent)
:Item(scene, parent), x(x), y(y), xRadius(xRadius), yRadius(yRadius)
{

}

void Ellipse::drawEllipse(int xs, int ys, int x, int y)
{
    drawPixel(xs + x, ys + y);
    drawPixel(xs - x, ys - y);
    drawPixel(xs + x, ys - y);
    drawPixel(xs - x, ys + y);
}

void Ellipse::ellipseMidpoint(int xs1, int ys1, int rx, int ry)
{
    int tx, ty;
    float d1, d2, dx, dy;
    tx = 0;
    ty = ry;
    d1 = pow(ry, 2) - (pow(rx,2) * ry) + (0.25 * pow(rx,2));
    dx = 2 * pow(ry,2) * tx;
    dy = 2 * pow(rx,2) * ty;

}

QRectF Ellipse::boundingRect() const
{

}
