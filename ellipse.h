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

    vector<vector<int>> getPoint();
    void setPoint(const vector<vector<int>> &mat);
    int getX() const;
    void setX(int value);

    int getY() const;
    void setY(int value);

    int getXRadius() const;
    void setXRadius(int value);

    int getYRadius() const;
    void setYRadius(int value);

protected:
    void drawEllipse(int xs, int ys, int x, int y);
    void ellipseMidpoint(int xs1, int ys1, int rx, int ry);
    void drawPixel(int x, int y);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;    

private:
    int x, y, xRadius, yRadius;
    std::vector<QPoint> points;
};


#endif // ELLIPSE_H
