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

    lineInfo = new LineInfo();
    rectInfo = new RectInfo();
    circleInfo = new CircleInfo();
    ellipseInfo = new EllipseInfo();
}

void Scene::setWindow(Window *value){
    this->window = value;    
}

void Scene::doChangeColor(const QColor &color)
{
    for(auto &item : this->selectedItems()){
        static_cast<Item*>(item)->setBrush(QBrush(color));
    }
}

void Scene::doFillColor(const QColor &color)
{
    if (this->selectedItems().isEmpty()) return;
    Item *item = static_cast<Item*>(this->selectedItems().first());
    switch (item->getType()) {
    case Item::Type::RECT:
        static_cast<Rectangle*>(item)->setFillColor(color);
        break;
    case Item::Type::CIRCLE:
        static_cast<Circle*>(item)->setFillColor(color);
        break;
    case Item::Type::ELIP:
        static_cast<Ellipse*>(item)->setFillColor(color);
        break;
    default:
        break;
    }
}

void Scene::deleteItem()
{
    for(auto &item : this->selectedItems()){        
        delete item;
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

void Scene::clearAll()
{
    this->clear();
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
            rect->setTopLeft(affine.translate(rect->getTopLeft(), dx, dy));
            rect->setTopRight(affine.translate(rect->getTopRight(), dx, dy));
            rect->setBottomLeft(affine.translate(rect->getBottomLeft(), dx, dy));
            rect->setBottomRight(affine.translate(rect->getBottomRight(), dx, dy));
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
            rect->setTopLeft(affine.rotate(rect->getTopLeft(), x, y, angle));
            rect->setTopRight(affine.rotate(rect->getTopRight(), x, y, angle));
            rect->setBottomLeft(affine.rotate(rect->getBottomLeft(), x, y, angle));
            rect->setBottomRight(affine.rotate(rect->getBottomRight(), x, y, angle));
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
    const float sx = window->getSXScale();
    const float sy = window->getSYScale();
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
            rect->setTopLeft(affine.scale(rect->getTopLeft(), sx, sy));
            rect->setTopRight(affine.scale(rect->getTopRight(), sx, sy));
            rect->setBottomLeft(affine.scale(rect->getBottomLeft(), sx, sy));
            rect->setBottomRight(affine.scale(rect->getBottomRight(), sx, sy));
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

void Scene::doReflection()
{    
    if (selectedItems().isEmpty()) return;
    Item *selectedItem = static_cast<Item*>(selectedItems().first());
    const int x = window->getXReflection();
    const int y = window->getYReflection();
    if (selectedItem){
        switch (selectedItem->getType()) {
        case Item::Type::LINE:
        {
            Line *line = static_cast<Line*>(selectedItem);
            line->setPoint1(affine.reflect(line->getPoint1(), x, y));
            line->setPoint2(affine.reflect(line->getPoint2(), x, y));
            line->reDraw();
            lineInfo->setLine(line);
            break;
        }
        case Item::Type::RECT:
        {
            Rectangle *rect = static_cast<Rectangle*>(selectedItem);
            rect->setTopLeft(affine.reflect(rect->getTopLeft(), x, y));
            rect->setTopRight(affine.reflect(rect->getTopRight(), x, y));
            rect->setBottomLeft(affine.reflect(rect->getBottomLeft(), x, y));
            rect->setBottomRight(affine.reflect(rect->getBottomRight(), x, y));
            rect->reDraw();
            rectInfo->setRect(rect);
            break;
        }
        case Item::Type::CIRCLE:
        {
            Circle *circle = static_cast<Circle*>(selectedItem);
            circle->setPoint(affine.reflect(circle->getPoint(), x, y));
            circle->reDraw();
            circleInfo->setCircle(circle);
            break;
        }
        case Item::Type::ELIP:
        {
            Ellipse *ellipse = static_cast<Ellipse*>(selectedItem);
            ellipse->setPoint(affine.reflect(ellipse->getPoint(), x, y));
            ellipse->reDraw();
            ellipseInfo->setEllipse(ellipse);
            break;
        }
        default:
            break;
        }
    }
}

void Scene::play(int delay)
{
    if (timer) delete timer;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(doAnimation()));
    timer->start(100);
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

    //Draw ruler
    painter->setOpacity(0.8);
    painter->setFont(QFont("Segoe UI", 8));
    const int jump = 10 * thickness;

    for(int xJump = halfThick + jump, x = -offx + 10; xJump < this->width(); xJump += jump, x += 10){
        painter->drawText(xJump - 10, halfHeight + halfThick + 10, QString::number(x));
    }
    for(int yJump = halfThick + jump, y = offy - 10; yJump < this->height(); yJump += jump, y -= 10){
        if (y == 0) continue;
        painter->drawText(halfWidth + halfThick - 15, yJump + 5, QString::number(y));
    }

    painter->setOpacity(1.0);    
    // Draw x, y
    painter->setFont(QFont("Segoe UI", 10));
    painter->drawText(halfWidth - 10, 10, QString("x"));
    painter->drawText(static_cast<int>(this->width()) - 10, halfHeight + 15, QString("y"));

    // Draw arrow
    halfWidth += halfThick;
    halfHeight += halfThick;
    painter->drawLine(static_cast<int>(this->width()) - 5, halfHeight - 5, static_cast<int>(this->width()), halfHeight);
    painter->drawLine(static_cast<int>(this->width()) - 5, halfHeight + 5, static_cast<int>(this->width()), halfHeight);
    painter->drawLine(halfWidth - 5, 5, halfWidth, 0);
    painter->drawLine(halfWidth + 5, 5, halfWidth, 0);
}

void Scene::doAnimation()
{
    static int cnt = 80;
    if (cnt == -80) {
        timer->stop();
        disconnect(timer, SIGNAL(timeout()), this, SLOT(doAnimation()));
        cnt = 0;
    }
    --cnt;
    this->clear();
    addItem(new Rectangle(QPoint(cnt, 0), QSize(10, 10), this));
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

