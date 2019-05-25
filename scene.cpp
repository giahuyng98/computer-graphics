#include "scene.h"
#include "item.h"
#include <QDebug>
#include <QPoint>
#include "window.h"

Scene::Scene(QWidget *parent) : QGraphicsScene (parent)
{
    const int WIDTH = 1200;
    const int HEIGH = 600;

    this->setSceneRect(0, 0, WIDTH, HEIGH);
    offx = static_cast<int>(width()) / thickness / 2;
    offy = static_cast<int>(height()) / thickness / 2;
}

void Scene::setWindow(Window *value){
    this->window = value;    
}

void Scene::translateItem(Item *item, int dx, int dy)
{
    switch (item->getType()) {
    case Item::Type::LINE:
    {
        Line *line = static_cast<Line*>(item);
        line->setPoint1(affine.translate(line->getPoint1(), dx, dy));
        line->setPoint2(affine.translate(line->getPoint2(), dx, dy));
        line->reDraw();
        break;
    }
    case Item::Type::RECT:
    {
        Rectangle *rect = static_cast<Rectangle*>(item);
        rect->setTopLeft(affine.translate(rect->getTopLeft(), dx, dy));
        rect->setTopRight(affine.translate(rect->getTopRight(), dx, dy));
        rect->setBottomLeft(affine.translate(rect->getBottomLeft(), dx, dy));
        rect->setBottomRight(affine.translate(rect->getBottomRight(), dx, dy));
        rect->reDraw();
        break;
    }
    case Item::Type::CIRCLE:
    {
        Circle *circle = static_cast<Circle*>(item);
        circle->setPoint(affine.translate(circle->getPoint(), dx, dy));
        circle->reDraw();
        break;
    }
    case Item::Type::ELIP:
    {
        Ellipse *ellipse = static_cast<Ellipse*>(item);
        ellipse->setPoint(affine.translate(ellipse->getPoint(), dx, dy));
        ellipse->reDraw();
        break;
    }
    default:
        break;
    }

}

void Scene::rotateItem(Item *item, int x, int y, int angle)
{
    switch (item->getType()) {
    case Item::Type::LINE:
    {
        Line *line = static_cast<Line*>(item);
        line->setPoint1(affine.rotate(line->getPoint1(), x, y, angle));
        line->setPoint2(affine.rotate(line->getPoint2(), x, y, angle));
        line->reDraw();
        break;
    }
    case Item::Type::RECT:
    {
        Rectangle *rect = static_cast<Rectangle*>(item);
        rect->setTopLeft(affine.rotate(rect->getTopLeft(), x, y, angle));
        rect->setTopRight(affine.rotate(rect->getTopRight(), x, y, angle));
        rect->setBottomLeft(affine.rotate(rect->getBottomLeft(), x, y, angle));
        rect->setBottomRight(affine.rotate(rect->getBottomRight(), x, y, angle));
        rect->reDraw();
        break;
    }
    case Item::Type::CIRCLE:
    {
        Circle *circle = static_cast<Circle*>(item);
        circle->setPoint(affine.rotate(circle->getPoint(), x, y, angle));
        circle->reDraw();
        break;
    }
    case Item::Type::ELIP:
    {
        Ellipse *ellipse = static_cast<Ellipse*>(item);
        ellipse->setPoint(affine.rotate(ellipse->getPoint(), x, y, angle));
        ellipse->reDraw();
        break;
    }
    default:
        break;
    }
}

void Scene::scaleItem(Item *item, float sx, float sy)
{
    switch (item->getType()) {
    case Item::Type::LINE:
    {
        Line *line = static_cast<Line*>(item);
        line->setPoint1(affine.scale(line->getPoint1(), sx, sy));
        line->setPoint2(affine.scale(line->getPoint2(), sx, sy));
        line->reDraw();
        break;
    }
    case Item::Type::RECT:
    {
        Rectangle *rect = static_cast<Rectangle*>(item);
        rect->setTopLeft(affine.scale(rect->getTopLeft(), sx, sy));
        rect->setTopRight(affine.scale(rect->getTopRight(), sx, sy));
        rect->setBottomLeft(affine.scale(rect->getBottomLeft(), sx, sy));
        rect->setBottomRight(affine.scale(rect->getBottomRight(), sx, sy));
        rect->reDraw();
        break;
    }
    case Item::Type::CIRCLE:
    {
        Circle *circle = static_cast<Circle*>(item);
        circle->setPoint(affine.scale(circle->getPoint(), sx, sy));
        circle->reDraw();
        break;
    }
    case Item::Type::ELIP:
    {
        Ellipse *ellipse = static_cast<Ellipse*>(item);
        ellipse->setPoint(affine.scale(ellipse->getPoint(), sx, sy));
        ellipse->reDraw();
        break;
    }
    default:
        break;
    }
}

void Scene::reflectItem(Item *item, int x, int y)
{
    switch (item->getType()) {
    case Item::Type::LINE:
    {
        Line *line = static_cast<Line*>(item);
        line->setPoint1(affine.reflect(line->getPoint1(), x, y));
        line->setPoint2(affine.reflect(line->getPoint2(), x, y));
        line->reDraw();
        break;
    }
    case Item::Type::RECT:
    {
        Rectangle *rect = static_cast<Rectangle*>(item);
        rect->setTopLeft(affine.reflect(rect->getTopLeft(), x, y));
        rect->setTopRight(affine.reflect(rect->getTopRight(), x, y));
        rect->setBottomLeft(affine.reflect(rect->getBottomLeft(), x, y));
        rect->setBottomRight(affine.reflect(rect->getBottomRight(), x, y));
        rect->reDraw();
        break;
    }
    case Item::Type::CIRCLE:
    {
        Circle *circle = static_cast<Circle*>(item);
        circle->setPoint(affine.reflect(circle->getPoint(), x, y));
        circle->reDraw();
        break;
    }
    case Item::Type::ELIP:
    {
        Ellipse *ellipse = static_cast<Ellipse*>(item);
        ellipse->setPoint(affine.reflect(ellipse->getPoint(), x, y));
        ellipse->reDraw();
        break;
    }
    default:
        break;
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

void Scene::wheelEvent(QGraphicsSceneWheelEvent *wheelEvent)
{
    if (wheelEvent->modifiers() & Qt::ControlModifier){
        if (wheelEvent->delta() > 0){
            setThickness(std::min(thickness + 5, 20));
        } else {
            setThickness(std::max(thickness - 5, 5));
        }
        window->setThickness(thickness);
        update();
    }
    QGraphicsScene::wheelEvent(wheelEvent);
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
    return QPoint(static_cast<int>(scenePos.x()) / thickness - offx,
                  offy - static_cast<int>(scenePos.y()) / thickness);
}

void Scene::setThickness(int value)
{
    thickness = value;
    offx = static_cast<int>(std::round(width() / thickness / 2));
    offy = static_cast<int>(std::round(height() / thickness / 2));
}

QPoint Scene::toScenePos(const QPoint &userPos) const
{
    return QPoint((userPos.x() + offx) * thickness, (offy - userPos.y()) * thickness);
}
