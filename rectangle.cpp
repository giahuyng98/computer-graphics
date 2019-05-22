#include "rectangle.h"
#include "scene.h"
#include "line.h"

Rectangle::Rectangle(const QPoint &pos, const QSize &size, Scene *scene, QGraphicsItem *parent)
    : Item(scene, parent),     
      pos(pos), size(size)
{
    set4Line();
}

QRectF Rectangle::boundingRect() const
{
    const int thickness = this->scene->getThickness();
    QPoint topleft = toScenePos(pos);
    topleft = QPoint(topleft.x() - thickness, topleft.y() - thickness);
    QSize sceneSize = QSize(size.width() * thickness + thickness*2 , size.height() * thickness + thickness*2);
    return QRectF(topleft, sceneSize);
}

void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->fillPath(path, brush);
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

void Rectangle::set4Line()
{
    path = QPainterPath();
    path = path.united((Line(pos, QPoint(pos.x() + size.width(), pos.y()), scene).getPath()));
    path = path.united((Line(pos, QPoint(pos.x(), pos.y() - size.height()), scene).getPath()));
    path = path.united((Line(pos.x(), pos.y() - size.height(), pos.x() + size.width(), pos.y() - size.height(), scene).getPath()));
    path = path.united((Line(pos.x() + size.width(), pos.y(), pos.x() + size.width(), pos.y() - size.height(), scene).getPath()));
}

void Rectangle::reDraw()
{
    set4Line();    
    scene->update();
}

Item::Type Rectangle::getType() const
{
    return Type::RECT;
}
