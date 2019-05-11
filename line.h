#ifndef LINE_H
#define LINE_H

#include <QWidget>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include "item.h"

class Line : public Item
{
public:
    Line();
    Line(int x1, int y1, int x2, int y2);

protected:
    QRectF boundingRect() const override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;    
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void drawLine();
    void drawLineLow(int x1, int y1, int x2, int y2);
    void drawLineHigh(int x1, int y1, int x2, int y2);
private:
    int x1, y1, x2, y2;
};

#endif // LINE_H
