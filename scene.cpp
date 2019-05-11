#include "scene.h"
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QTextItem>

Scene::Scene(QWidget *parent) : QGraphicsScene (parent)
{
    const int WIDTH = 1200;
    const int HEIGH = 600;    

    this->setSceneRect(0, 0, WIDTH, HEIGH);
    lenx = static_cast<int>(width()) / thickness;
    leny = static_cast<int>(height()) / thickness;

    offx = lenx / 2;
    offy = leny / 2;

}

void Scene::setTree(QTreeWidget *tree)
{
    this->tree = tree;
}

int Scene::getOffx() const
{
    return offx;
}

int Scene::getOffy() const
{
    return offy;
}

int Scene::getThickness() const
{
    return thickness;
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton){
        Item *item = static_cast<Item*>(itemAt(mouseEvent->scenePos(), QTransform()));
        if (item){
            tree->takeTopLevelItem(tree->indexOfTopLevelItem(static_cast<QTreeWidgetItem*>(item)));
            this->removeItem(static_cast<QGraphicsItem*>(item));
//            QGraphicsScene::mousePressEvent(mouseEvent);
        } else {
            int x = static_cast<int>(mouseEvent->scenePos().x()) / thickness - offx;
            int y = offy - static_cast<int>(mouseEvent->scenePos().y()) / thickness;

            Line *line = new Line(0, 0, x, y);
            tree->addTopLevelItem(static_cast<QTreeWidgetItem*>(line));
            addItem(line);
        }
    }

}

void Scene::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);
    int halfHeight = static_cast<int>(this->height()) / 2;
    int halfWidth = static_cast<int>(this->width()) / 2;
    const int halfThick = thickness / 2; //make it center

    // Draw ox and oy
    painter->setPen(QPen(QBrush(Qt::black), 1));
    painter->setOpacity(0.6);
    painter->drawLine(0, halfHeight + halfThick, static_cast<int>(this->width()), halfHeight + halfThick);
    painter->drawLine(halfWidth + halfThick, 0, halfWidth + halfThick, static_cast<int>(this->height()));

    const int space = thickness * 5; //line spacing
    painter->setOpacity(0.25);


    // Draw vertical line
    for(int xJump = halfThick; xJump < this->width(); xJump += space){
        painter->drawLine(xJump, 0, xJump, static_cast<int>(this->height()));        
    }

    // Draw horizontal line
    for(int yJump = halfThick; yJump < this->height(); yJump += space){
        painter->drawLine(0, yJump, static_cast<int>(this->width()), yJump);
    }

    // Draw grid
    painter->setOpacity(0.08);
    for(int xJump = halfThick; xJump < this->width(); xJump += thickness){
        painter->drawLine(xJump, 0, xJump, static_cast<int>(this->height()));
    }
    for(int yJump = halfThick; yJump < this->height(); yJump += thickness){
        painter->drawLine(0, yJump, static_cast<int>(this->width()), yJump);
    }

    // Draw arrow
    painter->setOpacity(1.0);
    halfWidth += halfThick;
    halfHeight += halfThick;
    painter->drawLine(static_cast<int>(this->width()) - 5, halfHeight - 5, static_cast<int>(this->width()), halfHeight);
    painter->drawLine(static_cast<int>(this->width()) - 5, halfHeight + 5, static_cast<int>(this->width()), halfHeight);

    painter->drawLine(halfWidth - 5, 5, halfWidth, 0);
    painter->drawLine(halfWidth + 5, 5, halfWidth, 0);
}

