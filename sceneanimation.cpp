#include "sceneanimation.h"
#include <iostream>
#include "window.h"

SceneAnimation::SceneAnimation(QWidget *parent)
    :Scene (parent)
{
//    setThickness(3);
    setItemIndexMethod(QGraphicsScene::ItemIndexMethod::NoIndex);
    parser = new FrameParser(this);
    connect(&timer, SIGNAL(timeout()), this, SLOT(doAnimation()));
}

void SceneAnimation::open(const QString &fileName)
{
    if (fileName.isEmpty()) return;
    if (!parser->setInputFile(fileName)){
        QMessageBox(QMessageBox::Icon::Critical, "ERROR", "BUG BUG BUG").exec();
        return;
    }
    window->setOpenFileName(fileName.split("/").back());
}

void SceneAnimation::play()
{
    parser->reset();
    this->clear();
    timer.start(window->getDelay());
}

void SceneAnimation::doAnimation()
{
    if (!parser->nextFrame()) {
        timer.stop();
        if (!window->isPauseAtEnd()) clear();
        parser->reset();
        return;
    }
}

void SceneAnimation::drawBackground(QPainter *painter, const QRectF &rect)
{
    Scene::drawBackground(painter, rect);
//    Q_UNUSED(rect);
//    int halfHeight = static_cast<int>(this->height()) / 2;
//    int halfWidth = static_cast<int>(this->width()) / 2;
//    const int halfThick = thickness / 2; //make it center

//    // Draw ox and oy
//    painter->setPen(QPen(QBrush(Qt::black), 1));
//    painter->setOpacity(0.6);
//    painter->drawLine(0, halfHeight + halfThick, static_cast<int>(this->width()), halfHeight + halfThick);
//    painter->drawLine(halfWidth + halfThick, 0, halfWidth + halfThick, static_cast<int>(this->height()));
}

void SceneAnimation::wheelEvent(QGraphicsSceneWheelEvent *wheelEvent)
{
    QGraphicsScene::wheelEvent(wheelEvent);
}
