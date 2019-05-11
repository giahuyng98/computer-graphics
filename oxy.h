#ifndef OXY_H
#define OXY_H

#include <QWidget>
#include <QPainter>
#include <QResizeEvent>
#include <QDebug>
#include <vector>
#include <iostream>

using std::vector;
using std::cerr;
using std::endl;

enum LINE_TYPE{
    SOLID

};

class Oxy : public QWidget
{
    Q_OBJECT
public:
    explicit Oxy(QWidget *parent = nullptr);
//    Oxy(){};
//    Oxy(int width, int height);
//    void setUp(const QSize &size);
//    int getLenX();
//    int getLenY();
    void putPixel(int x, int y, const QColor &color = Qt::black);
    void drawLine(int x1, int y1, int x2, int y2);

private:
    void draw(QPainter *painter);
    void drawCoordinate(QPainter *painter);
    void drawLineLow(int x1, int y1, int x2, int y2);
    void drawLineHigh(int x1, int y1, int x2, int y2);

protected:

    int thick;
    int rows, cols;
    int offx, offy;
    vector<vector<QColor>> mat;
    QColor pixColor;
    void paintEvent(QPaintEvent *event) override;
//    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

};

#endif // OXY_H
