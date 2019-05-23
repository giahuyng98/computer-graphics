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
        {-1, 0, 0},
        {0, -1, 0},
        {0, 0, 1}
    };

    rotateMat = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 1}
    };

}


vector<vector<int> > Affine::round(vector<vector<float> > mat) const
{
    vector<vector<int> > result(mat.size(), vector<int>(mat.front().size()));
    for (size_t i = 0; i < mat.size(); ++i)
    {
        for (size_t j = 0; j < mat.front().size(); ++j)
        {
            result[i][j] = static_cast<int>(std::round(mat[i][j]));
        }
    }
    return result;
}

void Affine::setTranslate(int dx, int dy)
{
    transMat[2][0] = dx;
    transMat[2][1] = dy;
}

void Affine::setScale(float sx, float sy)
{
    scaleMat[0][0] = sx;
    scaleMat[1][1] = sy;
}

void Affine::setRotate(int angle)
{
    rotateMat[0][0] = std::cos(angle * M_PI/180.f);
    rotateMat[0][1] = std::sin(angle * M_PI/180.f);
    rotateMat[1][0] = -rotateMat[0][1];
    rotateMat[1][1] = rotateMat[0][0];
}

void Affine::setReflect(int x, int y)
{
    refMat[2][0] = x << 1;
    refMat[2][1] = y << 1;
}
