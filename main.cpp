#include "window.h"
#include <QApplication>

#include "affine.h"

int main(int argc, char *argv[])
{
    Affine af;
    QApplication a(argc, argv);
    Window w;
    w.show();

    return a.exec();
}
