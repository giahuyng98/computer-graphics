#ifndef ITEM_H
#define ITEM_H
#include <QGraphicsItem>
#include <QTreeWidgetItem>

class Scene;

class Item : public QGraphicsItem{
public:
    enum Type{        
        LINE,
        RECT,
        CIRCLE,
        ELLIPSE,
        INVALID
    };

    Item(Scene *scene = nullptr, QGraphicsItem *parent = nullptr);
    virtual Type getType() const {return INVALID;}
    virtual QColor getFillColor() const;
    void setBrush(const QBrush &value);
    QColor getColor() const;

protected:
    QPoint toScenePos(const QPoint &userPos) const;
    QBrush brush = QBrush(Qt::black);
    QPainterPath path;
    Scene *scene;

    QPainterPath shape() const override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void drawPixel(int x, int y);
    void drawPixel(const QPoint &p);
    void drawPixel(int x, int y, QPainterPath &painterPath);
    void drawPixel(const QPoint &p, QPainterPath &painterPath);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};


#endif // ITEM_H
