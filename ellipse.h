//#ifndef ELLIPSE_H
//#define ELLIPSE_H

//#include "item.h"
//class Scene;

<<<<<<< HEAD
//class Ellipse : public Item
//{
//public:
//    Ellipse(int x, int y, int xRadius, int yRadius, Scene *scene, QGraphicsItem *parent = nullptr);
//protected:
//    void




//    QRectF boundingRect() const override;
//private:
//    int x, y, xRadius, yRadius;
//};
=======
class Ellipse : public Item
{
public:
    Ellipse(int x, int y, int xRadius, int yRadius, Scene *scene, QGraphicsItem *parent = nullptr);
protected:
    void drawEllipse(int xs, int ys, int x, int y);
    void ellipseMidpoint(int xs1, int ys1, int rx, int ry);
    void drawPixel(int x, int y);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    int x, y, xRadius, yRadius;
    std::vector<QPoint> points;
};
>>>>>>> bbe8505b388e143ecedcaa2646eaa4da5f667101

//#endif // ELLIPSE_H
