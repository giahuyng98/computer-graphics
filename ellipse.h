#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "item.h"
class Scene;

class Ellipse : public Item
{
public:
    Ellipse(int x, int y, int xRadius, int yRadius, Scene *scene, QGraphicsItem *parent = nullptr);
protected:
    void




    QRectF boundingRect() const override;
private:
    int x, y, xRadius, yRadius;
};

#endif // ELLIPSE_H
