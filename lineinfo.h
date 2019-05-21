#ifndef LINEINFO_H
#define LINEINFO_H

#include <QFrame>

namespace Ui {
class LineInfo;
}

class LineInfo : public QFrame
{
    Q_OBJECT

public:
    explicit LineInfo(QWidget *parent = nullptr);
    ~LineInfo();

private:
    Ui::LineInfo *ui;
};

#endif // LINEINFO_H
