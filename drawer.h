#ifndef DRAWER_H
#define DRAWER_H

#include <QPaintEvent>
#include <QWidget>
#include <oxy.h>

class Drawer : public QWidget
{
    Q_OBJECT
public:
    explicit Drawer(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
signals:

public slots:

private:
    Oxy oxy;
};

#endif // DRAWER_H
