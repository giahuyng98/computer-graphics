#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include "oxy.h"
#include "scene.h"

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();

private:
    Ui::Window *ui;
    Scene *scene;
};

#endif // WINDOW_H
