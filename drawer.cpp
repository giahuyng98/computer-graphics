#include "drawer.h"

Drawer::Drawer(QWidget *parent)
    : QWidget(parent),
      oxy(width(), height())
{
    show();
    oxy.putPixel(0, 0);
}

void Drawer::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    oxy.draw(&painter);
}
