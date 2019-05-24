#include "rectangle.h"
#include "scene.h"
#include "line.h"

Rectangle::Rectangle(const QPoint &pos, const QSize &size, Scene *scene, QGraphicsItem *parent)
    : Item(scene, parent),     
      pos(pos), size(size)
{
    drawRectanlge();
}

QRectF Rectangle::boundingRect() const
{
    const int thickness = this->scene->getThickness();
    QPoint topleft = toScenePos(pos);
    topleft = QPoint(topleft.x() - thickness, topleft.y() - thickness);
    QSize sceneSize = QSize(size.width() * thickness + thickness*2 , size.height() * thickness + thickness*2);
    return QRectF(topleft, sceneSize);
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

void Rectangle::drawRectanlge()
{
    for(const auto &point : Drawer::drawRect(pos, size)){
        drawPixel(point);
    }
}

vector<vector<int> > Rectangle::getPoint()
{
    return {
        {pos.x(), pos.y(), 1}
    };
}

void Rectangle::setPoint(const vector<vector<int> > &mat)
{
    pos = {mat[0][0], mat[0][1]};
}

QPoint Rectangle::getPos() const
{
    return pos;
}

void Rectangle::setPos(const QPoint &value)
{
    pos = value;
}

QSize Rectangle::getSize() const
{
    return size;
}

void Rectangle::setSize(const QSize &value)
{
    size = value;
}

void Rectangle::reDraw()
{
    path = QPainterPath();
    drawRectanlge();
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
}

Item::Type Rectangle::getType() const
{
    return Type::RECT;
}
