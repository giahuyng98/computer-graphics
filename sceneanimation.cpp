#include "sceneanimation.h"
#include <iostream>

SceneAnimation::SceneAnimation(QWidget *parent)
    :Scene (parent), mt(std::random_device()())
{
//    setThickness(3);
    connect(&timer, SIGNAL(timeout()), this, SLOT(doAnimation()));
}

void SceneAnimation::play()
{
    file.close();
    file.setFileName("animation.txt");
    stream.reset();
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        stream.setDevice(&file);
    } else {
        exit(20);
    }
    timer.start(20);
}

void SceneAnimation::doAnimation()
{
    static int frame = 0;

    if (stream.atEnd()) {
        timer.stop();
        clear();
        std::cerr << "Frame = " << frame << "\n";
        frame = 0;
    }
    ++frame;
    QString command;
    while (!stream.atEnd() && command != "STOP"){
        stream >> command;
        if (command == "ADD") add();
        else if (command == "TRANS") trans();
        else if (command == "ROTATE") rotate();
        else if (command == "SCALE") scale();
        else if (command == "REFLECT") reflect();
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

void SceneAnimation::add()
{
    QString objName, buff;
    stream >> objName >> buff;
    if (buff == "LINE"){
        int x1, y1, x2, y2;
        QString color;
        stream >> x1 >> y1 >> x2 >> y2 >> color;
        Line *line = new Line(x1, y1, x2, y2, this);
        line->setBrush(QBrush(QColor(color)));
        addItem(objs[objName] = line);
    } else if (buff == "RECT"){
        int x, y, w, h;
        QString borderColor, fillColor;
        stream >> x >> y >> w >> h >> borderColor >> fillColor;
        Rectangle *rect = new Rectangle(QPoint(x, y), QSize(w, h), this);
        rect->setBrush(QBrush(QColor(borderColor)));
        rect->setFillColor(QColor(fillColor));
        addItem(objs[objName] = rect);
    } else if (buff == "CIRCLE"){
        int x, y, r;
        QString borderColor, fillColor;
        stream >> x >> y >> r >> borderColor >> fillColor;
        Circle *circle = new Circle(x, y, r, this);
        circle->setBrush(QBrush(QColor(borderColor)));
        circle->setFillColor(QColor(fillColor));
        addItem(objs[objName] = circle);
    } else if (buff == "ELLIPSE"){
        int x, y, rx, ry;
        QString borderColor, fillColor;
        stream >> x >> y >> rx >> ry >> borderColor >> fillColor;
        Ellipse *ellipse = new Ellipse(x, y, rx, ry, this);
        ellipse->setBrush(QBrush(QColor(borderColor)));
        ellipse->setFillColor(QColor(fillColor));
        addItem(objs[objName] = ellipse);
    } else exit(23);

}

void SceneAnimation::trans()
{
    QString objName;
    int dx, dy;
    stream >> objName >> dx >> dy;
    Scene::translateItem(objs[objName], dx, dy);
}

void SceneAnimation::rotate()
{
    QString objName;
    int angle, x, y;
    stream >> objName >> x >> y >> angle;
    Scene::rotateItem(objs[objName], x, y, angle);
}

void SceneAnimation::scale()
{
    QString objName;
    float sx, sy;
    stream >> objName >> sx >> sy;
    Scene::scaleItem(objs[objName], sy, sy);
}

void SceneAnimation::reflect()
{
    QString objName;
    int x, y;
    stream >> objName >> x >> y;
    Scene::reflectItem(objs[objName], x, y);
}

QPoint SceneAnimation::getRandPoint()
{
    return{
        std::uniform_int_distribution<int>(-offx, offx)(mt),
        std::uniform_int_distribution<int>(-offy, offy)(mt)
    };
}
