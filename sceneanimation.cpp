#include "sceneanimation.h"
#include <iostream>

SceneAnimation::SceneAnimation(QWidget *parent)
    :Scene (parent), mt(std::random_device()())
{    
    setThickness(3);
    connect(&timer, SIGNAL(timeout()), this, SLOT(doAnimation()));
}

void SceneAnimation::play()
{
    file.close();
    file.open("animation.txt");
    timer.start(20);
}

void SceneAnimation::doAnimation()
{
    static int frame = 0;
    if (file.eof()) {
        timer.stop();
        clear();
        std::cerr << "Frame = " << frame << "\n";
        frame = 0;
    }
    ++frame;
    std::string command;
    while (file >> command && command != "STOP"){
        if (command == "ADD") add();
        else if (command == "TRANS") trans();
        else if (command == "ROTATE") rotate();
        else if (command == "SCALE") scale();
        else if (command == "REFLECT") reflect();
    }
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

void SceneAnimation::add()
{
    std::string objName, buff;
    file >> objName >> buff;
    if (buff == "LINE"){
        int x1, y1, x2, y2;
        string color;
        file >> x1 >> y1 >> x2 >> y2 >> color;
        Line *line = new Line(x1, y1, x2, y2, this);
        line->setBrush(QBrush(QColor(QString::fromStdString(color))));
        addItem(objs[objName] = line);
    } else if (buff == "RECT"){
        int x, y, w, h;
        string borderColor, fillColor;
        file >> x >> y >> w >> h >> borderColor >> fillColor;
        Rectangle *rect = new Rectangle(QPoint(x, y), QSize(w, h), this);
        rect->setBrush(QBrush(QColor(QString::fromStdString(borderColor))));
        rect->setFillColor(QColor(QString::fromStdString(fillColor)));
        addItem(objs[objName] = rect);
    } else if (buff == "CIRCLE"){
        int x, y, r;
        string borderColor, fillColor;
        file >> x >> y >> r >> borderColor >> fillColor;
        Circle *circle = new Circle(x, y, r, this);
        circle->setBrush(QBrush(QColor(QString::fromStdString(borderColor))));
        circle->setFillColor(QColor(QString::fromStdString(fillColor)));
        addItem(objs[objName] = circle);
    } else if (buff == "ELLIPSE"){
        int x, y, rx, ry;
        string borderColor, fillColor;
        file >> x >> y >> rx >> ry >> borderColor >> fillColor;
        Ellipse *ellipse = new Ellipse(x, y, rx, ry, this);
        ellipse->setBrush(QBrush(QColor(QString::fromStdString(borderColor))));
        ellipse->setFillColor(QColor(QString::fromStdString(fillColor)));
        addItem(objs[objName] = ellipse);
    } else exit(23);

}

void SceneAnimation::trans()
{
    string objName;
    int dx, dy;
    file >> objName >> dx >> dy;
    Scene::translateItem(objs[objName], dx, dy);
}

void SceneAnimation::rotate()
{
    string objName;
    int angle, x, y;
    file >> objName >> x >> y >> angle;
    Scene::rotateItem(objs[objName], x, y, angle);
}

void SceneAnimation::scale()
{
    string objName;
    float sx, sy;
    file >> objName >> sx >> sy;
    Scene::scaleItem(objs[objName], sy, sy);
}

void SceneAnimation::reflect()
{
    string objName;
    int x, y;
    file >> objName >> x >> y;
    Scene::reflectItem(objs[objName], x, y);
}

QPoint SceneAnimation::getRandPoint()
{
    return{
        std::uniform_int_distribution<int>(-offx, offx)(mt),
        std::uniform_int_distribution<int>(-offy, offy)(mt)
    };
}
