#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include "oxy.h"
#include "scene.h"
#include "lineinfo.h"

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();
    enum ShapeKind{
        NORMAL_LINE,
        CIRCLE,
        ELIP,
        RECTANGLE
    };

    ShapeKind getCurrentShape();
    void setInforFrame(LineInfo *lineInfo);

private slots:
    void on_changeColorBtn_clicked();

    void on_deleteBtn_clicked();

private:
    Ui::Window *ui;
    Scene *scene;
};

#endif // WINDOW_H
