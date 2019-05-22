#ifndef SCENE_H
#define SCENE_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QTreeWidgetItem>
#include <vector>
#include <cmath>
#include "items.h"
#include "line.h"
#include "rectangle.h"
#include "lineinfo.h"
#include "rectinfo.h"
#include "affine.h"
#include "circle.h"
#include "ellipse.h"
#include "circleinfo.h"
#include "ellipseinfo.h"

class Window;


class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QWidget *parent = nullptr);
//    void setTree(QTreeWidget *tree);
    int getOffx() const;
    int getOffy() const;
    int getThickness() const;
    QPoint toUserCoordinate(const QPointF &scenePos) const;

    void setWindow(Window *value);
    void changeColor(const QColor &color);
    void deleteItem();
    void clearAll();

    void doTranslation();

    void doRotation();

    void doScaling();

    RectInfo *getRectInfo() const;

    LineInfo *getLineInfo() const;

    CircleInfo *getCircleInfo() const;

    EllipseInfo *getEllipseInfo() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void drawBackground(QPainter *painter, const QRectF &rect) override;

//    void resizeEvent(QResizeEvent *event) override;
//    void paintEvent(QPaintEvent *event) override;

private:
    Affine affine;
    int lenx, leny;
    int offx, offy;
    int thickness = 5;
    bool isDrawing = false;
    Line *tmpLine = nullptr;
    Rectangle *tmpRectange = nullptr;
    Circle *tmpCircle = nullptr;
    Ellipse *tmpEllipse = nullptr;
    LineInfo *lineInfo;
    RectInfo *rectInfo;
    CircleInfo *circleInfo;
    EllipseInfo *ellipseInfo;
    std::vector<QPoint> points;
    Window *window;

//    QTreeWidget *tree;
};

#endif // SCENE_H
