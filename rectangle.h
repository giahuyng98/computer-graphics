#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "item.h"
#include "line.h"
#include <Qt>

class Scene;

class Rectangle : public Item
{
public:        
    Rectangle(const QPoint &topLeft, const QPoint &topRight,
              const QPoint &bottomLeft, const QPoint &bottomRight,
              Scene *scene, QGraphicsItem *parent = nullptr);
    Rectangle(const QPoint &topLeft, const QSize &size,
              Scene *scene, QGraphicsItem *parent = nullptr);

    Type getType() const override;

//    vector<vector<int>> getPoint();
//    void setPoint(const vector<vector<int>> &mat);

    void reDraw();    

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void drawRectangel();

private:
    QPoint topLeft, topRight, bottomLeft, bottomRight;
};

#endif // RECTANGLE_H
