#include "circleinfo.h"
#include "ui_circleinfo.h"

CircleInfo::CircleInfo(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CircleInfo)
{
    ui->setupUi(this);
}

CircleInfo::~CircleInfo()
{
    delete ui;
}

void CircleInfo::setCircle(Circle *value)
{
    circle = value;
    if (circle){
        ui->circlePoint1->setText(QString::number(circle->getX()));
        ui->circlePoint2->setText(QString::number(circle->getY()));
        ui->circleRadius->setText(QString::number(circle->getR()));
    } else {
        ui->circlePoint1->clear();
        ui->circlePoint2->clear();
        ui->circleRadius->clear();
    }
}


void CircleInfo::on_applyBtn_clicked()
{
    if (!circle) return;
    circle->setX(ui->circlePoint1->text().toInt());
    circle->setY(ui->circlePoint2->text().toInt());
    circle->setR(ui->circleRadius->text().toInt());
    circle->reDraw();
}
