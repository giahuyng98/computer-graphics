#include "scene3d.h"
#include <QPainter>

Scene3D::Scene3D(QWidget *parent) : QGraphicsScene (parent)
{
    const int WIDTH = 1200;
    const int HEIGH = 600;

    this->setSceneRect(0, 0, WIDTH, HEIGH);
    lenx = static_cast<int>(width()) / thickness;
    leny = static_cast<int>(height()) / thickness;

    offx = lenx / 2;
    offy = leny / 2;
}

int Scene3D::getOffx() const
{
    return offx;
}

int Scene3D::getOffy() const
{
    return offy;
}

int Scene3D::getThickness() const
{
    return thickness;
}

void Scene3D::setWindow(Window *value)
{
    window = value;
}

void Scene3D::addCube(int x, int y, int z, int width, int height, int length)
{
    Cube *cube = new Cube(x, y, z, width, height, length, this);
    addItem(cube);
}

void Scene3D::drawBackground(QPainter *painter, const QRectF &rect)
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
    const int square = std::min(halfHeight, halfWidth) + halfThick * 2;
    painter->drawLine(halfWidth + square , 0, square, static_cast<int>(this->height()));

//    const int space = thickness * 5; //line spacing
//    painter->setOpacity(0.25);

//    // Draw vertical line
//    for(int xJump = halfThick; xJump < this->width(); xJump += space){
//        painter->drawLine(xJump, 0, xJump, static_cast<int>(this->height()));
//    }

//    // Draw horizontal line
//    for(int yJump = halfThick; yJump < this->height(); yJump += space){
//        painter->drawLine(0, yJump, static_cast<int>(this->width()), yJump);
//    }

//    // Draw grid
//    painter->setOpacity(0.08);
//    for(int xJump = halfThick; xJump < this->width(); xJump += thickness){
//        painter->drawLine(xJump, 0, xJump, static_cast<int>(this->height()));
//    }
//    for(int yJump = halfThick; yJump < this->height(); yJump += thickness){
//        painter->drawLine(0, yJump, static_cast<int>(this->width()), yJump);
//    }

    //Draw ruler
    painter->setOpacity(0.8);
    painter->setFont(QFont("Segoe UI", 8));
    const int jump = 10 * thickness;

    for(int xJump = halfThick + jump, y = halfHeight + halfThick + 10, x = -offx + 10;
         xJump < this->width(); xJump += jump, x += 10){
        painter->drawText(xJump - 10, y, QString::number(x));
    }
    for(int yJump = halfThick + jump, y = offy - 10, x = halfWidth + halfThick - 15;
         yJump < this->height(); yJump += jump, y -= 10){
        if (y == 0) continue;
        painter->drawText(x, yJump + 5, QString::number(y));
    }
    for(int x = square + halfWidth, y = halfThick, val = -std::min(offx, offy);
         x > 0 && y < this->height(); x -= jump, y += jump, val += 10){
        if (val == 0) continue;
        painter->drawText(x, y + 5, QString::number(val));
    }

    painter->setOpacity(1.0);
    // Draw x, y
    painter->setFont(QFont("Segoe UI", 10));
    painter->drawText(halfWidth - 10, 10, QString("z"));
    painter->drawText(static_cast<int>(this->width()) - 10, halfHeight + 15, QString("x"));
    painter->drawText(square + 15, static_cast<int>(this->height()) - 5, QString("y"));

    // Draw arrow
    halfWidth += halfThick;
    halfHeight += halfThick;
    painter->drawLine(static_cast<int>(this->width()) - 5, halfHeight - 5, static_cast<int>(this->width()), halfHeight);
    painter->drawLine(static_cast<int>(this->width()) - 5, halfHeight + 5, static_cast<int>(this->width()), halfHeight);
    painter->drawLine(halfWidth - 5, 5, halfWidth, 0);
    painter->drawLine(halfWidth + 5, 5, halfWidth, 0);
    painter->drawLine(square, static_cast<int>(this->height()) - 7, square, static_cast<int>(this->height()));
    painter->drawLine(square, static_cast<int>(this->height()) - 1, square + 7, static_cast<int>(this->height()) - 1);
}
