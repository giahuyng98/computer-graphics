#include "window.h"
#include "ui_window.h"
#include <QDebug>
#include <QStringListModel>
#include <QTimer>
#include <QColorDialog>

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    scene = new Scene(ui->graphicsView);
    scene->setWindow(this);
    scene3d = new Scene3D(ui->graphicsView);
    scene3d->setWindow(this);
    frame = new Scene(ui->graphicsView);
    frame->setWindow(this);
    ui->graphicsView->setScene(scene);
    ui->shapeKind->setId(ui->lineBtn, ShapeKind::NORMAL_LINE);
    ui->shapeKind->setId(ui->rectBtn, ShapeKind::RECTANGLE);
    ui->shapeKind->setId(ui->circleBtn, ShapeKind::CIRCLE);
    ui->shapeKind->setId(ui->elipBtn, ShapeKind::ELIP);

    ui->splitter->insertWidget(0, scene->getLineInfo());
}

Window::~Window()
{
    delete ui;
}

Window::ShapeKind Window::getCurrentShape()
{
    return ShapeKind(ui->shapeKind->checkedId());
}

int Window::getDxTrans() const
{
    return ui->dxTranslate->text().toInt();
}

int Window::getDyTrans() const
{
    return ui->dyTranslate->text().toInt();
}

int Window::getXRotate() const
{
    return ui->xRolate->text().toInt();
}

int Window::getYRotate() const
{
    return ui->yRolate->text().toInt();
}

int Window::getAngleRotate() const
{
    return ui->angleRolate->text().toInt();
}

float Window::getSXScale() const
{
    return ui->sxScale->text().toFloat();
}

float Window::getSYScale() const
{
    return ui->syScale->text().toFloat();
}

int Window::getXReflection() const
{
    return ui->xReflection->text().toInt();
}

int Window::getYReflection() const
{
    return ui->yReflection->text().toInt();
}

void Window::setShapeKind(Window::ShapeKind shape)
{
    switch (shape) {
    case NORMAL_LINE:
        ui->splitter->replaceWidget(0, scene->getLineInfo());
        break;
    case RECTANGLE:
       ui->splitter->replaceWidget(0, scene->getRectInfo());
        break;
    case CIRCLE:
        ui->splitter->replaceWidget(0, scene->getCircleInfo());
        break;
    case ELIP:
        ui->splitter->replaceWidget(0, scene->getEllipseInfo());
        break;
    }
}

void Window::setEnableFillButton(bool enable)
{
    ui->fillColorBtn->setEnabled(enable);
}

void Window::on_changeColorBtn_clicked()
{
    QColor color = QColorDialog::getColor(Qt::black, this);
    if (color.isValid()) scene->doChangeColor(color);
}

void Window::on_deleteBtn_clicked()
{
    scene->deleteItem();
}

void Window::on_clearSceneBtn_clicked()
{
    scene->clearAll();
}

void Window::on_translateBtn_clicked()
{
    scene->doTranslation();
}

void Window::on_scaleBtn_clicked()
{
    scene->doScaling();
}

void Window::on_rolateBtn_clicked()
{
    scene->doRotation();
}
void Window::on_reflecBtn_clicked()
{
    scene->doReflection();
}

void Window::on_tabWidget_currentChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
    ui->verticalSlider->setDisabled(index == 2);
    switch (index){
    case 0:
        ui->graphicsView->setScene(scene);
        ui->thicknessLabel->setNum(scene->getThickness());
        ui->verticalSlider->setValue(scene->getThickness());
        break;
    case 1:
        ui->graphicsView->setScene(scene3d);
        ui->thicknessLabel->setNum(scene3d->getThickness());
        ui->verticalSlider->setValue(scene3d->getThickness());
        break;
    case 2:
        ui->graphicsView->setScene(frame);
        break;
    }
}

void Window::on_addCubeBtn_clicked()
{
    scene3d->addCube(ui->cubeX->text().toInt(), ui->cubeY->text().toInt(), ui->cubeZ->text().toInt(),
                     ui->cubeW->text().toInt(), ui->cubeH->text().toInt(), ui->cubeL->text().toInt());
}

void Window::on_cavalier_toggled(bool checked)
{
    if (checked){
        scene3d->setMethod(1);
    } else {
        scene3d->setMethod(0);
    }
}

void Window::on_clear3Dbtn_clicked()
{
    scene3d->clear();
}

void Window::on_addSphereBtn_clicked()
{
    scene3d->addSphere(ui->xSphere->text().toInt(), ui->ySphere->text().toInt(), ui->zSphere->text().toInt(),
                       ui->rShere->text().toInt());
}

void Window::on_fillColorBtn_clicked()
{
    QColor color = QColorDialog::getColor(Qt::black, this);
    if (color.isValid()) scene->doFillColor(color);
}

void Window::on_playBtn_clicked()
{
    frame->play(0);
}

void Window::on_verticalSlider_valueChanged(int value)
{
    ui->thicknessLabel->setNum(value);
    switch (ui->tabWidget->currentIndex()){
    case 0:
        scene->setThickness(value);
        break;
    case 1:
        scene3d->setThickness(value);
        break;
    case 2:
        break;
    }
}
