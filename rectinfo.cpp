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
