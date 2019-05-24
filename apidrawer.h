#ifndef APIDRAWER_H
#define APIDRAWER_H

#include <QPoint>
#include <QSize>
#include <vector>
#include <algorithm>
#include <cmath>
const float CAVALIER = 0.70710678118654752440084436210485f;
const float CABINET = 0.70710678118654752440084436210485f / 2.f;

namespace Drawer{
using std::vector;
using VPoints = vector<QPoint>;
int sqr(int num);
int dist(const QPoint &p1, const QPoint &p2);
QPoint cabinet(int x, int y, int z);
QPoint cavalier(int x, int y, int z);
VPoints drawLine(int x1, int y1, int x2, int y2);
VPoints drawLine(const QPoint &from, const QPoint &to);
VPoints drawDashedLine(const QPoint &from, const QPoint &to, int dash, int dot);
VPoints drawRect(const QPoint &topLelf, const QSize &size);
VPoints drawRect(const QPoint &topLeft, const QPoint &topRight,const QPoint &bottomLeft, const QPoint &bottomRight);
VPoints drawCircle(const QPoint &center, int radius);
VPoints drawHalfTopEllipse(const QPoint &center, int xRadius, int yRadius);
VPoints drawHalfBotEllipse(const QPoint &center, int xRadius, int yRadius);
VPoints drawEllipse(const QPoint &center, int xRadius, int yRadius);
VPoints drawCube(int x, int y, int z, int width, int height, int length, QPoint (*method)(int, int, int) = cavalier);
VPoints drawSphere(int x, int y, int z, int r, QPoint (*method)(int, int, int) = cavalier);
VPoints floodFill(const VPoints &border, const QPoint &point);
VPoints toDashDot(const VPoints &points, int dash, int dot);

VPoints drawEllipseUtil(const QPoint &center, int xRadius, int yRadius, void (*addPoint)(VPoints&, int, int, int, int)) ;
};


#endif // APIDRAWER_H
