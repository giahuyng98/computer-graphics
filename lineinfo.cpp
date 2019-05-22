#include "lineinfo.h"
#include "ui_lineinfo.h"

LineInfo::LineInfo(QWidget *parent) :
                                      QFrame(parent),
                                      ui(new Ui::LineInfo)
{
    ui->setupUi(this);
}

LineInfo::~LineInfo()
{
    delete ui;
}

void LineInfo::setLine(Line *line)
{
    this->line = line;
    if (line){
        ui->lineEditPoint1x->setText(QString::number(line->getX1()));
        ui->lineEditPoint1y->setText(QString::number(line->getY1()));
        ui->lineEditPoint2x->setText(QString::number(line->getX2()));
        ui->lineEditPoint2y->setText(QString::number(line->getY2()));
    } else {
        ui->lineEditPoint1x->clear();
        ui->lineEditPoint1y->clear();
        ui->lineEditPoint2x->clear();
        ui->lineEditPoint2y->clear();
    }
}

void LineInfo::on_applyBtn_clicked()
{
    if (!line) return;
    line->setX1(ui->lineEditPoint1x->text().toInt());
    line->setY1(ui->lineEditPoint1y->text().toInt());
    line->setX2(ui->lineEditPoint2x->text().toInt());
    line->setY2(ui->lineEditPoint2y->text().toInt());
    line->reDraw();
}
