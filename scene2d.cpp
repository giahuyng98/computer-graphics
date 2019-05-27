#include "scene2d.h"
#include "item.h"
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QTextItem>
#include <QPoint>
#include <QFileDialog>
#include <QCoreApplication>
#include "window.h"

Scene2D::Scene2D(QWidget *parent) : Scene(parent)
{
    lineInfo = new LineInfo();
    rectInfo = new RectInfo();
    circleInfo = new CircleInfo();
    ellipseInfo = new EllipseInfo();
    tmpFile.setFileName("tmp.txt");
    if (tmpFile.open(QFile::WriteOnly | QFile::Truncate)){
        out.setDevice(&tmpFile);
    } else {
        QMessageBox(QMessageBox::Icon::Critical, "Error", "Can't load app").exec();
        return;
    }
}

void Scene2D::toTextFile()
{
    out.flush();
    QString outFileName = QFileDialog(window, "Save to file",
                                  QCoreApplication::applicationDirPath()).getSaveFileName();
    if (QFile::exists(outFileName))
        QFile::remove(outFileName);        

    if (!QFile::copy(tmpFile.fileName(), outFileName)){
        QMessageBox(QMessageBox::Icon::Critical, "Error", "Can't save file: " + outFileName).exec();
    } else {
//        QFile::remove(tmpFile.fileName());
    }
}

void Scene2D::doChangeColor(const QColor &color)
{
    for(auto &it : this->selectedItems()){
        Item *item = static_cast<Item*>(it);
        out << "CHCOLOR " << item << " " << color.name() << "\n";
        changeColor(item, color);
    }
}

void Scene2D::doFillColor(const QColor &color)
{
    for(auto &it : this->selectedItems()){
        Item *item = static_cast<Item*>(it);
        out << "FILLCOLOR " << item << " " << color.name() << "\n";
        changeFillColor(item, color);
    }
}

void Scene2D::deleteItem()
{
    for(auto &it : this->selectedItems()){
        Item *item = static_cast<Item*>(it);
        out << "DELETE " << item << "\n";
        removeItem(item);
    }


    if (!this->items().isEmpty()) {
        Item *item = static_cast<Item*>(this->items().first());
        item->setSelected(true);
        window->setEnableFillButton(item->getType() != Item::Type::LINE);
        updateInfo(item);
    } else {
        lineInfo->setLine(nullptr);
        rectInfo->setRect(nullptr);
        circleInfo->setCircle(nullptr);
        ellipseInfo->setEllipse(nullptr);
    }

}

void Scene2D::clearAll()
{
    out << "CLEAR\n";
    this->clear();
    lineInfo->setLine(nullptr);
    rectInfo->setRect(nullptr);
    circleInfo->setCircle(nullptr);
    ellipseInfo->setEllipse(nullptr);
}

void Scene2D::doTranslation()
{
    for(auto &it : selectedItems()){
        Item *selectedItem = static_cast<Item*>(it);
        if (selectedItem){
            out << "TRANS " << selectedItem << " " << window->getDxTrans() << " " << window->getDyTrans() << "\n";
            translateItem(selectedItem, window->getDxTrans(), window->getDyTrans());
            updateInfo(selectedItem);
        }
    }
}

void Scene2D::doRotation()
{
    for(auto &it : selectedItems()){
        Item *selectedItem = static_cast<Item*>(it);
        if (selectedItem){
            out << "ROTATE " << selectedItem << " " << window->getXRotate() << " " << window->getYRotate()
                << " " << window->getAngleRotate() << "\n";
            rotateItem(selectedItem, window->getXRotate(), window->getYRotate(), window->getAngleRotate());
            updateInfo(selectedItem);
        }
    }
}

void Scene2D::doScaling()
{
    for(auto &it : selectedItems()){
        Item *selectedItem = static_cast<Item*>(it);
        if (selectedItem){
            out << "SCALE " << selectedItem << " " << window->getSXScale()<< " " << window->getSYScale() << "\n";
            scaleItem(selectedItem, window->getSXScale(), window->getSYScale());
            updateInfo(selectedItem);
        }
    }
}

void Scene2D::doReflection()
{    
    for(auto &it : selectedItems()){
        Item *selectedItem = static_cast<Item*>(it);
        if (selectedItem){
            out << "REFLECT " << selectedItem << " " <<  window->getXReflection() << " " << window->getYReflection() << "\n";
            reflectItem(selectedItem, window->getXReflection(), window->getYReflection());
            updateInfo(selectedItem);
        }
    }
}

