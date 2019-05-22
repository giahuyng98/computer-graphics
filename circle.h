#ifndef CIRCLE_H
#define CIRCLE_H

#include "item.h"

class Scene;

class Circle : public Item
{
public:
    Circle(int x, int y, int r,Scene *scene, QGraphicsItem *parent = nullptr);

    int getX() const;
    void setX(int value);

    int getY() const;
    void setY(int value);

    int getR() const;
    void setR(int value);

protected:
    void drawCircle(int xc, int yc, int x, int y);
    void circleBres();
    QRectF boundingRect() const override;
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
//    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    int x, y, r;
};

#endif // CIRCLE_H
