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
    QColor getFillColor() const override;
    void reDraw() override;

    QPoint getTopLeft() const;
    void setTopLeft(const QPoint &value);

    QPoint getTopRight() const;
    void setTopRight(const QPoint &value);

    QPoint getBottomLeft() const;
    void setBottomLeft(const QPoint &value);

    QPoint getBottomRight() const;
    void setBottomRight(const QPoint &value);

    int getWidth() const;
    int getHeight() const;

    QPoint getCenter() const;

    void setFillColor(const QColor &value);

protected:
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void drawRectangle();
    void fillRectangle();

private:
    QPoint topLeft, topRight, bottomLeft, bottomRight;
    QPainterPath fillPath;
    QColor fillColor = Qt::color0;
};

#endif // RECTANGLE_H
