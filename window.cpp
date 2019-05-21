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
    ui->graphicsView->setScene(scene);
    ui->shapeKind->setId(ui->lineBtn, ShapeKind::NORMAL_LINE);
    ui->shapeKind->setId(ui->rectBtn, ShapeKind::RECTANGLE);
    ui->shapeKind->setId(ui->circleBtn, ShapeKind::CIRCLE);
    ui->shapeKind->setId(ui->elipBtn, ShapeKind::ELIP);

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

void Window::setInforFrame(QWidget *widget)
{

    ui->infoLayout->addWidget(widget);
}

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
