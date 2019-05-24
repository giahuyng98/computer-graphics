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
    if (rect)
    {
        ui->rectEditTopLeftX->setText(QString::number(rect->getTopLeft().x()));
        ui->rectEditTopLeftY->setText(QString::number(rect->getTopLeft().y()));
        ui->rectEditBottomRightX->setText(QString::number(rect->getBottomRight().x()));
        ui->rectEditBottomRightY->setText(QString::number(rect->getBottomRight().y()));
        ui->rectEditWidth->setText(QString::number(std::abs(rect->getTopRight().x() - rect->getTopLeft().x())));
        ui->rectEditHeight->setText(QString::number(std::abs(rect->getTopLeft().y() - rect->getBottomLeft().y())));
    } else {
        ui->rectEditTopLeftX->clear();
        ui->rectEditTopLeftY->clear();
        ui->rectEditWidth->clear();
        ui->rectEditHeight->clear();
    }
}

void RectInfo::on_applyBtn_clicked()
{
    if (!rect) return;
//    rect->setTopLeft(QPoint(ui->rectEditTopLeftX->text().toInt(), ui->rectEditTopLeftY->text().toInt()));
//    rect->setBottomRight(QPoint(ui->rectEditBottomRightX->text().toInt(), ui->rectEditBottomRightY->text().toInt()));
//    rect->setTopRight(QPoint(ui->rectEditTopLeftX->text().toInt() + ui->rectEditWidth->text().toInt(), ));
//    rect->setPos(QPoint(ui->rectEditPoint1->text().toInt(), ui->rectEditPoint2->text().toInt()));
//    rect->setSize(QSize(ui->rectEditWidth->text().toInt(), ui->rectEditHeight->text().toInt()));
    rect->reDraw();
}
