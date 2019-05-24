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

    int getOffx() const;

    int getOffy() const;

    int getThickness() const;

    QPoint toUserCoordinate(const QPointF &scenePos) const;

    void setWindow(Window *value);

    void doChangeColor(const QColor &color);

    void doFillColor(const QColor &color);

    void deleteItem();

    void clearAll();

    void doTranslation();

    void translateItem(Item *item, int dx, int dy);

    void doRotation();

    void rotateItem(Item *item, int x, int y, int angle);

    void doScaling();

    void scaleItem(Item *item, float sx, float sy);

    void doReflection();

    void reflectItem(Item *item, int x, int y);

    void play(int delay);

    void updateInfo(Item *item);

    RectInfo *getRectInfo() const;

    LineInfo *getLineInfo() const;

    CircleInfo *getCircleInfo() const;

    EllipseInfo *getEllipseInfo() const;

    void setThickness(int value);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void drawBackground(QPainter *painter, const QRectF &rect) override;

//    void resizeEvent(QResizeEvent *event) override;
//    void paintEvent(QPaintEvent *event) override;

private slots:
    void doAnimation();

private:
    QTimer *timer;

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
};

#endif // SCENE_H
