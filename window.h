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
    int getDxTrans() const;
    int getDyTrans() const;

private slots:
    void on_changeColorBtn_clicked();

    void on_deleteBtn_clicked();

    void on_rectBtn_clicked();

    void on_lineBtn_clicked();

    void on_clearSceneBtn_clicked();

    void on_translateBtn_clicked();

    void on_scaleBtn_clicked();

    void on_rolateBtn_clicked();

private:
    Ui::Window *ui;
    Scene *scene;
};

#endif // WINDOW_H
