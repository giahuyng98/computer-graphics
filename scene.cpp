#include "scene.h"
#include "item.h"
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QTextItem>
#include <QPoint>
#include "window.h"

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

void Scene::setWindow(Window *value){
    this->window = value;
}

void Scene::changeColor(const QColor &color)
{
    for(auto &item : this->selectedItems()){
        static_cast<Item*>(item)->setBrush(QBrush(color));
    }
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

QPoint Scene::toUserCoordinate(const QPointF &scenePos) const
{
    return QPoint(static_cast<int>(scenePos.x()) / thickness - offx, offy - static_cast<int>(scenePos.y()) / thickness);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);
    if (mouseEvent->button() == Qt::LeftButton){
        Item *selectedItem = static_cast<Item*>(this->itemAt(mouseEvent->scenePos(), QTransform()));
        if (selectedItem){
            selectedItem->setSelected(true);
            window->showInfo(selectedItem->getInfo());
            //TODO: show info
            return;
        }

        isDrawing = true;
        points.emplace_back(toUserCoordinate(mouseEvent->scenePos()));
        switch (window->getCurrentShape()){
        case Window::ShapeKind::NORMAL_LINE :
            points.emplace_back(toUserCoordinate(mouseEvent->scenePos()));
            tmpLine = new Line(points.front(), points.back(), this);
            addItem(tmpLine);
            break;

        case Window::ShapeKind::RECTANGLE :
            if (points.size() == 2){
                Rectangle *rec = new Rectangle(points.front(), QSize(std::abs(points.back().x() - points.front().x()),
                                                                             std::abs(points.back().y() - points.front().y())), this);
                addItem(rec);

                points.clear();
            } else {
            }
            break;
        case Window::ShapeKind::CIRCLE :
            break;
        case Window::ShapeKind::ELIP :
            break;
        }

    }    
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    isDrawing = false;
    points.clear();
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (isDrawing && window->getCurrentShape() == Window::ShapeKind::NORMAL_LINE){
        points.pop_back();
        points.emplace_back(toUserCoordinate(mouseEvent->scenePos()));
        removeItem(tmpLine);
        delete tmpLine;
        this->addItem(tmpLine = new Line(points.front(), points.back(), this));
        tmpLine->setSelected(true);
        tmpLine->update();
        window->showInfo(tmpLine->getInfo());
    }

    QGraphicsScene::mouseMoveEvent(mouseEvent);
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

