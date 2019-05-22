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

    rolateMat = {
        {},
        {},
        {}
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