void Scene2D::updateInfo(Item *item)
{
    if (!item) return;
    switch (item->getType()) {
    case Item::Type::LINE:
        window->setMode(Window::Mode::DRAW_LINE);
        lineInfo->setLine(static_cast<Line*>(item));
        break;
    case Item::Type::RECT:
        window->setMode(Window::Mode::DRAW_RECT);
        rectInfo->setRect(static_cast<Rectangle*>(item));
        break;
    case Item::Type::CIRCLE:
        window->setMode(Window::Mode::DRAW_CIRCLE);
        circleInfo->setCircle(static_cast<Circle*>(item));
        break;
    case Item::Type::ELLIPSE:
        window->setMode(Window::Mode::DRAW_CIRCLE);
        ellipseInfo->setEllipse(static_cast<Ellipse*>(item));
        break;
    default:
        break;
    }
}

void Scene2D::setThickness(int value)
{
    Scene::setThickness(value);
    for(auto &item : this->items()){
        switch (static_cast<Item*>(item)->getType()) {
        case Item::Type::LINE:
            static_cast<Line*>(item)->reDraw();
            break;
        case Item::Type::RECT:
            static_cast<Rectangle*>(item)->reDraw();
            break;
        case Item::Type::CIRCLE:
            static_cast<Circle*>(item)->reDraw();
            break;
        case Item::Type::ELLIPSE:
            static_cast<Ellipse*>(item)->reDraw();
            break;
        default: break;
        }
    }
    update();
}

void Scene2D::addScene()
{
    out << "STOP\n";
    out.flush();
}

void Scene2D::addItemFrom2Points(const QPoint &p1, const QPoint &p2)
{
    if (tmpItem){
        removeItem(tmpItem);
        tmpItem = nullptr;
    }
    if (tmpSelected){
        removeItem(tmpSelected);
        tmpSelected = nullptr;
    }
    switch (window->getMode()){
    case Window::Mode::DRAW_LINE :
        tmpItem = new Line(p1, p2, this);
        break;
    case Window::Mode::DRAW_RECT :
        tmpItem = new Rectangle(QPoint(std::min(p1.x(), p2.x()), std::max(p1.y(), p2.y())),
                                QSize(std::abs(p2.x() - p1.x()), std::abs(p2.y() - p1.y())), this);
        break;
    case Window::Mode::DRAW_CIRCLE :
        tmpItem = new Circle(p1.x(), p1.y(),
                             Drawer::dist(p1, p2), this);
        break;
    case Window::Mode::DRAW_ELLIPSE :
        tmpItem = new Ellipse(p1.x(), p1.y(),
                              std::abs(p2.x() - p1.x()),
                              std::abs(p2.y() - p1.y()), this);
        break;
    case Window::Mode::SELECT_ITEMS:
    {
        QPoint sceneP1 = toScenePos(p1);
        QPoint sceneP2 = toScenePos(p2);
        tmpSelected = new QGraphicsRectItem(
            std::min(sceneP1.x(), sceneP2.x()),
            std::min(sceneP1.y(), sceneP2.y()),
            std::abs(sceneP1.x() - sceneP2.x()),
            std::abs(sceneP1.y() - sceneP2.y())
            );
        tmpSelected->setPen(QPen(Qt::black, 1, Qt::DashLine));
        addItem(tmpSelected);
        setSelectionArea(tmpSelected->shape());
        tmpSelected->setSelected(false);
        return;
    }
    }
    addItem(tmpItem);
    tmpItem->setSelected(true);
    updateInfo(tmpItem);
    window->setEnableFillButton(tmpItem->getType() != Item::Type::LINE);
}

void Scene2D::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    points.clear();
    if (mouseEvent->button() == Qt::LeftButton){
        points.emplace_back(toUserCoordinate(mouseEvent->scenePos()));
        points.emplace_back(toUserCoordinate(mouseEvent->scenePos()));
        if (window->getMode() == Window::Mode::SELECT_ITEMS){
            Item *selectedItem = static_cast<Item*>(this->itemAt(mouseEvent->scenePos(), QTransform()));
            if (selectedItem){
                updateInfo(selectedItem);
                window->setEnableFillButton(selectedItem->getType() != Item::Type::LINE);
                if (!(mouseEvent->modifiers() & Qt::ControlModifier)){
                    clearSelection();
                }
                selectedItem->setSelected(true);
            }
        } else {
            clearSelection();
            addItemFrom2Points(points.front(), points.back());
        }
    }
//    QGraphicsScene::mousePressEvent(mouseEvent);
}

void Scene2D::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (tmpSelected) removeItem(tmpSelected);
    else outPutItem(tmpItem);
    tmpItem = nullptr;
    tmpSelected = nullptr;
    points.clear();
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void Scene2D::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    points.pop_back();
    points.emplace_back(toUserCoordinate(mouseEvent->scenePos()));
    addItemFrom2Points(points.front(), points.back());
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void Scene2D::outPutItem(Item *item)
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

EllipseInfo *Scene2D::getEllipseInfo() const
{
    return ellipseInfo;
}

CircleInfo *Scene2D::getCircleInfo() const
{
    return circleInfo;
}

LineInfo *Scene2D::getLineInfo() const
{
    return lineInfo;
}

RectInfo *Scene2D::getRectInfo() const
{
    return rectInfo;
}

