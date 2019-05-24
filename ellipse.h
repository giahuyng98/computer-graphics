#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "item.h"
#include <vector>
using std::vector;

class Scene;

class Ellipse : public Item
{
public:
    Ellipse(int x, int y, int xRadius, int yRadius, Scene *scene, QGraphicsItem *parent = nullptr);
    Type getType() const override;

    void reDraw();
    void fill(const QColor &color);

    QPoint getPoint() const;
    void setPoint(const QPoint &point);

    int getX() const;
    void setX(int value);

    int getY() const;
    void setY(int value);

    int getXRadius() const;
    void setXRadius(int value);

    int getYRadius() const;
    void setYRadius(int value);

protected:
    void drawEllipse();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;    

private:
    QPainterPath fillPath;
    QColor fillColor = Qt::color0;
    int x, y, xRadius, yRadius;    
};


#endif // ELLIPSE_H
