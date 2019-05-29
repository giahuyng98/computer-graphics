#include "frameparser.h"

FrameParser::FrameParser(Scene *scene) : scene(scene)
{
    out.setString(&outStream);
}

FrameParser::FrameParser(Scene *scene, const QString &fileName)
    :FrameParser(scene)
{
    setInputFile(fileName);
}

bool FrameParser::setInputFile(const QString &fileName)
{
    if (inFile.isOpen()){
        int code = QMessageBox(QMessageBox::Icon::Information, "Information", "There is opening file\n Do you want to continue?",
                    QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No).exec();
        if (!code){
            return false;
        }
        inFile.close();
    }
    scene->clear();
    outStream.clear();
    out.reset();
    objs.clear();
    out.reset();
    outStream.clear();
    inFile.setFileName(fileName);
    if (inFile.open(QIODevice::ReadOnly)){
        in.setDevice(&inFile);
        return true;
    }
    return false;
}

QString FrameParser::getOutPut()
{
    out.flush();
    return outStream;
}

bool FrameParser::nextFrame()
{
    out << "STOP\n";
    if (in.atEnd()) return false;
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
    return true;
}

void FrameParser::removeObj(Item *item)
{
    for(auto it = objs.begin(); it != objs.end(); ++it){
        if (it->second == item){
//            this->scene->removeItem(it->second);
            delete it->second;
            objs.erase(it);
        }
    }
}

void FrameParser::reset()
{
    inFile.reset();
    in.reset();
    objs.clear();
    out.reset();
    outStream.clear();    
}

void FrameParser::add()
{
    QString objName, buff;
    in >> objName >> buff;
    auto it = objs.find(objName);
    if (it != objs.end()){
        objs.erase(it);
        scene->removeItem(it->second);
        delete it->second;
    }
    if (buff == "LINE"){
        int x1, y1, x2, y2;
        QString color;
        in >> x1 >> y1 >> x2 >> y2 >> color;
        Item *line = new Line(x1, y1, x2, y2, scene);
        line->setBrush(QBrush(QColor(color)));
        outPutItem(line);
        scene->addItem(objs[objName] = line);
    } else if (buff == "RECT"){
        int x, y, w, h;
        QString borderColor, fillColor;
        in >> x >> y >> w >> h >> borderColor >> fillColor;
        Rectangle *rect = new Rectangle(QPoint(x, y), QSize(w, h), scene);
        rect->setBrush(QBrush(QColor(borderColor)));
        rect->setFillColor(QColor(fillColor));
        outPutItem(rect);
        scene->addItem(objs[objName] = static_cast<Item*>(rect));
    } else if (buff == "CIRCLE"){
        int x, y, r;
        QString borderColor, fillColor;
        in >> x >> y >> r >> borderColor >> fillColor;
        Circle *circle = new Circle(x, y, r, scene);
        circle->setBrush(QBrush(QColor(borderColor)));
        circle->setFillColor(QColor(fillColor));
        outPutItem(circle);
        scene->addItem(objs[objName] = static_cast<Item*>(circle));
    } else if (buff == "ELLIPSE"){
        int x, y, rx, ry;
        QString borderColor, fillColor;
        in >> x >> y >> rx >> ry >> borderColor >> fillColor;
        Ellipse *ellipse = new Ellipse(x, y, rx, ry, scene);
        ellipse->setBrush(QBrush(QColor(borderColor)));
        ellipse->setFillColor(QColor(fillColor));
        outPutItem(ellipse);
        scene->addItem(objs[objName] = static_cast<Item*>(ellipse));
    }
}

void FrameParser::trans()
{
    QString objName;
    int dx, dy;
    in >> objName >> dx >> dy;
    auto it = objs.find(objName);
    if (it != objs.end() && scene->items().contains(it->second)){
        scene->translateItem(it->second, dx, dy);
        outPutTranslation(it->second, dx, dy);
    }
}

void FrameParser::rotate()
{
    QString objName;
    int angle, x, y;
    in >> objName >> x >> y >> angle;
    auto it = objs.find(objName);
    if (it != objs.end() && scene->items().contains(it->second)){
        scene->rotateItem(it->second, x, y, angle);
        outPutRotation(it->second, x, y, angle);
    }
}

void FrameParser::scale()
{
    QString objName;
    float sx, sy;
    in >> objName >> sx >> sy;
    auto it = objs.find(objName);
    if (it != objs.end() && scene->items().contains(it->second)){
        scene->scaleItem(it->second, sx, sy);
        outPutScaling(it->second, sx, sy);
    }
}

