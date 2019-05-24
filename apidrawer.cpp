#include "apidrawer.h"
#include <cmath>

bool operator<(const QPoint &p1, const QPoint &p2){
    return std::make_pair(p1.x(), p1.y()) < std::make_pair(p2.x(), p2.y());
}
namespace Drawer{
VPoints drawLine(int x1, int y1, int x2, int y2){
    VPoints result;

    auto drawLineLow = [&result](int x1, int y1, int x2, int y2){
        int dx = x2 - x1;
        int dy = y2 - y1;
        int ystep = 1;
        if (dy < 0){
            ystep = -1;
            dy = -dy;
        }
        int d = (dy << 1) - dx;
        for(int x = x1, y = y1; x <= x2; ++x){
            result.emplace_back(x, y);
            if (d > 0){
                y += ystep;
                d -= dx << 1;
            }
            d += dy << 1;
        }
    };

    auto drawLineHigh = [&result](int x1, int y1, int x2, int y2){
        int dx = x2 - x1;
        int dy = y2 - y1;
        int xstep = 1;
        if (dx < 0){
            xstep = -1;
            dx = -dx;
        }
        int d = (dx << 1) - dy;
        for(int x = x1, y = y1; y <= y2; ++y){
            result.emplace_back(x, y);
            if (d > 0){
                x += xstep;
                d -= dy << 1;
            }
            d += dx << 1;
        }
    };

    if (std::abs(y2 - y1) < std::abs(x2 - x1)){
        if (x1 > x2)
            drawLineLow(x2, y2, x1, y1);
        else
            drawLineLow(x1, y1, x2, y2);
    } else if (y1 > y2){
        drawLineHigh(x2, y2, x1, y1);
    } else
        drawLineHigh(x1, y1, x2, y2);
    return result;
}

VPoints drawLine(const QPoint &from, const QPoint &to){
    return drawLine(from.x(), from.y(), to.x(), to.y());
}

VPoints drawDashedLine(const QPoint &from, const QPoint &to, int dash, int dot){
    auto tmp = drawLine(from, to);
    VPoints result;
    for(auto it = tmp.begin(); it < tmp.end();){
        int addDash = 0;
        while (addDash < dash && it < tmp.end()) result.emplace_back(*it++), ++addDash;
        int ignoreDot = 0;
        while (ignoreDot < dot && it < tmp.end()) ++it, ++ignoreDot;
    }
    return result;
}

VPoints drawRect(const QPoint &topLelf, const QSize &size){
    VPoints line1, line2, line3, line4;
    line1 = drawLine(topLelf.x(), topLelf.y(), topLelf.x() + size.width(), topLelf.y());
    line2 = drawLine(topLelf.x(), topLelf.y(), topLelf.x(), topLelf.y() - size.height());
    line3 = drawLine(topLelf.x(), topLelf.y() - size.height(), topLelf.x() + size.width(), topLelf.y() - size.height());
    line4 = drawLine(topLelf.x() + size.width(), topLelf.y(), topLelf.x() + size.width(), topLelf.y() - size.height());
    VPoints result;
//    result.reserve(line1.size() * 4);
    std::move(line1.begin(), line1.end(), std::back_inserter(result));
    std::move(line2.begin(), line2.end(), std::back_inserter(result));
    std::move(line3.begin(), line3.end(), std::back_inserter(result));
    std::move(line4.begin(), line4.end(), std::back_inserter(result));
    std::sort(result.begin(), result.end());
    result.erase(std::unique(result.begin(), result.end()), result.end());
    return result;
}



VPoints drawCircle(const QPoint &center, int radius){
    VPoints result;
    auto add8Points = [&result](int x, int y, int dx, int dy){
        result.emplace_back(x + dx, y + dy);
        result.emplace_back(x - dx, y + dy);
        result.emplace_back(x + dx, y - dy);
        result.emplace_back(x - dx, y - dy);
        result.emplace_back(x + dy, y + dx);
        result.emplace_back(x - dy, y + dx);
        result.emplace_back(x + dy, y - dx);
        result.emplace_back(x - dy, y - dx);
    };

    int p = 0, q = radius;
    int d = 3 - 2 * radius;
    add8Points(center.x(), center.y(), p, q);
    while (q >= p){
        ++p;
        if (d <= 0) d = d + 4*p + 6;
        else{
            --q;
            d = d + 4 * (p - q) + 10;
        }
        add8Points(center.x(), center.y(), p, q);
    }
    std::sort(result.begin(), result.end());
    result.erase(std::unique(result.begin(), result.end()), result.end());
    return result;
}

VPoints drawEllipse(const QPoint &center, int xRadius, int yRadius){
    auto add4Points = [](VPoints &result, int x, int y, int dx, int dy){
        result.emplace_back(x - dx, y + dy);
        result.emplace_back(x + dx, y + dy);
        result.emplace_back(x - dx, y - dy);
        result.emplace_back(x + dx, y - dy);
    };
    return drawEllipseUtil(center, xRadius, yRadius, add4Points);
}

VPoints drawCube(int x, int y, int z, int width, int height, int length, QPoint (*method)(int x, int y, int z))
{
    QPoint p1 = method(x, y, z);
    QPoint p2 = method(x + length, y, z);
    QPoint p3 = method(x + length, y, z + height);
    QPoint p4 = method(x, y, z + height);
    QPoint p5 = method(x, y + width, z);
    QPoint p6 = method(x + length, y + width, z);
    QPoint p7 = method(x + length, y + width, z + height);
    QPoint p8 = method(x, y + width, z + height);

    const int DASH = 2, DOT = 2;

    auto line1 = drawDashedLine(p1, p2, DASH, DOT);
    auto line2 = drawLine(p2, p3);
    auto line3 = drawLine(p3, p4);
    auto line4 = drawDashedLine(p4, p1, DASH, DOT);
    auto line5 = drawLine(p5, p6);
    auto line6 = drawLine(p6, p7);
    auto line7 = drawLine(p7, p8);
    auto line8 = drawLine(p8, p5);
    auto line9 = drawLine(p4, p8);
    auto line10 = drawLine(p3, p7);
    auto line11 = drawDashedLine(p1, p5, DASH, DOT);
    auto line12 = drawLine(p2, p6);

    VPoints result;
    std::move(line1.begin(), line1.end(), std::back_inserter(result));
    std::move(line2.begin(), line2.end(), std::back_inserter(result));
    std::move(line3.begin(), line3.end(), std::back_inserter(result));
    std::move(line4.begin(), line4.end(), std::back_inserter(result));
    std::move(line5.begin(), line5.end(), std::back_inserter(result));
    std::move(line6.begin(), line6.end(), std::back_inserter(result));
    std::move(line7.begin(), line7.end(), std::back_inserter(result));
    std::move(line8.begin(), line8.end(), std::back_inserter(result));
    std::move(line9.begin(), line9.end(), std::back_inserter(result));
    std::move(line10.begin(), line10.end(), std::back_inserter(result));
    std::move(line11.begin(), line11.end(), std::back_inserter(result));
    std::move(line12.begin(), line12.end(), std::back_inserter(result));
    std::sort(result.begin(), result.end());
    result.erase(std::unique(result.begin(), result.end()), result.end());
    return result;
}

VPoints drawSphere(int x, int y, int z, int r, QPoint (*method)(int, int, int)){
    QPoint center = method(x, y, z);
    auto circle = drawCircle(center, r);
    auto ellipse = drawEllipse(center, r, r / 4);
    VPoints result;
    std::move(circle.begin(), circle.end(), std::back_inserter(result));
    std::move(ellipse.begin(), ellipse.end(), std::back_inserter(result));
    std::sort(result.begin(), result.end());
    result.erase(std::unique(result.begin(), result.end()), result.end());
    return result;
}

QPoint cavalier(int x, int y, int z){
    return QPoint(std::round(x - y * CAVALIER), std::round(z - y * CAVALIER));
}

QPoint cabinet(int x, int y, int z)
{
    return QPoint(std::round(x - y * CABINET), std::round(z - y * CABINET));
}

VPoints drawHalfTopEllipse(const QPoint &center, int xRadius, int yRadius)
{
    auto add2Points = [](VPoints &result, int x, int y, int dx, int dy){
        result.emplace_back(x - dx, y + dy);
        result.emplace_back(x + dx, y + dy);
    };
    return drawEllipseUtil(center, xRadius, yRadius, add2Points);
}

VPoints drawHalfBotEllipse(const QPoint &center, int xRadius, int yRadius)
{
    auto add2Points = [](VPoints &result, int x, int y, int dx, int dy){
        result.emplace_back(x - dx, y - dy);
        result.emplace_back(x + dx, y - dy);
    };
    return drawEllipseUtil(center, xRadius, yRadius, add2Points);
}

VPoints drawEllipseUtil(const QPoint &center, int xRadius, int yRadius, void (*addPoint)(VPoints &, int, int, int, int))
{
    VPoints result;
    double dx, dy, d1, d2;
    int tx = 0, ty = yRadius;
    d1 = (yRadius * yRadius) - (xRadius * xRadius * yRadius) + (0.25 * xRadius * xRadius);
    dx = 2 * yRadius * yRadius * tx;
    dy = 2 * xRadius * xRadius * ty;
    while(dx < dy)
    {
        addPoint(result, center.x(), center.y(), tx, ty);
        if(d1 < 0)
        {
            ++tx;
            dx = dx + (2 * yRadius * yRadius);
            d1 = d1 + dx + (yRadius * yRadius);
        }
        else
        {
            ++tx;
            --ty;
            dx = dx + (2 * yRadius * yRadius);
            dy = dy - (2 * xRadius * xRadius);
            d1 = d1 + dx - dy + (yRadius * yRadius);
        }
    }
    d2 = ((yRadius * yRadius) * ((tx + 0.5) * (tx + 0.5))) +
        ((xRadius * xRadius) * ((ty - 1) * (ty - 1))) -
        (xRadius * xRadius * yRadius * yRadius);
    while(ty >= 0)
    {
        addPoint(result, center.x(), center.y(), tx, ty);
        if(d2 > 0)
        {
            --ty;
            dy = dy - (2 * xRadius * xRadius);
            d2 = d2 + (xRadius * xRadius) - dy;
        }
        else
        {
            --ty;
            ++tx;
            dx = dx + (2 * yRadius * yRadius);
            dy = dy - (2 * xRadius * xRadius);
            d2 = d2 + dx - dy + (xRadius * xRadius);
        }
    }
    std::sort(result.begin(), result.end());
    result.erase(std::unique(result.begin(), result.end()), result.end());
    return result;
}

VPoints drawRect(const QPoint &topLeft, const QPoint &topRight, const QPoint &bottomLeft, const QPoint &bottomRight)
{
    VPoints line1, line2, line3, line4;
    line1 = drawLine(topLeft.x(), topLeft.y(), topRight.x(), topRight.y());
    line2 = drawLine(topLeft.x(), topLeft.y(), bottomLeft.x(), bottomLeft.y());
    line3 = drawLine(bottomLeft.x(), bottomLeft.y(), bottomRight.x(), bottomRight.y());
    line4 = drawLine(topRight.x(), topRight.y(), bottomRight.x(), bottomRight.y());

    VPoints result;
    std::move(line1.begin(), line1.end(), std::back_inserter(result));
    std::move(line2.begin(), line2.end(), std::back_inserter(result));
    std::move(line3.begin(), line3.end(), std::back_inserter(result));
    std::move(line4.begin(), line4.end(), std::back_inserter(result));
    std::sort(result.begin(), result.end());
    result.erase(std::unique(result.begin(), result.end()), result.end());
    return result;
}



}
