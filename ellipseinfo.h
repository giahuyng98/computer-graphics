#ifndef ELLIPSEINFO_H
#define ELLIPSEINFO_H

#include <QFrame>
#include "ellipse.h"

namespace Ui {
class EllipseInfo;
}

class EllipseInfo : public QFrame
{
    Q_OBJECT

public:
    explicit EllipseInfo(QWidget *parent = nullptr);
    ~EllipseInfo();

    void setEllipse(Ellipse *value);

private slots:
    void on_applyBtn_clicked();

private:
    Ui::EllipseInfo *ui;
    Ellipse *ellipse;

};

#endif // ELLIPSEINFO_H
