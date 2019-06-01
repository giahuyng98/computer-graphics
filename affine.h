#ifndef AFFINE_H
#define AFFINE_H

#include <vector>
#include <cmath>
#include <QPoint>
using std::vector;

class Affine
{
public:
    explicit Affine();
    QPoint translate(const QPoint &point, int dx, int dy);
    QPoint rotate(const QPoint &point, int x, int y, int angle);
    QPoint scale(const QPoint &point, float sX, float sY);
    QPoint scale(const QPoint &point, float sX, float sY, int x, int y);
    QPoint reflect(const QPoint &point, int x, int y);

private:
    vector<vector<double>> getMatFromPoint(const QPoint &point) const;
    QPoint getPointFromMat(const vector<vector<double>> &mat) const;

    void setTranslate(int dx, int dy);
    void setScale(float sx, float sy);
    void setRotate(int angle);
    void setReflect(int x, int y);

    vector<vector<double>> mul(const vector<vector<double>> &point,
                               const vector<vector<double>> &mat) const;
    vector<vector<double>> rotateMat, scaleMat, transMat, refMat;
};

#endif // AFFINE_H
