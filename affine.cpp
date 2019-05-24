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

QPoint Affine::translate(const QPoint &point, int dx, int dy)
{
    setTranslate(dx, dy);
    return getPointFromMat(mul(getMatFromPoint(point), transMat));
}

QPoint Affine::rotate(const QPoint &point, int x, int y, int angle)
{
    setTranslate(-x, -y);
    auto trans = mul(getMatFromPoint(point), transMat);
    setRotate(angle);
    auto rot = mul(trans, rotateMat);
    setTranslate(x, y);
    return getPointFromMat(mul(rot, transMat));
}

QPoint Affine::scale(const QPoint &point, float sX, float sY)
{
    setScale(sX, sY);
    return getPointFromMat(mul(getMatFromPoint(point), scaleMat));
}

QPoint Affine::reflect(const QPoint &point, int x, int y)
{
    setReflect(x, y);
    return getPointFromMat(mul(getMatFromPoint(point), refMat));
}

vector<vector<double> > Affine::getMatFromPoint(const QPoint &point) const
{
    return {
        {static_cast<double>(point.x()),
         static_cast<double>(point.y()), 1}
    };
}

QPoint Affine::getPointFromMat(const vector<vector<double> > &mat) const
{
    return {
        static_cast<int>(std::round(mat[0][0])),
        static_cast<int>(std::round(mat[0][1]))
    };
}

void Affine::setTranslate(int dx, int dy)
{
    transMat[2][0] = dx;
    transMat[2][1] = dy;
}

void Affine::setScale(float sx, float sy)
{
    scaleMat[0][0] = static_cast<double>(sx);
    scaleMat[1][1] = static_cast<double>(sy);
}

void Affine::setRotate(int angle)
{
    rotateMat[0][0] = std::cos(angle * M_PI/180);
    rotateMat[0][1] = std::sin(angle * M_PI/180);
    rotateMat[1][0] = -rotateMat[0][1];
    rotateMat[1][1] = rotateMat[0][0];
}

void Affine::setReflect(int x, int y)
{
    refMat[2][0] = x << 1;
    refMat[2][1] = y << 1;
}

vector<vector<double> > Affine::mul(const vector<vector<double> > &point, const vector<vector<double> > &mat) const
{
    vector<vector<double> > result(point.size(), vector<double>(mat.front().size()));
    for(size_t i = 0; i < result.size(); ++i){
        for(size_t j = 0; j < result.front().size(); ++j){
            for(size_t k = 0; k < point.front().size(); ++k){
                result[i][j] += point[i][k] * mat[k][j];
            }
        }
    }
    return result;
}
