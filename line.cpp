#include "line.h"
#include "scene.h"

Line::Line()
{
}

Line::Line(int x1, int y1, int x2, int y2)
    : x1(x1), y1(y1), x2(x2), y2(y2)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setFlag(ItemIsSelectable);

    this->setText(0, "Line");
    this->addChild(new QTreeWidgetItem({"Point", "(" + QString::number(x1) + "," + QString::number(y1) + ")"}));
    this->addChild(new QTreeWidgetItem({"Point", "(" + QString::number(x2) + "," + QString::number(y2) + ")"}));
    this->setExpanded(true);
}

QRectF Line::boundingRect() const
{
    int offx = ((Scene*)this->scene())->getOffx();
    int offy = ((Scene*)this->scene())->getOffy();
    int thickness = ((Scene*)this->scene())->getThickness();
    return QRectF((std::min(x1, x2) + offx) * thickness, (offy - std::max(y1, y2)) * thickness,
                  (std::max(x1, x2) + offx) * thickness, (offy - std::min(y1, y2)) * thickness);
}

void Line::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->lastPos().x() < event->pos().x()){
        ++x1;
    } else if (event->lastPos().x() > event->pos().x()){
        --x1;
    }

    if (event->lastPos().y() < event->pos().y()){
        --y1;

    } else if (event->lastPos().y() > event->pos().y()){
        ++y1;
    }
    path = QPainterPath();
    drawLine();

    this->prepareGeometryChange();
    update();
}

void Line::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << this;
}

void Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(path.isEmpty()) drawLine();    
    painter->fillPath(path, QBrush(Qt::black));
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
