#ifndef ITEM_H
#define ITEM_H
#include <QGraphicsItem>
#include <QTreeWidgetItem>

class Scene;

class Item : public QGraphicsItem{
public:
    enum Type{
        NULL_TYPE,
        LINE,
        RECT,
        CIRCLE,
        ELIP
    };
    QPainterPath getPath() const;
    Item(Scene *scene = nullptr, QGraphicsItem *parent = nullptr);
    virtual Type getType() const;
//    virtual QStringList getInfo() const;

    void setBrush(const QBrush &value);

protected:
    QPoint toScenePos(const QPoint &userPos) const;
    QBrush brush = QBrush(Qt::black);
    QPainterPath path;
    Scene *scene;
    QPainterPath shape() const override;
    void drawPixel(int x, int y);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};


#endif // ITEM_H
