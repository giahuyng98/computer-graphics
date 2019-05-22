#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include "scene.h"
#include "scene3d.h"

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
    int getXRotate() const;
    int getYRotate() const;
    int getAngleRotate() const;
    float getSXScale() const;
    float getSYScale() const;
    int getXReflection() const;
    int getYReflection() const;

    void setShapeKind(ShapeKind shape);


private slots:
    void on_changeColorBtn_clicked();

    void on_deleteBtn_clicked();

    void on_rectBtn_clicked();

    void on_lineBtn_clicked();

    void on_clearSceneBtn_clicked();

    void on_translateBtn_clicked();

    void on_scaleBtn_clicked();


    void on_rolateBtn_clicked();

    void on_circleBtn_clicked();


    void on_elipBtn_clicked();

<<<<<<< HEAD
    void on_reflecBtn_clicked();
=======
    void on_tabWidget_currentChanged(int index);
>>>>>>> d78b721ce4e8f743d7ce69fbd248121d1922abbb

private:
    Ui::Window *ui;
    Scene *scene;
    Scene3D *scene3d;
};

#endif // WINDOW_H
