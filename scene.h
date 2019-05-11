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
#include <deque>
#include "items.h"
#include "line.h"


class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QWidget *parent = nullptr);
    void setTree(QTreeWidget *tree);
    int getOffx() const;
    int getOffy() const;
    int getThickness() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void drawBackground(QPainter *painter, const QRectF &rect) override;

//    void resizeEvent(QResizeEvent *event) override;
//    void paintEvent(QPaintEvent *event) override;

private:
    int lenx, leny;
    int offx, offy;
    int thickness = 5;

    QTreeWidget *tree;    
};

#endif // SCENE_H
