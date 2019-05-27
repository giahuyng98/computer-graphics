#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include "scene3d.h"
#include "scene2d.h"
#include "sceneanimation.h"
#include "apidrawer.h"

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();
    enum Mode{
        DRAW_LINE,
        DRAW_CIRCLE,
        DRAW_ELLIPSE,
        DRAW_RECT,
        SELECT_ITEMS
    };

    Mode getMode();
    int getDxTrans() const;
    int getDyTrans() const;
    int getXRotate() const;
    int getYRotate() const;
    int getAngleRotate() const;
    float getSXScale() const;
    float getSYScale() const;
    int getXReflection() const;
    int getYReflection() const;

    void setMode(Mode mode);
    void setEnableFillButton(bool enable);
    void setThickness(int value);


private slots:
    void on_changeColorBtn_clicked();

    void on_deleteBtn_clicked();   

    void on_clearSceneBtn_clicked();

    void on_translateBtn_clicked();

    void on_scaleBtn_clicked();

    void on_rolateBtn_clicked();   

    void on_reflecBtn_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_addCubeBtn_clicked();

    void on_cavalier_toggled(bool checked);

    void on_clear3Dbtn_clicked();

    void on_addSphereBtn_clicked();

    void on_fillColorBtn_clicked();

    void on_playBtn_clicked();

    void on_verticalSlider_valueChanged(int value);

    void on_addCylinder_clicked();

    void on_toTextFileBtn_clicked();

    void on_openSceneBtn_clicked();

    void on_addSceneBtn_clicked();

private:
    Ui::Window *ui;
    Scene2D *scene2d;
    Scene3D *scene3d;
    SceneAnimation *sceneAnimation;
};

#endif // WINDOW_H
