#ifndef SPHERE_H
#define SPHERE_H

#include <QWidget>
#include <QGraphicsItem>
#include <QDebug>
#include "apidrawer.h"

class Scene3D;

class Sphere : public QGraphicsItem
{
public:
    Sphere(int x, int y, int z, int r, Scene3D *scene, QGraphicsItem *parent = nullptr);

protected:
    QPainterPath shape() const override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void drawPixel(const QPoint &point);
    void drawSphere();    

private:
    int x, y, z, r;
    QBrush brush = QBrush(Qt::black);
    QPainterPath path;
    Scene3D *scene;
};

#endif // SPHERE_H
