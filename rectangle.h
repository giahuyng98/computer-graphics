#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "item.h"
#include "line.h"
#include <Qt>

class Scene;

class Rectangle : public Item
{
public:    
    Rectangle(const QPoint &pos, const QSize &size, Scene *scene, QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
//    QStringList getInfo() const override;
    QPoint getPos() const;
    void setPos(const QPoint &value);

    QSize getSize() const;
    void setSize(const QSize &value);

    void reDraw();
    Type getType() const override;

private:
    Line line1, line2, line3, line4;
    QPoint pos;
    QSize size;
};

#endif // RECTANGLE_H
