#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "item.h"
class Scene;

class Ellipse : public Item
{
public:
    Ellipse(int x, int y, int xRadius, int yRadius, Scene *scene, QGraphicsItem *parent = nullptr);
protected:
    void drawEllipse(int xs, int ys, int x, int y);
    void ellipseMidpoint(int xs1, int ys1, int rx, int ry);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    int x, y, xRadius, yRadius;
};

#endif // ELLIPSE_H
