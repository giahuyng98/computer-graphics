#ifndef SCENE2D_H
#define SCENE2D_H

#include "scene.h"
#include "lineinfo.h"
#include "rectinfo.h"
#include "circleinfo.h"
#include "ellipseinfo.h"

class Window;

class Scene2D : public Scene
{
    Q_OBJECT
public:
    explicit Scene2D(QWidget *parent = nullptr);

    void toTextFile();

    void doChangeColor(const QColor &color);

    void doFillColor(const QColor &color);

    void deleteItem();

    void clearAll();

    void doTranslation();

    void doRotation();

    void doScaling();

    void doReflection();

    void updateInfo(Item *item);

    void setThickness(int value) override;

    void addScene();

    RectInfo *getRectInfo() const;

    LineInfo *getLineInfo() const;

    CircleInfo *getCircleInfo() const;

    EllipseInfo *getEllipseInfo() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void outPutItem(Item *item);

private:
    QFile tmpFile;
    QTextStream out;
    bool isDrawing = false;
    Line *tmpLine = nullptr;
    Rectangle *tmpRectange = nullptr;
    Circle *tmpCircle = nullptr;
    Ellipse *tmpEllipse = nullptr;
    LineInfo *lineInfo;
    RectInfo *rectInfo;
    CircleInfo *circleInfo;
    EllipseInfo *ellipseInfo;
    std::vector<QPoint> points;
};

#endif // SCENE2D_H
