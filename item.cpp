#include "item.h"
#include "scene.h"

void Item::drawPixel(int x, int y)
{
    int offx = ((Scene*)this->scene())->getOffx();
    int offy = ((Scene*)this->scene())->getOffy();
    int thickness = ((Scene*)this->scene())->getThickness();
    path.addRect((x + offx) * thickness, (offy - y) * thickness, thickness, thickness);
}
QPainterPath Item::shape() const{
    return path;
}
