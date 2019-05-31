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
        ui->rectEditWidth->setText(QString::number(rect->getWidth()));
        ui->rectEditHeight->setText(QString::number(rect->getHeight()));
    } else {
        ui->rectEditTopLeftX->clear();
        ui->rectEditTopLeftY->clear();
        ui->rectEditBottomRightX->clear();
        ui->rectEditBottomRightY->clear();
        ui->rectEditWidth->clear();
        ui->rectEditHeight->clear();
    }
}

void RectInfo::on_applyBtn_clicked()
{
    if (!rect) return;
    rect->setTopLeft(QPoint(ui->rectEditTopLeftX->text().toInt(),
                            ui->rectEditTopLeftY->text().toInt()));
    rect->setBottomRight(QPoint(ui->rectEditBottomRightX->text().toInt(),
                                ui->rectEditBottomRightY->text().toInt()));
    QSize size(std::abs(rect->getTopLeft().x() - rect->getBottomRight().x()),
               std::abs(rect->getTopLeft().y() - rect->getBottomRight().y()));

    rect->setTopRight(QPoint(rect->getTopLeft().x() + size.width(), rect->getTopLeft().y()));
    rect->setBottomLeft(QPoint(rect->getTopLeft().x(), rect->getTopLeft().y() - size.height()));
    rect->reDraw();
}
