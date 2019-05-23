#ifndef CUBE_H
#define CUBE_H

#include <QWidget>
#include <QGraphicsItem>
#include <QDebug>

class Scene3D;

class Cube : public QGraphicsItem
{
public:
    Cube(int x, int y, int z, int width, int height, int length, Scene3D *scene, QGraphicsItem *parent = nullptr);

protected:
    QPainterPath shape() const override;
    QRectF boundingRect() const override;
    void drawPixel(int x, int y);
    QPoint toScenePos(const QPoint &userPos) const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void drawLine(int x1, int y1, int x2, int y2);
    void drawLineLow(int x1, int y1, int x2, int y2);
    void drawLineHigh(int x1, int y1, int x2, int y2);
private:
    int x, y, z, width, height, length;
    QBrush brush = QBrush(Qt::black);
    QPainterPath path;
    Scene3D *scene;
};

#endif // CUBE_H
