#ifndef CIRCLEINFO_H
#define CIRCLEINFO_H

#include <QFrame>
#include "circle.h"
namespace Ui {
class CircleInfo;
}

class CircleInfo : public QFrame
{
    Q_OBJECT

public:
    explicit CircleInfo(QWidget *parent = nullptr);
    ~CircleInfo();


    void setCircle(Circle *value);

private slots:
    void on_applyBtn_clicked();

private:
    Ui::CircleInfo *ui;
    Circle *circle;
};

#endif // CIRCLEINFO_H
