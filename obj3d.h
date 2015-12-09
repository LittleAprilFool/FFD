#ifndef OBJ3D_H
#define OBJ3D_H

#include <QVector>
#include <QtOpenGL>
#include <QString>
#include <QVector3D>

typedef struct Point2d {
    int v;
    int vn;
} point2d;

typedef QVector<point2d> Face;

class obj3d
{
public:
    obj3d();
    QVector<QVector3D> V;
    QVector<QVector3D> ori_V;
    QVector<QVector3D> VN;
    QVector<Face> F;
    void process(QString s);
    void clear();
    float rotateX;
    float rotateY;
    void reset();
};

#endif // OBJ3D_H
