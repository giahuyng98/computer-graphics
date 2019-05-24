#ifndef SCENE_H
#define SCENE_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <vector>
#include <cmath>
#include "items.h"
#include "line.h"
#include "rectangle.h"
#include "rectinfo.h"
#include "affine.h"
#include "circle.h"
#include "ellipse.h"

class Window;

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QWidget *parent = nullptr);

    int getOffx() const;

    int getOffy() const;

    int getThickness() const;

    void setThickness(int value);

    QPoint toScenePos(const QPoint &userPos) const;

    QPoint toUserCoordinate(const QPointF &scenePos) const;

    void setWindow(Window *value);

    void translateItem(Item *item, int dx, int dy);

    void rotateItem(Item *item, int x, int y, int angle);

    void scaleItem(Item *item, float sx, float sy);

    void reflectItem(Item *item, int x, int y);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;

    Affine affine;
    int lenx, leny;
    int offx, offy;
    int thickness = 5;    
    Window *window;    
};

#endif // SCENE_H
