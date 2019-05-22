#ifndef AFFINE_H
#define AFFINE_H

#include <vector>
using std::vector;

class Affine
{
public:
    explicit Affine();
    template<class T> std::vector<T> translate(const std::vector<T> &point, int dx, int dy);

private:
    void setTranslate(int dx, int dy);
    void setScale(int sx, int sy);
    template<class T = int, class E = int> std::vector<T> mul(const std::vector<T> &point, const std::vector<E> &mat) const;

    vector<vector<int>> transMat, scaleMat, refMat;
    vector<vector<float>> rolateMat;
};


template<class T, class E>
vector<T> Affine::mul(const vector<T> &point, const vector<E> &mat) const
{
    vector<T> result(point.size(), T(mat.front().size()));
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

#endif // AFFINE_H
