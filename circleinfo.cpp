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
