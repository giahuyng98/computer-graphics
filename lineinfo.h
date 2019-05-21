#ifndef LINEINFO_H
#define LINEINFO_H

#include <QFrame>
#include <line.h>

namespace Ui {
class LineInfo;
}

class LineInfo : public QFrame
{
    Q_OBJECT

public:
    explicit LineInfo(QWidget *parent = nullptr);
    ~LineInfo();
    void setLine(Line *line);

private slots:
    void on_applyBtn_clicked();

private:
    Ui::LineInfo *ui;
    Line *line = nullptr;
};

#endif // LINEINFO_H
