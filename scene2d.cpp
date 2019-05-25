#include "scene2d.h"
#include "item.h"
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QTextItem>
#include <QPoint>
#include "window.h"

Scene2D::Scene2D(QWidget *parent) : Scene(parent)
{
    lineInfo = new LineInfo();
    rectInfo = new RectInfo();
    circleInfo = new CircleInfo();
    ellipseInfo = new EllipseInfo();
}

void Scene2D::toTextFile()
{
    QFile file("test.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream stream(&file);
        int cnt = 0;
        for(auto &item : items()){
            stream << "ADD ";
            switch (static_cast<Item*>(item)->getType()) {
            case Item::Type::LINE:
            {
                Line *line = static_cast<Line*>(item);
                stream << ++cnt << " LINE " << line->getX1() << " "
                       << line->getY1() << " "<< line->getX2() << " "
                       << line->getY2() << " " << line->getColor().name();
                break;
            }
            case Item::Type::RECT:
            {
                Rectangle *rect = static_cast<Rectangle*>(item);
                stream << ++cnt << " RECT " << rect->getTopLeft().x() << " "
                       << rect->getTopLeft().y() << " "
                       << rect->getWidth() << " " << rect->getHeight() << " "
                       << rect->getColor().name() << " " << rect->getFillColor().name();

                break;
            }
            case Item::Type::CIRCLE:
            {
                Circle *circle = static_cast<Circle*>(item);
                stream << ++cnt << " CIRCLE " << circle->getX() << " "
                       << circle->getY() << " " << circle->getR() << " "
                       << circle->getColor().name() << " " << circle->getFillColor().name();
                break;
            }
            case Item::Type::ELIP:
            {
                Ellipse *ellipse = static_cast<Ellipse*>(item);
                stream << ++cnt << " ELLIPSE " << ellipse->getX() << " "
                       << ellipse->getY() << " " << ellipse->getXRadius() << " "
                       << ellipse->getYRadius() << " "
                       << ellipse->getColor().name() << " " << ellipse->getFillColor().name();
                break;
            }
            default:
                break;
            }
            stream << "\n";
        }
        stream << "STOP\n";
    }
}

void Scene2D::doChangeColor(const QColor &color)
{
    for(auto &item : this->selectedItems()){
        changeColor(static_cast<Item*>(item), color);
    }
}

void Scene2D::doFillColor(const QColor &color)
{
    if (this->selectedItems().isEmpty()) return;
    Item *item = static_cast<Item*>(this->selectedItems().first());
    changeFillColor(item, color);
}

void Scene2D::deleteItem()
{
    if (!this->selectedItems().isEmpty()){
        Item *item = static_cast<Item*>(this->selectedItems().first());
        delete item;
        //        removeItem(item);
    }

    if (!this->items().isEmpty()) {
        Item *item = static_cast<Item*>(this->items().first());
        item->setSelected(true);
        window->setEnableFillButton(item->getType() != Item::Type::LINE);
        switch (item->getType()) {
        case Item::Type::LINE:
            lineInfo->setLine(static_cast<Line*>(item));
            window->setShapeKind(Window::ShapeKind::NORMAL_LINE);
            break;
        case Item::Type::RECT:
            rectInfo->setRect(static_cast<Rectangle*>(item));
            window->setShapeKind(Window::ShapeKind::RECTANGLE);
            break;
        case Item::Type::CIRCLE:
            circleInfo->setCircle(static_cast<Circle*>(item));
            window->setShapeKind(Window::ShapeKind::CIRCLE);
            break;
        case Item::Type::ELIP:
            ellipseInfo->setEllipse(static_cast<Ellipse*>(item));
            window->setShapeKind(Window::ShapeKind::ELIP);
            break;
        default:
            break;
        }
    } else {
        lineInfo->setLine(nullptr);
        rectInfo->setRect(nullptr);
        circleInfo->setCircle(nullptr);
        ellipseInfo->setEllipse(nullptr);
    }

}

void Scene2D::clearAll()
{    
    this->clear();
    lineInfo->setLine(nullptr);
    rectInfo->setRect(nullptr);
    circleInfo->setCircle(nullptr);
    ellipseInfo->setEllipse(nullptr);
}

