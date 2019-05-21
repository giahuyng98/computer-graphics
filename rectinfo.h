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

private:
    Ui::RectInfo *ui;

};

#endif // RECTINFO_H
