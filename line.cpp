#include "line.h"
#include "scene.h"

//Line::Line(Scene *scene)
//{

//}

//Line::Line(int x1, int y1, int x2, int y2)
//    : x1(x1), y1(y1), x2(x2), y2(y2)
//{
//    setFlag(ItemIsMovable);
//    setFlag(ItemSendsGeometryChanges);

////    this->setText(0, "Line");
////    this->addChild(new QTreeWidgetItem({"Point", "(" + QString::number(x1) + "," + QString::number(y1) + ")"}));
////    this->addChild(new QTreeWidgetItem({"Point", "(" + QString::number(x2) + "," + QString::number(y2) + ")"}));
////    this->setExpanded(true);
//}

//Line::Line(const QPoint &from, const QPoint &to) : Line(from.x(), from.y(), to.x(), to.y())
//{    }

//const Line &Line::operator=(const Line &another)
//{
//    x1 = another.x1;
//    x2 = another.x2;
//    y1 = another.y1;
//    y2 = another.y2;
//}

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

QStringList Line::getInfo() const
{
    QStringList result;
    result << QString("<b><u>Line</u></b>" );
    result << QString("\tPoint: (" + QString::number(x1) + "," + QString::number(y1) + ")");
    result << QString("\tPoint: (" + QString::number(x2) + "," + QString::number(y2) + ")");
//    result << QString("\tColor: " + brush.color().name());
    return result;
}

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
//    qDebug() << "item " << this;
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

void Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->fillPath(path, brush);
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
