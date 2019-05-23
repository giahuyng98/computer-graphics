#include "line.h"
#include "scene.h"

Line::Line(Scene *scene, QGraphicsItem *parent)
    :Item(scene, parent)
{
}

Line::Line(int x1, int y1, int x2, int y2, Scene *scene, QGraphicsItem *parent)
    :Item(scene, parent), x1(x1), y1(y1), x2(x2), y2(y2)
{
    drawLine();
}

Line::Line(const QPoint &from, const QPoint &to, Scene *scene, QGraphicsItem *parent)
    : Line(from.x(), from.y(), to.x(), to.y(), scene, parent)
{
}

Item::Type Line::getType() const
{
    return Type::LINE;
}

vector<vector<int> > Line::getPoint1()
{
    return {
        {x1, y1, 1}
    };
}

vector<vector<int> > Line::getPoint2()
{
    return {
        {x2, y2, 1}
    };
}

void Line::setPoint1(const vector<vector<int> > &mat)
{
    x1 = mat[0][0];
    y1 = mat[0][1];
}

void Line::setPoint2(const vector<vector<int> > &mat)
{
    x2 = mat[0][0];
    y2 = mat[0][1];
}


//QStringList Line::getInfo() const
//{
//    QStringList result;
//    result << QString("<b><u>Line</u></b>" );
//    result << QString("\tPoint: (" + QString::number(x1) + "," + QString::number(y1) + ")");
//    result << QString("\tPoint: (" + QString::number(x2) + "," + QString::number(y2) + ")");
////    result << QString("\tColor: " + brush.color().name());
//    return result;
//}

QRectF Line::boundingRect() const
{
    const int offx = this->scene->getOffx();
    const int offy = this->scene->getOffy();
    const int thickness = this->scene->getThickness();
    return QRectF((std::min(x1, x2) + offx) * thickness, (offy - std::max(y1, y2)) * thickness,
                  (std::max(x1, x2) + offx) * thickness, (offy - std::min(y1, y2)) * thickness);
}

void Line::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}

QVariant Line::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
//    if (change == QGraphicsItem::ItemSelectedChange){
//        if (value == true){
//            brush = QBrush(Qt::blue);
//        } else{
//            brush = QBrush(Qt::black);
//        }
//    }
    return QGraphicsItem::itemChange(change, value);
}

void Line::drawLine()
{
    if (std::abs(y2 - y1) < std::abs(x2 - x1)){
        if (x1 > x2)
            drawLineLow(x2, y2, x1, y1);
        else
            drawLineLow(x1, y1, x2, y2);
    } else if (y1 > y2){
        drawLineHigh(x2, y2, x1, y1);
    } else
        drawLineHigh(x1, y1, x2, y2);
}

void Line::drawLineLow(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int ystep = 1;
    if (dy < 0){
        ystep = -1;
        dy = -dy;
    }
    int d = (dy << 1) - dx;
    for(int x = x1, y = y1; x <= x2; ++x){
        drawPixel(x, y);
        if (d > 0){
            y += ystep;
            d -= dx << 1;
        }
        d += dy << 1;
    }
}

void Line::drawLineHigh(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int xstep = 1;
    if (dx < 0){
        xstep = -1;
        dx = -dx;
    }
    int d = (dx << 1) - dy;
    for(int x = x1, y = y1; y <= y2; ++y){
        drawPixel(x, y);
        if (d > 0){
            x += xstep;
            d -= dy << 1;
        }
        d += dx << 1;
    }
}

int Line::getY2() const
{
    return y2;
}

void Line::setY2(int value)
{
    y2 = value;
}

void Line::reDraw()
{
    path = QPainterPath();
    drawLine();
    scene->update();
}

QPainterPath Line::getLine(int x1, int y1, int x2, int y2)
{
    QPainterPath tmp = path;
    path = QPainterPath();
    std::tuple<int,int,int,int> t = {this->x1, this->y1, this->x2, this->y2};
    std::tie(this->x1, this->y1, this->x2, this->y2) = {x1, y1, x2, y2};
    drawLine();
    std::swap(tmp, path);
    std::tie(this->x1, this->y1, this->x2, this->y2) = t;
    return tmp;
}

int Line::getX2() const
{
    return x2;
}

void Line::setX2(int value)
{
    x2 = value;
}

int Line::getY1() const
{
    return y1;
}

void Line::setY1(int value)
{
    y1 = value;
}

int Line::getX1() const
{
    return x1;
}

void Line::setX1(int value)
{
    x1 = value;
}
