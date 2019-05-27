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
#include "frameparser.h"

Scene2D::Scene2D(QWidget *parent) : Scene(parent)
{
    parser = new FrameParser(this);
    lineInfo = new LineInfo();
    rectInfo = new RectInfo();
    circleInfo = new CircleInfo();
    ellipseInfo = new EllipseInfo();    
}

void Scene2D::readTextFile(const QString &fileName)
{
    if (!parser->setFile(fileName)) exit(43);
}

bool Scene2D::nextFrame()
{
    if (!parser->nextFrame()){
//        QFile test("huy.txt");
//        test.write(parser->getOutPut().toLatin1());
        return false;
    }
    return true;

}

void Scene2D::toTextFile()
{    
    QString outFileName = QFileDialog(window, "Save to file",
                                  QCoreApplication::applicationDirPath()).getSaveFileName();
    QFile outFile(outFileName);
    if (outFile.open(QIODevice::WriteOnly)){
        outFile.write(parser->getOutPut().toLatin1());
    } else {
        QMessageBox(QMessageBox::Icon::Critical, "Error", "Can't not save file: " + outFileName).exec();
    }

}

void Scene2D::doChangeColor(const QColor &color)
{
    for(auto &it : this->selectedItems()){
        Item *item = static_cast<Item*>(it);        
        parser->outPutChangeColor(item, color);
        changeColor(item, color);
    }
}

void Scene2D::doFillColor(const QColor &color)
{
    for(auto &it : this->selectedItems()){
        Item *item = static_cast<Item*>(it);
        parser->outPutFillColot(item, color);
        changeFillColor(item, color);
    }
}

void Scene2D::deleteItem()
{
    for(auto &it : this->selectedItems()){
        Item *item = static_cast<Item*>(it);
        parser->outPutDeletion(item);
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
    parser->outPutClear();
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
            parser->outPutTranslation(selectedItem, window->getDxTrans(), window->getDyTrans());
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
            parser->outPutRotation(selectedItem, window->getXRotate(), window->getYRotate(), window->getAngleRotate());
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
            parser->outPutScaling(selectedItem, window->getSXScale(), window->getSYScale());
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
            parser->outPutReflection(selectedItem, window->getXReflection(), window->getYReflection());
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
    parser->outPutAddition();
}

void Scene2D::addItemFrom2Points(const QPoint &p1, const QPoint &p2)
{
    if (tmpItem) removeItem(tmpItem);
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
    default:
        break;
    }
    tmpItem->setSelected(true);
    addItem(tmpItem);
    tmpItem->update();
    updateInfo(tmpItem);
    window->setEnableFillButton(tmpItem->getType() != Item::Type::LINE);

}

void Scene2D::addBoundingRect(const QPoint &p1, const QPoint &p2)
{
    QPoint sceneP1 = toScenePos(p1);
    QPoint sceneP2 = toScenePos(p2);
    if (tmpSelected){
        removeItem(tmpSelected);
    }
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
}

void Scene2D::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    points.clear(); // TODO: add polygon
    QGraphicsScene::mousePressEvent(mouseEvent);
    if (mouseEvent->button() == Qt::LeftButton){
        points.emplace_back(toUserCoordinate(mouseEvent->scenePos()));
        points.emplace_back(toUserCoordinate(mouseEvent->scenePos()));
        if (window->getMode() == Window::Mode::SELECT_ITEMS){
            isDrawing = false;
            QGraphicsItem *selectedItem = (this->itemAt(mouseEvent->scenePos(), QTransform()));
            if (selectedItem){
                Item *item = static_cast<Item*>(selectedItem);
                updateInfo(item);
                window->setEnableFillButton(item->getType() != Item::Type::LINE);
                if (!(mouseEvent->modifiers() & Qt::ControlModifier)){
                    clearSelection();
                }
                selectedItem->setSelected(true);
            }
        } else {
            isDrawing = true;
            clearSelection();
            addItemFrom2Points(points.front(), points.back());
        }
    }    
}

void Scene2D::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_UNUSED(mouseEvent);
    if (window->getMode() == Window::Mode::SELECT_ITEMS){
        if (tmpSelected) removeItem(tmpSelected);
        tmpSelected = nullptr;
    } else {
        parser->outPutItem(tmpItem);
        tmpItem = nullptr;
    }
    isDrawing = false;
    points.clear();    
//    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void Scene2D::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (isDrawing){
        points.pop_back();
        points.emplace_back(toUserCoordinate(mouseEvent->scenePos()));
        addItemFrom2Points(points.front(), points.back());
    } else if (window->getMode() == Window::Mode::SELECT_ITEMS){
        if (!points.empty()) points.pop_back();
        points.emplace_back(toUserCoordinate(mouseEvent->scenePos()));
        addBoundingRect(points.front(), points.back());
    }
    QGraphicsScene::mouseMoveEvent(mouseEvent);
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

