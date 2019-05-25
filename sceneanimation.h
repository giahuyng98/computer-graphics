#ifndef SCENEANIMATION_H
#define SCENEANIMATION_H

#include "scene.h"
#include <QTimer>
#include <random>

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

private:
    QPoint getRandPoint();

    std::mt19937 mt;
    QTimer timer;
    int currentFrame;
};

#endif // SCENEANIMATION_H
