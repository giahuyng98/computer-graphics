#ifndef ITEMS_H
#define ITEMS_H

#include <array>
#include <string>
#include <vector>
#include <utility>
#include <QTreeWidgetItem>
#include <QGraphicsItemGroup>
#include <QGraphicsItem>
#include <QString>
using std::array;
using std::string;
using std::vector;

using m3 = array<int, 3>;
using m4 = array<int, 4>;

//class Base{
//public:
//    virtual string write();
//};

//class Point {
//    m3 data;
//public:
////    string write() override {};
//    Point(int x = 0, int y = 0, int t = 1) : data{x, y, t}{}
////    QTreeWidget* info(){return new QTreeWidgetItem()}
//    void showInfo(QTreeWidgetItem *root) const {
//        root->addChild(new QTreeWidgetItem({"Point", "(" + QString::number(x()) + ", " + QString::number(y()) + ")"}));
//    }
//    bool operator==(const Point &another){return std::make_tuple(x(), y()) == std::make_tuple(another.x(), another.y());}
//    bool operator!=(const Point &another){return !(*this == another);}
//    int &x() {return data[0];}
//    int &y() {return data[1];}
//    int x() const {return data[0];}
//    int y() const {return data[1];}
//};





//class Line{
//    Point p1, p2;
//    QGraphicsItem *gitem;
//    QTreeWidgetItem *titem;
//public:
//    Line(const Point &p1, const Point &p2) : p1(p1), p2(p2) {}
//    void showInfo(QTreeWidgetItem *root) const {
//        root->setText(0, "Line");
//        p1.showInfo(root);
//        p2.showInfo(root);
//    }
//    const Point first() const {return p1;}
//    const Point second() const {return p2;}
//};




#endif // ITEMS_H