void Scene2D::doTranslation()
{
    if (selectedItems().isEmpty()) return;
    Item *selectedItem = static_cast<Item*>(selectedItems().first());
    if (selectedItem){
        translateItem(selectedItem, window->getDxTrans(), window->getDyTrans());
        updateInfo(selectedItem);
    }
}

void Scene2D::doRotation()
{
    if (selectedItems().isEmpty()) return;
    Item *selectedItem = static_cast<Item*>(selectedItems().first());
    if (selectedItem){
        rotateItem(selectedItem, window->getXRotate(), window->getYRotate(), window->getAngleRotate());
        updateInfo(selectedItem);
    }
}

void Scene2D::doScaling()
{
    if (selectedItems().isEmpty()) return;
    Item *selectedItem = static_cast<Item*>(selectedItems().first());
    if (selectedItem){
        scaleItem(selectedItem, window->getSXScale(), window->getSYScale());
        updateInfo(selectedItem);
    }
}

void Scene2D::doReflection()
{
    if (selectedItems().isEmpty()) return;
    Item *selectedItem = static_cast<Item*>(selectedItems().first());
    if (selectedItem){
        reflectItem(selectedItem, window->getXReflection(), window->getYReflection());
        updateInfo(selectedItem);
    }
}

void Scene2D::updateInfo(Item *item)
{
    switch (item->getType()) {
    case Item::Type::LINE:
        lineInfo->setLine(static_cast<Line*>(item));
        break;
    case Item::Type::RECT:
        rectInfo->setRect(static_cast<Rectangle*>(item));
        break;
    case Item::Type::CIRCLE:
        circleInfo->setCircle(static_cast<Circle*>(item));
        break;
    case Item::Type::ELIP:
        ellipseInfo->setEllipse(static_cast<Ellipse*>(item));
        break;
    default:
        break;
    }
}

void Scene2D::setThickness(int value)
{
    Scene::setThickness(value);
    for(auto &item : this->items()){
        switch (static_cast<Item*>(item)->getType()) {
        case Item::Type::LINE:
            static_cast<Line*>(item)->reDraw();
            break;
        case Item::Type::RECT:
            static_cast<Rectangle*>(item)->reDraw();
            break;
        case Item::Type::CIRCLE:
            static_cast<Circle*>(item)->reDraw();
            break;
        case Item::Type::ELIP:
            static_cast<Ellipse*>(item)->reDraw();
            break;
        default: break;
        }
    }
    update();
}

void Scene2D::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);
    if (mouseEvent->button() == Qt::LeftButton){
        this->clearSelection();
        Item *selectedItem = static_cast<Item*>(this->itemAt(mouseEvent->scenePos(), QTransform()));

        if (selectedItem){

            switch (selectedItem->getType()) {
            case Item::Type::LINE:
                lineInfo->setLine(static_cast<Line*>(selectedItem));
                window->setShapeKind(Window::ShapeKind::NORMAL_LINE);
                break;
            case Item::Type::RECT:
                rectInfo->setRect(static_cast<Rectangle*>(selectedItem));
                window->setShapeKind(Window::ShapeKind::RECTANGLE);
                break;
            case Item::Type::CIRCLE:
                circleInfo->setCircle(static_cast<Circle*>(selectedItem));
                window->setShapeKind(Window::ShapeKind::CIRCLE);
                break;
            case Item::Type::ELIP:
                ellipseInfo->setEllipse(static_cast<Ellipse*>(selectedItem));
                window->setShapeKind(Window::ShapeKind::ELIP);
                break;
            default:
                break;
            }
            selectedItem->setSelected(true);
            window->setEnableFillButton(selectedItem->getType() != Item::Type::LINE);

            return;
        }

        isDrawing = true;
        points.emplace_back(toUserCoordinate(mouseEvent->scenePos()));
        window->setEnableFillButton(window->getCurrentShape() != Window::NORMAL_LINE);

        switch (window->getCurrentShape()){
        case Window::ShapeKind::NORMAL_LINE :
            points.emplace_back(toUserCoordinate(mouseEvent->scenePos()));
            tmpLine = new Line(points.front(), points.back(), this);
            addItem(tmpLine);
            lineInfo->setLine(tmpLine);
            window->setShapeKind(Window::ShapeKind::NORMAL_LINE);
            break;

        case Window::ShapeKind::RECTANGLE :
            points.emplace_back(toUserCoordinate(mouseEvent->scenePos()));
            tmpRectange = new Rectangle(points.front(), QSize(std::abs(points.back().x() - points.front().x()),
                                                              std::abs(points.back().y() - points.front().y())), this);
            addItem(tmpRectange);
            rectInfo->setRect(tmpRectange);
            window->setShapeKind(Window::ShapeKind::RECTANGLE);
            break;
        case Window::ShapeKind::CIRCLE :
        {
            points.emplace_back(toUserCoordinate(mouseEvent->scenePos()));

            tmpCircle = new Circle(points.front().x(), points.front().y(), Drawer::dist(points.front(), points.back()), this);
            addItem(tmpCircle);
            circleInfo->setCircle(tmpCircle);
            window->setShapeKind(Window::ShapeKind::CIRCLE);
            break;
        }
        case Window::ShapeKind::ELIP :
            points.emplace_back(toUserCoordinate(mouseEvent->scenePos()));
            tmpEllipse = new Ellipse(points.front().x(), points.front().y(),
                                     std::abs(points.back().x() - points.front().x()),
                                     std::abs(points.back().y() - points.front().y()), this);
            addItem(tmpEllipse);
            ellipseInfo->setEllipse(tmpEllipse);
            window->setShapeKind(Window::ShapeKind::ELIP);
            break;
        }

    }
}

