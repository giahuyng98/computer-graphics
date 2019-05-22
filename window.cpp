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
    ui->graphicsView->setScene(scene);
    ui->shapeKind->setId(ui->lineBtn, ShapeKind::NORMAL_LINE);
    ui->shapeKind->setId(ui->rectBtn, ShapeKind::RECTANGLE);
    ui->shapeKind->setId(ui->circleBtn, ShapeKind::CIRCLE);
    ui->shapeKind->setId(ui->elipBtn, ShapeKind::ELIP);

    ui->splitter->insertWidget(0, scene->getLineInfo());

//    scene->setTree(ui->treeWidget);
//    ui->treeWidget->setColumnCount(2);
//    ui->treeWidget->setHeaderLabels(QStringList() << "Name" << "Value");

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

//void Window::setInforFrame(QWidget *widget)
//{

//    ui->infoLayout->addWidget(widget);
//}

void Window::on_changeColorBtn_clicked()
{
    QColor color = QColorDialog::getColor(Qt::black, this);
    if (color.isValid()) scene->changeColor(color);
}

void Window::on_deleteBtn_clicked()
{
    scene->deleteItem();
}

void Window::on_rectBtn_clicked()
{
    ui->splitter->replaceWidget(0, scene->getRectInfo());
}

void Window::on_lineBtn_clicked()
{
    ui->splitter->replaceWidget(0, scene->getLineInfo());
//    ui->infoLayout->removeItem(ui->infoLayout->takeAt(0));
//    ui->infoLayout->addWidget(scene->getLineInfo());
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

void Window::on_circleBtn_clicked()
{
    ui->splitter->replaceWidget(0, scene->getCircleInfo());
}

void Window::on_elipBtn_clicked()
{
    ui->splitter->replaceWidget(0, scene->getEllipseInfo());
}

void Window::on_tabWidget_currentChanged(int index)
{
    switch (index){
    case 0:
        ui->graphicsView->setScene(scene);
        break;
    case 1:
        ui->graphicsView->setScene(scene3d);
        break;
    default:
        exit(23);
    }
}
