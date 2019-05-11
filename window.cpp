#include "window.h"
#include "ui_window.h"
#include <QDebug>
#include <QStringListModel>
#include <QTimer>

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    scene = new Scene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
    scene->setTree(ui->treeWidget);
    ui->treeWidget->setColumnCount(2);
    ui->treeWidget->setHeaderLabels(QStringList() << "Name" << "Value");

}

Window::~Window()
{
    delete ui;
}
