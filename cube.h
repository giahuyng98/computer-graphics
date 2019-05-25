#ifndef CUBE_H
#define CUBE_H

#include <QWidget>
#include <QGraphicsItem>
#include <QDebug>
#include "apidrawer.h"

class Scene3D;

class Cube : public QGraphicsItem
{
public:
    Cube(int x, int y, int z, int width, int height, int length, Scene3D *scene, QGraphicsItem *parent = nullptr);

protected:
    QPainterPath shape() const override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void drawPixel(const QPoint &point);
    void drawCube();    

private:
    int x, y, z, width, height, length;
    QBrush brush = QBrush(Qt::black);
    QPainterPath path;
    Scene3D *scene;
};

#endif // CUBE_H
