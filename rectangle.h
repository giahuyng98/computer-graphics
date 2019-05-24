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
    Type getType() const override;

    vector<vector<int>> getPoint();
    void setPoint(const vector<vector<int>> &mat);

    QPoint getPos() const;
    void setPos(const QPoint &value);

    QSize getSize() const;
    void setSize(const QSize &value);

    void reDraw();
    void fill(const QColor &color);

protected:
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void drawRectanlge();
private:
    QPoint pos;
    QSize size;
    QPainterPath fillPath;
    QBrush fillColor;
};

#endif // RECTANGLE_H
