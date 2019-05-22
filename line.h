#ifndef LINE_H
#define LINE_H

#include <QWidget>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPoint>
#include <Qt>
#include "item.h"
#include <vector>
using std::vector;

class Scene;

class Rectangle;
class LineInfo;
class Circle;
class Line : public Item
{
public:
    Line(Scene *scene, QGraphicsItem *parent = nullptr);
    Line(int x1, int y1, int x2, int y2, Scene *scene, QGraphicsItem *parent = nullptr);
    Line(const QPoint &from, const QPoint &to, Scene *scene, QGraphicsItem *parent = nullptr);
    Type getType() const override;
//    QStringList getInfo() const override;
//    const Line& operator=(const Line &l);

    vector<vector<int>> getPoint1();
    vector<vector<int>> getPoint2();
    void setPoint1(const vector<vector<int>> &mat);
    void setPoint2(const vector<vector<int>> &mat);

    int getX1() const;
    void setX1(int value);

    int getY1() const;
    void setY1(int value);

    int getX2() const;
    void setX2(int value);

    int getY2() const;
    void setY2(int value);

    void reDraw();

protected:
    QRectF boundingRect() const override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;        

    void drawLine();
    void drawLineLow(int x1, int y1, int x2, int y2);
    void drawLineHigh(int x1, int y1, int x2, int y2);
private:
    int x1, y1, x2, y2;
//    friend class Rectangle;
//    friend class LineInfo;
};

#endif // LINE_H
