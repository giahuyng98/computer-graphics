#ifndef CIRCLE_H
#define CIRCLE_H

#include "item.h"
#include <vector>
using std::vector;

class Scene;

class Circle : public Item
{
public:
    Circle(int x, int y, int r, Scene *scene, QGraphicsItem *parent = nullptr);
    Type getType() const override;
    int getX() const;
    void setX(int value);

    int getY() const;
    void setY(int value);

    int getR() const;
    void setR(int value);

    QPoint getPoint() const;
    void setPoint(const QPoint &point);

    void reDraw();
    void fill(const QColor &color);

protected:    
    void drawCircle();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QPainterPath fillPath;
    QColor fillColor = Qt::color0;
    int x, y, r;
};

#endif // CIRCLE_H
