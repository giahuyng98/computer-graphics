#ifndef ITEM_H
#define ITEM_H
#include <QGraphicsItem>
#include <QTreeWidgetItem>

class Scene;

class Item : public QGraphicsItem{
public:
    enum Type{
        LINE,
        RECT
    };
    QPainterPath getPath() const;
    Item(Scene *scene = nullptr, QGraphicsItem *parent = nullptr);
    virtual QStringList getInfo() const;

    void setBrush(const QBrush &value);

protected:
    QPoint toScenePos(const QPoint &userPos) const;
    QBrush brush = QBrush(Qt::black);
    QPainterPath path;
    Scene *scene;
    QPainterPath shape() const override;
    void drawPixel(int x, int y);
};


#endif // ITEM_H
