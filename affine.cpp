#include "affine.h"
#include <cassert>


Affine::Affine()
{
    transMat = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    scaleMat = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    refMat = {
        {},
        {},
        {}
    };

    rotateMat = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 1}
    };

}

void Affine::setTranslate(int dx, int dy)
{
    transMat[2][0] = dx;
    transMat[2][1] = dy;
}

void Affine::setScale(int sx, int sy)
{
    scaleMat[0][0] = sx;
    scaleMat[1][1] = sy;
}

void Affine::setRotate(int angle)
{

    rotateMat[0][0] = std::cos(angle * 3.141592653589/180);
    rotateMat[0][1] = std::sin(angle * 3.141592653589/180);
    rotateMat[1][0] = -rotateMat[0][1];
    rotateMat[1][1] = rotateMat[0][0];

}
