#ifndef CIRCLE_H
#define CIRCLE_H

#include "item.h"

class Circle : public Item
{
public:
    Circle(int x, int y, int r);

protected:
    QRectF boundingRect() const override;
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
//    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QStringList getInfo() const override;
private:
    int x, y, r;
};

#endif // CIRCLE_H
