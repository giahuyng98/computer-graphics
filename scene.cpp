#include "scene.h"
#include "item.h"
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QTextItem>
#include <QPoint>
#include "window.h"
auto dist = [](const QPoint &p1, const QPoint &p2){
    return sqrt(pow(p1.x() - p2.x(),2) + pow(p1.y() - p2.y(), 2));
};
Scene::Scene(QWidget *parent) : QGraphicsScene (parent)
{
    const int WIDTH = 1200;
    const int HEIGH = 600;    

    this->setSceneRect(0, 0, WIDTH, HEIGH);
    lenx = static_cast<int>(width()) / thickness;
    leny = static_cast<int>(height()) / thickness;

    offx = lenx / 2;
    offy = leny / 2;

    lineInfo = new LineInfo();
    rectInfo = new RectInfo();
    circleInfo = new CircleInfo();
    ellipseInfo = new EllipseInfo();
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

void Scene::deleteItem()
{
    for(auto &item : this->selectedItems()){
        this->removeItem(item);
    }
    if (!this->items().isEmpty()) {
        this->items().first()->setSelected(true);
        switch (static_cast<Item*>(this->items().first())->getType()) {
        case Item::Type::LINE:
            lineInfo->setLine(static_cast<Line*>(this->items().first()));
            break;
        case Item::Type::RECT:
            rectInfo->setRect(static_cast<Rectangle*>(this->items().first()));
            break;
        case Item::Type::CIRCLE:
            circleInfo->setCircle(static_cast<Circle*>(this->items().first()));
            break;
        case Item::Type::ELIP:
            ellipseInfo->setEllipse(static_cast<Ellipse*>(this->items().first()));
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

void Scene::clearAll()
{
    for(auto &item : this->items()){
        this->removeItem(item);
    }
    lineInfo->setLine(nullptr);
    rectInfo->setRect(nullptr);
    circleInfo->setCircle(nullptr);
    ellipseInfo->setEllipse(nullptr);
}

void Scene::doTranslation()
{
    if (selectedItems().isEmpty()) return;
    Item *selectedItem = static_cast<Item*>(selectedItems().first());
    const int dx = window->getDxTrans();
    const int dy = window->getDyTrans();
    if (selectedItem){
        switch (selectedItem->getType()) {
        case Item::Type::LINE:
        {
            Line *line = static_cast<Line*>(selectedItem);
            line->setPoint1(affine.translate(line->getPoint1(), dx, dy));
            line->setPoint2(affine.translate(line->getPoint2(), dx, dy));
            line->reDraw();
            lineInfo->setLine(line);
            break;
        }
        case Item::Type::RECT:
        {
            Rectangle *rect = static_cast<Rectangle*>(selectedItem);
            rect->setPoint(affine.translate(rect->getPoint(), dx, dy));
            rect->reDraw();
            rectInfo->setRect(rect);
            break;
        }
        case Item::Type::CIRCLE:
        {
            Circle *circle = static_cast<Circle*>(selectedItem);
            circle->setPoint(affine.translate(circle->getPoint(), dx, dy));
            circle->reDraw();
            circleInfo->setCircle(circle);
            break;
        }
        case Item::Type::ELIP:
        {
            Ellipse *ellipse = static_cast<Ellipse*>(selectedItem);
            ellipse->setPoint(affine.translate(ellipse->getPoint(), dx, dy));
            ellipse->reDraw();
            ellipseInfo->setEllipse(ellipse);
            break;
        }
        default:
            break;
        }
    }
}

void Scene::doRotation()
{
    if (selectedItems().isEmpty()) return;
    Item *selectedItem = static_cast<Item*>(selectedItems().first());
    const int x = window->getXRotate();
    const int y = window->getYRotate();
    const int angle = window->getAngleRotate();
    vector<vector<int> > tam, temp;
    if (selectedItem){
        switch (selectedItem->getType()) {
        case Item::Type::LINE:
        {
            Line *line = static_cast<Line*>(selectedItem);
            line->setPoint1(affine.rotate(line->getPoint1(), x, y, angle));
            line->setPoint2(affine.rotate(line->getPoint2(), x, y, angle));
            line->reDraw();
            lineInfo->setLine(line);
            break;
        }
        case Item::Type::RECT:
        {
            Rectangle *rect = static_cast<Rectangle*>(selectedItem);
            rect->setPoint(affine.translate(rect->getPoint(), rect->getSize().width() / 2, -rect->getSize().height() / 2));
            rect->setPoint(affine.rotate(rect->getPoint(), x, y, angle));
            rect->setPoint(affine.translate(rect->getPoint(), -rect->getSize().width() / 2, rect->getSize().height() / 2));
            rect->reDraw();
            rectInfo->setRect(rect);
            break;
        }
        case Item::Type::CIRCLE:
        {

            Circle *circle = static_cast<Circle*>(selectedItem);
            circle->setPoint(affine.rotate(circle->getPoint(), x, y, angle));
            circle->reDraw();
            circleInfo->setCircle(circle);
            break;
        }
        case Item::Type::ELIP:
        {
            Ellipse *ellipse = static_cast<Ellipse*>(selectedItem);
            ellipse->setPoint(affine.rotate(ellipse->getPoint(), x, y, angle));
            ellipse->reDraw();
            ellipseInfo->setEllipse(ellipse);
            break;
        }
        default:
            break;
        }
    }

}

void Scene::doScaling()
{
    if (selectedItems().isEmpty()) return;
    Item *selectedItem = static_cast<Item*>(selectedItems().first());
    const int sx = window->getSXScale();
    const int sy = window->getSYScale();
    if (selectedItem){
        switch (selectedItem->getType()) {
        case Item::Type::LINE:
        {
            Line *line = static_cast<Line*>(selectedItem);
            line->setPoint1(affine.scale(line->getPoint1(), sx, sy));
            line->setPoint2(affine.scale(line->getPoint2(), sx, sy));
            line->reDraw();
            lineInfo->setLine(line);
            break;
        }
        case Item::Type::RECT:
        {

            Rectangle *rect = static_cast<Rectangle*>(selectedItem);
            rect->setPoint(affine.scale(rect->getPoint(), sx, sy));
            rect->reDraw();
            rectInfo->setRect(rect);
            break;
        }
        case Item::Type::CIRCLE:
        {

            Circle *circle = static_cast<Circle*>(selectedItem);
            circle->setPoint(affine.scale(circle->getPoint(), sx, sy));
            circle->reDraw();
            circleInfo->setCircle(circle);
            break;
        }
        case Item::Type::ELIP:
        {
            Ellipse *ellipse = static_cast<Ellipse*>(selectedItem);
            ellipse->setPoint(affine.scale(ellipse->getPoint(), sx, sy));
            ellipse->reDraw();
            ellipseInfo->setEllipse(ellipse);
            break;
        }
        default:
            break;
        }
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
            switch (selectedItem->getType()) {
            case Item::Type::LINE:
                lineInfo->setLine(static_cast<Line*>(selectedItem));
                break;
            case Item::Type::RECT:
                rectInfo->setRect(static_cast<Rectangle*>(selectedItem));
                break;
            case Item::Type::CIRCLE:
                circleInfo->setCircle(static_cast<Circle*>(selectedItem));
                break;
            case Item::Type::ELIP:
                ellipseInfo->setEllipse(static_cast<Ellipse*>(selectedItem));
                break;
            default:
                break;
            }
            selectedItem->setSelected(true);


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
            points.emplace_back(toUserCoordinate(mouseEvent->scenePos()));
            tmpRectange = new Rectangle(points.front(), QSize(std::abs(points.back().x() - points.front().x()),
                                                        std::abs(points.back().y() - points.front().y())), this);
            addItem(tmpRectange);

            break;
        case Window::ShapeKind::CIRCLE :
        {
            points.emplace_back(toUserCoordinate(mouseEvent->scenePos()));

            tmpCircle = new Circle(points.front().x(), points.front().y(), dist(points.front(), points.back()), this);
            addItem(tmpCircle);
            break;
        }
        case Window::ShapeKind::ELIP :
            points.emplace_back(toUserCoordinate(mouseEvent->scenePos()));
            tmpEllipse = new Ellipse(points.front().x(), points.front().y(),
                                     std::abs(points.back().x() - points.front().x()),
                                     std::abs(points.back().y() - points.front().y()), this);
            addItem(tmpEllipse);
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
            tmpCircle = new Circle(points.front().x(), points.front().y(), dist(points.front(), points.back()), this);
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

EllipseInfo *Scene::getEllipseInfo() const
{
    return ellipseInfo;
}


CircleInfo *Scene::getCircleInfo() const
{
    return circleInfo;
}

LineInfo *Scene::getLineInfo() const
{
    return lineInfo;
}

RectInfo *Scene::getRectInfo() const
{
    return rectInfo;
}

