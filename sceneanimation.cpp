#include "sceneanimation.h"

SceneAnimation::SceneAnimation(QWidget *parent)
    :Scene (parent), mt(std::random_device()())
{
    currentFrame = -50;
}

void SceneAnimation::play()
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(doAnimation()));
    timer.start(200);
}

void SceneAnimation::doAnimation()
{
    if (currentFrame == 100){
        currentFrame = 0;
        disconnect(&timer, SIGNAL(timeout()), this, SLOT(doAnimation()));
        timer.stop();
        return;
    }
    ++currentFrame;
    clear();
    addItem(new Line(getRandPoint(), getRandPoint(), this));
}

QPoint SceneAnimation::getRandPoint()
{
    return{
        std::uniform_int_distribution<int>(-offx, offx)(mt),
        std::uniform_int_distribution<int>(-offy, offy)(mt)
    };
}