void FrameParser::reflect()
{
    QString objName;
    int x, y;
    in >> objName >> x >> y;
    auto it = objs.find(objName);
    if (it != objs.end() && scene->items().contains(it->second)){
        scene->reflectItem(it->second, x, y);
        outPutReflection(it->second, x, y);
    }
}

void FrameParser::doDelete()
{
    QString objName;
    in >> objName;
    auto it = objs.find(objName);
    if (it != objs.end() && scene->items().contains(it->second)) {
        outPutDeletion(it->second);        
        scene->removeItem(it->second);
        scene->items().removeOne(it->second);
        delete it->second;
        objs.erase(it);
    }
}

void FrameParser::doClear()
{
    for(auto &it : scene->items()){
        scene->removeItem(it);
        delete it;
        it = nullptr;
    }
    objs.clear();
    scene->clear();
}

void FrameParser::changeColor()
{
    QString objName, colorName;
    in >> objName >> colorName;
    auto it = objs.find(objName);
    if (it != objs.end() && scene->items().contains(it->second)){
        scene->changeColor(it->second, QColor(colorName));
        outPutChangeColor(it->second, QColor(colorName));
    }
}

void FrameParser::fillColor()
{
    QString objName, colorName;
    in >> objName >> colorName;
    auto it = objs.find(objName);
    if (it != objs.end() && scene->items().contains(it->second)){
        scene->changeFillColor(it->second, QColor(colorName));
        outPutFillColor(it->second, QColor(colorName));
    }
}

void FrameParser::outPutItem(Item *item)
{
    if (!item) return;
    out << "ADD ";
    switch (static_cast<Item*>(item)->getType()) {
    case Item::Type::LINE:
    {
        Line *line = static_cast<Line*>(item);
        out << item << " LINE " << line->getX1() << " "
            << line->getY1() << " "<< line->getX2() << " "
            << line->getY2() << " " << line->getColor().name();
        break;
    }
    case Item::Type::RECT:
    {
        Rectangle *rect = static_cast<Rectangle*>(item);
        out << item << " RECT " << rect->getTopLeft().x() << " "
            << rect->getTopLeft().y() << " "
            << rect->getWidth() << " " << rect->getHeight() << " "
            << rect->getColor().name() << " " << rect->getFillColor().name();

        break;
    }
    case Item::Type::CIRCLE:
    {
        Circle *circle = static_cast<Circle*>(item);
        out << item << " CIRCLE " << circle->getX() << " "
            << circle->getY() << " " << circle->getR() << " "
            << circle->getColor().name() << " " << circle->getFillColor().name();
        break;
    }
    case Item::Type::ELLIPSE:
    {
        Ellipse *ellipse = static_cast<Ellipse*>(item);
        out << item << " ELLIPSE " << ellipse->getX() << " "
            << ellipse->getY() << " " << ellipse->getXRadius() << " "
            << ellipse->getYRadius() << " "
            << ellipse->getColor().name() << " " << ellipse->getFillColor().name();
        break;
    }
    default:
        break;
    }
    out << "\n";
}

void FrameParser::outPutTranslation(Item *item, int dx, int dy)
{
    out << "TRANS " << item << " " << dx << " " << dy << "\n";
}

void FrameParser::outPutRotation(Item *item, int x, int y, int angle)
{
    out << "ROTATE " << item << " " << x << " " << y
        << " " << angle << "\n";
}

void FrameParser::outPutScaling(Item *item, float sx, float sy)
{
    out << "SCALE " << item << " " << sx << " " << sy << "\n";
}

void FrameParser::outPutReflection(Item *item, int x, int y)
{
    out << "REFLECT " << item << " " << x << " " << y << "\n";
}

void FrameParser::outPutDeletion(Item *item)
{
    out << "DELETE " << item << "\n";
}

void FrameParser::outPutClear()
{
    out << "CLEAR\n";
}

void FrameParser::outPutChangeColor(Item *item, const QColor &color)
{
    out << "CHCOLOR " << item << " " << color.name() << "\n";
}

void FrameParser::outPutFillColor(Item *item, const QColor &color)
{
    out << "FILLCOLOR " << item << " " << color.name() << "\n";
}

void FrameParser::outPutAddition()
{
    out << "STOP\n";
}
