#include "sceneanimation.h"
#include <iostream>
#include "window.h"

SceneAnimation::SceneAnimation(QWidget *parent)
    :Scene (parent), mt(std::random_device()())
{
//    setThickness(3);
    connect(&timer, SIGNAL(timeout()), this, SLOT(doAnimation()));
}

void SceneAnimation::open(const QString &fileName)
{
    if (fileName.isEmpty()) return;
    file.close();
    file.setFileName(fileName);
}

void SceneAnimation::play()
{
    file.close();
    in.reset();
    clear();
    objs.clear();
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        in.setDevice(&file);
        window->setOpenFileName(file.fileName());
    } else {
        QMessageBox(QMessageBox::Icon::Critical, "Error", "Can't open file: " + file.fileName()).exec();
        return;
    }
    timer.start(window->getDelay());
}

void SceneAnimation::doAnimation()
{    
    if (in.atEnd()) {
        timer.stop();
        if (!window->isPauseAtEnd()) clear();
        update();
        objs.clear();        
        return;
    }    
    QString command;
    while (!in.atEnd() && command != "STOP"){
        in >> command;
        if (command == "ADD") add();
        else if (command == "TRANS") trans();
        else if (command == "ROTATE") rotate();
        else if (command == "SCALE") scale();
        else if (command == "REFLECT") reflect();
        else if (command == "DELETE") doDelete();
        else if (command == "CLEAR") doClear();
        else if (command == "CHCOLOR") changeColor();
        else if (command == "FILLCOLOR") fillColor();
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
    in >> objName >> buff;
    auto it = objs.find(objName);
    if (it != objs.end()){
        objs.erase(it);
        removeItem(it->second);
    }
    if (buff == "LINE"){
        int x1, y1, x2, y2;
        QString color;
        in >> x1 >> y1 >> x2 >> y2 >> color;
        Item *line = new Line(x1, y1, x2, y2, this);
        line->setBrush(QBrush(QColor(color)));
        addItem(objs[objName] = line);
    } else if (buff == "RECT"){
        int x, y, w, h;
        QString borderColor, fillColor;
        in >> x >> y >> w >> h >> borderColor >> fillColor;
        Rectangle *rect = new Rectangle(QPoint(x, y), QSize(w, h), this);
        rect->setBrush(QBrush(QColor(borderColor)));
        rect->setFillColor(QColor(fillColor));
        addItem(objs[objName] = static_cast<Item*>(rect));
    } else if (buff == "CIRCLE"){
        int x, y, r;
        QString borderColor, fillColor;
        in >> x >> y >> r >> borderColor >> fillColor;
        Circle *circle = new Circle(x, y, r, this);
        circle->setBrush(QBrush(QColor(borderColor)));
        circle->setFillColor(QColor(fillColor));
        addItem(objs[objName] = static_cast<Item*>(circle));
    } else if (buff == "ELLIPSE"){
        int x, y, rx, ry;
        QString borderColor, fillColor;
        in >> x >> y >> rx >> ry >> borderColor >> fillColor;
        Ellipse *ellipse = new Ellipse(x, y, rx, ry, this);
        ellipse->setBrush(QBrush(QColor(borderColor)));
        ellipse->setFillColor(QColor(fillColor));
        addItem(objs[objName] = static_cast<Item*>(ellipse));
    }
}

void SceneAnimation::trans()
{
    QString objName;
    int dx, dy;
    in >> objName >> dx >> dy;
    Scene::translateItem(objs[objName], dx, dy);
}

void SceneAnimation::rotate()
{
    QString objName;
    int angle, x, y;
    in >> objName >> x >> y >> angle;
    Scene::rotateItem(objs[objName], x, y, angle);
}

void SceneAnimation::scale()
{
    QString objName;
    float sx, sy;
    in >> objName >> sx >> sy;
    Scene::scaleItem(objs[objName], sx, sy);
}

void SceneAnimation::reflect()
{
    QString objName;
    int x, y;
    in >> objName >> x >> y;
    Scene::reflectItem(objs[objName], x, y);
}

void SceneAnimation::doDelete()
{
    QString objName;
    in >> objName;
    auto it = objs.find(objName);
    if (it != objs.end() && it->second) {
        objs.erase(it);
        removeItem(it->second);
    }

//    removeItem(objs[objName]);
//    delete objs[objName];
}

void SceneAnimation::doClear()
{
    for(auto &it : items()){
//        delete it;
        removeItem(it);
    }
    objs.clear();
}

void SceneAnimation::changeColor()
{
    QString objName, colorName;
    in >> objName >> colorName;
    Scene::changeColor(objs[objName], QColor(colorName));
}

void SceneAnimation::fillColor()
{
    QString objName, colorName;
    in >> objName >> colorName;
    Scene::changeFillColor(objs[objName], QColor(colorName));
}

//QPoint SceneAnimation::getRandPoint()
//{
//    return{
//        std::uniform_int_distribution<int>(-offx, offx)(mt),
//        std::uniform_int_distribution<int>(-offy, offy)(mt)
//    };
//}
