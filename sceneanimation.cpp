#include "sceneanimation.h"

SceneAnimation::SceneAnimation(QWidget *parent)
    :Scene (parent), mt(std::random_device()())
{
    currentFrame = -50;
}

void SceneAnimation::play()
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(doAnimation()));
    timer.start(20);
}

void SceneAnimation::doAnimation()
{
    if (currentFrame == 100){
        currentFrame = 0;        
        timer.stop();
        return;
    }
    ++currentFrame;
    clear();
    addItem(new Line(getRandPoint(), getRandPoint(), this));
}

void SceneAnimation::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);
    int halfHeight = static_cast<int>(this->height()) / 2;
    int halfWidth = static_cast<int>(this->width()) / 2;
    const int halfThick = thickness / 2; //make it center

    // Draw ox and oy
    painter->setPen(QPen(QBrush(Qt::black), 1));
    painter->setOpacity(0.6);
    painter->drawLine(0, halfHeight + halfThick, static_cast<int>(this->width()), halfHeight + halfThick);
    painter->drawLine(halfWidth + halfThick, 0, halfWidth + halfThick, static_cast<int>(this->height()));
}

void SceneAnimation::wheelEvent(QGraphicsSceneWheelEvent *wheelEvent)
{
    QGraphicsScene::wheelEvent(wheelEvent);
}

QPoint SceneAnimation::getRandPoint()
{
    return{
        std::uniform_int_distribution<int>(-offx, offx)(mt),
        std::uniform_int_distribution<int>(-offy, offy)(mt)
    };
}
