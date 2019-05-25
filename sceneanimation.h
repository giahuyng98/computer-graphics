#ifndef SCENEANIMATION_H
#define SCENEANIMATION_H

#include "scene.h"
#include <QTimer>
#include <random>
#include <string>
#include <fstream>
#include <map>

class Window;

class SceneAnimation : public Scene
{
    Q_OBJECT

public:
    explicit SceneAnimation(QWidget *parent = nullptr);

    void play();


private slots:
    void doAnimation();

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void wheelEvent(QGraphicsSceneWheelEvent *wheelEvent) override;

    void add();
    void trans();
    void rotate();
    void scale();
    void reflect();

private:
    std::ifstream file;
    QPoint getRandPoint();
    std::map<std::string, Item*> objs;
    std::mt19937 mt;
    QTimer timer;    
};

#endif // SCENEANIMATION_H
