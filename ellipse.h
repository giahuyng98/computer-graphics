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
    QColor getFillColor() const override;
    void reDraw();

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

    void setFillColor(const QColor &value);

protected:
    void fillEllipse();
    void drawEllipse();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;    

private:
    QPainterPath fillPath;
    QColor fillColor = QColor::Spec::Invalid;
    int x, y, xRadius, yRadius;    
};


#endif // ELLIPSE_H
