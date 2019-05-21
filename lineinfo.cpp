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