void Scene2D::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    isDrawing = false;
    points.clear();
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void Scene2D::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (isDrawing){

        switch (window->getCurrentShape()) {
        case  Window::ShapeKind::NORMAL_LINE:
            points.pop_back();
            points.emplace_back(toUserCoordinate(mouseEvent->scenePos()));
            removeItem(tmpLine);
            delete tmpLine;
            this->addItem(tmpLine = new Line(points.front(), points.back(), this));
            tmpLine->setSelected(true);
            tmpLine->update();
            lineInfo->setLine(tmpLine);
            break;
        case Window::ShapeKind::RECTANGLE:

            points.pop_back();
            points.emplace_back(toUserCoordinate(mouseEvent->scenePos()));
            removeItem(tmpRectange);
            delete tmpRectange;
            tmpRectange = new Rectangle(QPoint(std::min(points.front().x(), points.back().x()), std::max(points.front().y(), points.back().y())),
                                        QSize(std::abs(points.back().x() - points.front().x()),
                                              std::abs(points.back().y() - points.front().y())), this);

            tmpRectange->setSelected(true);
            tmpRectange->update();
            rectInfo->setRect(tmpRectange);
            this->addItem(tmpRectange);

            break;
        case Window::ShapeKind::CIRCLE:
            points.pop_back();
            points.emplace_back(toUserCoordinate(mouseEvent->scenePos()));
            removeItem(tmpCircle);
            delete tmpCircle;
            tmpCircle = new Circle(points.front().x(), points.front().y(), Drawer::dist(points.front(), points.back()), this);
            tmpCircle->setSelected(true);
            tmpCircle->update();
            circleInfo->setCircle(tmpCircle);
            this->addItem(tmpCircle);

            break;
        case Window::ShapeKind::ELIP:
            points.pop_back();
            points.emplace_back(toUserCoordinate(mouseEvent->scenePos()));
            removeItem(tmpEllipse);
            delete tmpEllipse;
            tmpEllipse = new Ellipse(points.front().x(), points.front().y(),
                                     std::abs(points.back().x() - points.front().x()),
                                     std::abs(points.back().y() - points.front().y()), this);
            tmpEllipse->setSelected(true);
            tmpEllipse->update();
            ellipseInfo->setEllipse(tmpEllipse);
            this->addItem(tmpEllipse);

            break;
        }

    }

    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

EllipseInfo *Scene2D::getEllipseInfo() const
{
    return ellipseInfo;
}

CircleInfo *Scene2D::getCircleInfo() const
{
    return circleInfo;
}

LineInfo *Scene2D::getLineInfo() const
{
    return lineInfo;
}

RectInfo *Scene2D::getRectInfo() const
{
    return rectInfo;
}

