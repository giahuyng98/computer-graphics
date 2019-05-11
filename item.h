#ifndef ITEM_H
#define ITEM_H
#include <QGraphicsItem>
#include <QTreeWidgetItem>

class Item : public QGraphicsItem, public QTreeWidgetItem{
protected:
    QPainterPath path;
    QPainterPath shape() const override;
    void drawPixel(int x, int y);

};


#endif // ITEM_H
