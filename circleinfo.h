#ifndef CIRCLEINFO_H
#define CIRCLEINFO_H

#include <QFrame>

namespace Ui {
class CircleInfo;
}

class CircleInfo : public QFrame
{
    Q_OBJECT

public:
    explicit CircleInfo(QWidget *parent = nullptr);
    ~CircleInfo();

private:
    Ui::CircleInfo *ui;
};

#endif // CIRCLEINFO_H
