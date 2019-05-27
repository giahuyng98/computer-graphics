#include "window.h"
#include "ui_window.h"
#include <QDebug>
#include <QStringListModel>
#include <QTimer>
#include <QColorDialog>
#include <QFileDialog>

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    scene2d = new Scene2D(ui->graphicsView);
    scene2d->setWindow(this);
    scene3d = new Scene3D(ui->graphicsView);
    scene3d->setWindow(this);
    sceneAnimation = new SceneAnimation(ui->graphicsView);
    sceneAnimation->setWindow(this);

    ui->graphicsView->setScene(scene2d);
    ui->modeGroupBtn->setId(ui->lineBtn, Mode::DRAW_LINE);
    ui->modeGroupBtn->setId(ui->rectBtn, Mode::DRAW_RECT);
    ui->modeGroupBtn->setId(ui->circleBtn, Mode::DRAW_CIRCLE);
    ui->modeGroupBtn->setId(ui->elipBtn, Mode::DRAW_ELLIPSE);
    ui->modeGroupBtn->setId(ui->selectBtn, Mode::SELECT_ITEMS);

    ui->splitter->insertWidget(0, scene2d->getLineInfo());
}

Window::~Window()
{
    delete ui;
}

Window::Mode Window::getMode()
{
    return Mode(ui->modeGroupBtn->checkedId());
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

void Window::setMode(Window::Mode mode)
{
    switch (mode) {
    case DRAW_LINE:
        if (ui->splitter->widget(0) != scene2d->getLineInfo())
            ui->splitter->replaceWidget(0, scene2d->getLineInfo());
        break;
    case DRAW_RECT:
        if (ui->splitter->widget(0) != scene2d->getRectInfo())
            ui->splitter->replaceWidget(0, scene2d->getRectInfo());
        break;
    case DRAW_CIRCLE:
        if (ui->splitter->widget(0) != scene2d->getCircleInfo())
            ui->splitter->replaceWidget(0, scene2d->getCircleInfo());
        break;
    case DRAW_ELLIPSE:
        if (ui->splitter->widget(0) != scene2d->getEllipseInfo())
            ui->splitter->replaceWidget(0, scene2d->getEllipseInfo());
        break;
    }
}

void Window::setEnableFillButton(bool enable)
{
    ui->fillColorBtn->setEnabled(enable);
}

void Window::setThickness(int value)
{
    ui->verticalSlider->setValue(value / 5);
}

void Window::on_changeColorBtn_clicked()
{
    QColor color = QColorDialog::getColor(Qt::black, this);
    if (color.isValid()) scene2d->doChangeColor(color);
}

void Window::on_deleteBtn_clicked()
{
    scene2d->deleteItem();
}

void Window::on_clearSceneBtn_clicked()
{
    scene2d->clearAll();
}

void Window::on_translateBtn_clicked()
{
    scene2d->doTranslation();
}

void Window::on_scaleBtn_clicked()
{
    scene2d->doScaling();
}

void Window::on_rolateBtn_clicked()
{
    scene2d->doRotation();
}
void Window::on_reflecBtn_clicked()
{
    scene2d->doReflection();
}

void Window::on_tabWidget_currentChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
    ui->verticalSlider->setDisabled(index == 2);
    ui->stackedWidget->setMaximumSize(9999, 9999);
    switch (index){
    case 0:
        ui->graphicsView->setScene(scene2d);        
        ui->verticalSlider->setValue(scene2d->getThickness() / 5);
        break;
    case 1:
        ui->graphicsView->setScene(scene3d);
        ui->verticalSlider->setValue(scene3d->getThickness() / 5);
        break;
    case 2:
        ui->graphicsView->setScene(sceneAnimation);
        ui->verticalSlider->setValue(sceneAnimation->getThickness() / 5);
        ui->stackedWidget->setMaximumSize(200, 9999);
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
    scene3d->addSphere(ui->xSphere->text().toInt(), ui->ySphere->text().toInt(),
                       ui->zSphere->text().toInt(), ui->rShere->text().toInt());
}
void Window::on_addCylinder_clicked()
{
    scene3d->addCylinder(ui->cylinderX->text().toInt(), ui->cylinderY->text().toInt(),
                         ui->cylinderZ->text().toInt(), ui->cylinderR->text().toInt(),
                         ui->cylinderH->text().toInt());
}
void Window::on_fillColorBtn_clicked()
{
    QColor color = QColorDialog::getColor(Qt::black, this);
    if (color.isValid()) scene2d->doFillColor(color);
}

void Window::on_playBtn_clicked()
{
    sceneAnimation->play();
}

void Window::on_verticalSlider_valueChanged(int value)
{
    value *= 5;
    ui->thicknessLabel->setNum(value);
    switch (ui->tabWidget->currentIndex()){
    case 0:
        scene2d->setThickness(value);
        break;
    case 1:
        scene3d->setThickness(value);
        break;
    case 2:
//        sceneAnimation->setThickness(value);
        break;
    }
}

void Window::on_toTextFileBtn_clicked()
{
    scene2d->toTextFile();
}

void Window::on_openSceneBtn_clicked()
{
    sceneAnimation->open(QFileDialog(this, "Select file",
     QCoreApplication::applicationDirPath()).getOpenFileName());
}

void Window::on_addSceneBtn_clicked()
{
    static int cur = 0;
    ++cur;
    ui->addSceneBtn->setText("Add Scene " + QString::number(cur));
    scene2d->addScene();
}
