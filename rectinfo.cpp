#include "rectinfo.h"
#include "ui_rectinfo.h"

RectInfo::RectInfo(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::RectInfo)
{
    ui->setupUi(this);    
}

RectInfo::~RectInfo()
{
    delete ui;
}

void RectInfo::setRect(Rectangle *value)
{
    rect = value;
    if (rect){
        ui->rectEditPoint1->setText(QString::number(rect->getPos().x()));
        ui->rectEditPoint2->setText(QString::number(rect->getPos().y()));
        ui->rectEditWidth->setText(QString::number(rect->getSize().width()));
        ui->rectEditHeight->setText(QString::number(rect->getSize().height()));
    } else {
        ui->rectEditPoint1->clear();
        ui->rectEditPoint2->clear();
        ui->rectEditWidth->clear();
        ui->rectEditHeight->clear();
    }
}

void RectInfo::on_applyBtn_clicked()
{
    rect->setPos(QPoint(ui->rectEditPoint1->text().toInt(), ui->rectEditPoint2->text().toInt()));
    rect->setSize(QSize(ui->rectEditWidth->text().toInt(), ui->rectEditHeight->text().toInt()));
    rect->reDraw();
}
