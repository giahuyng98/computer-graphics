#ifndef AFFINE_H
#define AFFINE_H

#include <vector>
#include <cmath>
using std::vector;

class Affine
{
public:
    explicit Affine();
    template<class T> std::vector<T> translate(const std::vector<T> &point, int dx, int dy);
    template<class T> std::vector<T> rotate(const std::vector<T> &point, int x, int y, int angle);

private:

    vector<vector<float>> round(vector<vector<float>> mat) const;
    void setTranslate(int dx, int dy);
    void setScale(int sx, int sy);
    void setRotate(int angle);

    template<class T, class E> std::vector<E> mul(const std::vector<T> &point, const std::vector<E> &mat) const;

    vector<vector<int>> transMat, scaleMat, refMat;
    vector<vector<float>> rotateMat;
};



template<class T, class E>
vector<E> Affine::mul(const vector<T> &point, const vector<E> &mat) const
{
    vector<E> result(point.size(), E(mat.front().size()));
    for(size_t i = 0; i < result.size(); ++i){
        for(size_t j = 0; j < result.front().size(); ++j){
            for(size_t k = 0; k < point.front().size(); ++k){
                result[i][j] += point[i][k] * mat[k][j];
            }            
        }
    }
    return result;
}

template<class T>
std::vector<T> Affine::translate(const std::vector<T> &point, int dx, int dy)
{
    setTranslate(dx, dy);
    return mul(point, transMat);
}

template<class T>
std::vector<T> Affine::rotate(const std::vector<T> &point, int x, int y, int angle)
{
    setRotate(angle);
    setTranslate(-x, -y);
    auto tran = mul(point, transMat);
    auto rot = round(mul(tran, rotateMat));
    setTranslate(x, y);
    return mul(rot, transMat);
}

#endif // AFFINE_H
