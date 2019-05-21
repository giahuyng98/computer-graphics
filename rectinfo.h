#ifndef RECTINFO_H
#define RECTINFO_H

#include <QFrame>
#include "rectangle.h"

namespace Ui {
class RectInfo;
}

class RectInfo : public QFrame
{
    Q_OBJECT

public:
    explicit RectInfo(QWidget *parent = nullptr);    
    ~RectInfo();

    void setRect(Rectangle *value);

private slots:
    void on_applyBtn_clicked();

private:
    Ui::RectInfo *ui;
    Rectangle *rect = nullptr;
};

#endif // RECTINFO_H
