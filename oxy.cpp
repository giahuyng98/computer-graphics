#include "oxy.h"
#include <QThread>

Oxy::Oxy(QWidget *parent)
    : QWidget (parent)
{
    thick = 5;
}

void Oxy::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    draw(&painter);
}

//void Oxy::resizeEvent(QResizeEvent *event)
//{
//}

void Oxy::mousePressEvent(QMouseEvent *event)
{
    int x = event->x() / thick - offx;
    int y = offy - event->y() / thick;

    qDebug() << x << " " << y;
    putPixel(x, y);
    static std::pair<int,int> last = {x, y};
    if (last != std::make_pair(x, y)){
        drawLine(last.first, last.second, x, y);
        last = {x, y};
        repaint();
    }

}

void Oxy::draw(QPainter *painter)
{

    rows = this->height() / thick;
    cols = this->width() / thick;

    offy = rows / 2;
    offx = cols / 2;
    if (rows != mat.size() || cols != mat.front().size()){
        mat.resize(rows);
        for(auto &row : mat){
            row.resize(cols, Qt::white);
        }
    }


    for (int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j){
            painter->fillRect(j * thick, i * thick, thick, thick, mat[i][j]);
        }
    }

    drawCoordinate(painter);
}

void Oxy::putPixel(int x, int y, const QColor &color)
{
    mat[offy - y][x + offx] = color;    
}

void Oxy::drawLine(int x1, int y1, int x2, int y2)
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
void Oxy::drawLineLow(int x1, int y1, int x2, int y2)
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
        putPixel(x, y);
        if (d > 0){
            y += ystep;
            d -= dx << 1;
        }
        d += dy << 1;
    }
}

void Oxy::drawLineHigh(int x1, int y1, int x2, int y2)
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
        putPixel(x, y);
        if (d > 0){
            x += xstep;
            d -= dy << 1;
        }
        d += dx << 1;
    }
}

void Oxy::drawCoordinate(QPainter *painter)
{
    int halfHeight = this->height() / 2;
    int halfWidth = this->width() / 2;
    const int halfThick = thick / 2; //make it center

    // Draw ox and oy
    painter->setPen(QPen(QBrush(Qt::black), 1));
    painter->setOpacity(0.6);
    painter->drawLine(0, halfHeight + halfThick, this->width(), halfHeight + halfThick);
    painter->drawLine(halfWidth + halfThick, 0, halfWidth + halfThick, this->height());

    const int space = thick * 5; //line spacing
//    painter->setPen(QPen(QBrush(Qt::black), 1));
    painter->setOpacity(0.25);

    // Draw vertical line
    for(int xJumpRight = halfWidth, xJumpLeft = halfWidth; xJumpRight < this->width(); xJumpRight += space, xJumpLeft -= space){
        painter->drawLine(xJumpRight + halfThick, 0, xJumpRight + halfThick, this->height());
        painter->drawLine(xJumpLeft + halfThick, 0, xJumpLeft + halfThick, this->height());
    }

    // Draw horizontal line
    for(int yJumpRight = halfHeight, yJumpLeft = halfHeight; yJumpRight < this->height(); yJumpRight += space, yJumpLeft -= space){
        painter->drawLine(0, yJumpRight + halfThick, this->width(), yJumpRight + halfThick);
        painter->drawLine(0, yJumpLeft + halfThick, this->width(), yJumpLeft + halfThick);
    }

    painter->setOpacity(0.08);
    for(int xJumpRight = halfWidth, xJumpLeft = halfWidth; xJumpRight < this->width(); xJumpRight += thick, xJumpLeft -= thick){
        painter->drawLine(xJumpRight + halfThick, 0, xJumpRight + halfThick, this->height());
        painter->drawLine(xJumpLeft + halfThick, 0, xJumpLeft + halfThick, this->height());
    }
    for(int yJumpRight = halfHeight, yJumpLeft = halfHeight; yJumpRight < this->height(); yJumpRight += thick, yJumpLeft -= thick){
        painter->drawLine(0, yJumpRight + halfThick, this->width(), yJumpRight + halfThick);
        painter->drawLine(0, yJumpLeft + halfThick, this->width(), yJumpLeft + halfThick);
    }



//    painter->setPen(QPen(QBrush(Qt::black), 2));
    painter->setOpacity(1.0);
//    painter->setRenderHint(QPainter::RenderHint::Antialiasing);
    // Arrow ox
    halfWidth += halfThick;
    halfHeight += halfThick;
    painter->drawLine(this->width() - 5, halfHeight - 5, this->width(), halfHeight);
    painter->drawLine(this->width() - 5, halfHeight + 5, this->width(), halfHeight);
//    QPainterPath xName;
//    xName.addText(this->width() - 10, halfHeight + 10, QFont("consolas"), "x");
//    painter->drawPath(xName);
//    painter->drawText(this->width() - 10, halfHeight + 10, "x");
    // Arrow oy
    painter->drawLine(halfWidth - 5, 5, halfWidth, 0);
    painter->drawLine(halfWidth + 5, 5, halfWidth, 0);
//    QPainterPath yName;
//    yName.addText(halfWidth + 10, 10, QFont("consolas"), "y");
//    painter->drawPath(yName);
//    painter->drawText(halfWidth + 10, 10, "y");

}


