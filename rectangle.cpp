#include "rectangle.h"
#include "scene.h"
#include "line.h"

Rectangle::Rectangle(const QPoint &topLeft, const QPoint &topRight, const QPoint &bottomLeft, const QPoint &bottomRight, Scene *scene, QGraphicsItem *parent)
    : Item(scene, parent),
      topLeft(topLeft), topRight(topRight), bottomLeft(bottomLeft), bottomRight(bottomRight)
{
    drawRectangel();
}

Rectangle::Rectangle(const QPoint &topLeft, const QSize &size, Scene *scene, QGraphicsItem *parent)
    : Item(scene, parent), topLeft(topLeft), topRight(topLeft.x() + size.width(), topLeft.y()),
      bottomLeft(topLeft.x(), topLeft.y() - size.height()),
      bottomRight(topLeft.x() + size.width(), topLeft.y() - size.height())
{
    drawRectangel();
}

QRectF Rectangle::boundingRect() const
{    
    const int thickness = this->scene->getThickness();
    return QRectF(toScenePos(topLeft) * (thickness - 1) , toScenePos(bottomRight) * (thickness + 1));
}

QPainterPath Rectangle::shape() const{
    return path + fillPath;
}

void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->fillPath(path, brush);
    painter->fillPath(fillPath, fillColor);
}

void Rectangle::drawRectangel()
{
    for(const auto &point : Drawer::drawRect(topLeft, topRight, bottomLeft, bottomRight)){
        drawPixel(point);
    }
}

//vector<vector<int> > Rectangle::getPoint()
//{
//    return {
//        {topLeft.x(), topLeft.y(), 1},
//        {topRight.x(), topRight.y(), 1},
//        {bottomLeft.x(), bottomLeft.y(), 1},
//        {bottomRight.x(), bottomRight.y(), 1}
//    };
//}

//void Rectangle::setPoint(const vector<vector<int> > &mat)
//{
//    topLeft = {mat[0][0], mat[0][1]};
//    topRight = {mat[1][0], mat[1][1]};
//    bottomLeft = {mat[2][0], mat[2][1]};
//    bottomRight = {mat[3][0], mat[3][1]};
//}

//QPoint Rectangle::getPos() const
//{
//    return topLeft;
//}

//void Rectangle::setPos(const QPoint &value)
//{
//    topLeft = value;
//}

//QSize Rectangle::getSize() const
//{
//    return size;
//}

//void Rectangle::setSize(const QSize &value)
//{
//    size = value;
//}

void Rectangle::reDraw()
{
    path = QPainterPath();
    drawRectangel();
    scene->update();
}

void Rectangle::fill(const QColor &color)
{
    fillColor = color;
    fillPath = QPainterPath();
    for(const auto &point : Drawer::floodFill(
             Drawer::drawRect(pos, size), {pos.x() + size.width()/2,pos.y() - size.height() / 2})){
        drawPixel(point, fillPath);
    }
    scene->update();
}

Item::Type Rectangle::getType() const
{
    return Type::RECT;
}
