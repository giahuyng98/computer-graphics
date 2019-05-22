#include "ellipseinfo.h"
#include "ui_ellipseinfo.h"

EllipseInfo::EllipseInfo(QWidget *parent) :
                                            QFrame(parent),
                                            ui(new Ui::EllipseInfo)
{
    ui->setupUi(this);
}

EllipseInfo::~EllipseInfo()
{
    delete ui;
}

void EllipseInfo::setEllipse(Ellipse *value)
{
    ellipse = value;
    if (ellipse){
        ui->ellipsePointx->setText(QString::number(ellipse->getX()));
        ui->ellipsePointy->setText(QString::number(ellipse->getY()));
        ui->ellipseRx->setText(QString::number(ellipse->getXRadius()));
        ui->ellipseRy->setText(QString::number(ellipse->getYRadius()));
    } else {
        ui->ellipsePointx->clear();
        ui->ellipsePointy->clear();
        ui->ellipseRx->clear();
        ui->ellipseRy->clear();
    }
}
