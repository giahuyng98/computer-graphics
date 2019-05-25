#ifndef CYLINDER_H
#define CYLINDER_H
#include <QWidget>
#include <QGraphicsItem>
#include <QDebug>
#include "apidrawer.h"
class Scene3D;
class Cylinder :  public QGraphicsItem
{
public:
    explicit Cylinder(int cx, int cy, int cz, int r, int h, Scene3D *scene, QGraphicsItem *parent = nullptr);
protected:
    QPainterPath shape() const override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void drawPixel(const QPoint &point);
    void drawCylinder();

private:
    int cx, cy, cz, r, h;
    QBrush brush = QBrush(Qt::black);
    QPainterPath path;
    Scene3D *scene;
};

#endif // CYLINDER_H


