#ifndef OBJ3D_H
#define OBJ3D_H

#include <QVector>
#include <QtOpenGL>
#include <QString>

typedef struct Point3d {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} point3d;

typedef struct Point2d {
    int v;
    int vn;
} point2d;

typedef struct Face {
    point2d p1;
    point2d p2;
    point2d p3;
} face;

class obj3d
{
public:
    obj3d();
    QVector<point3d> V;
    QVector<point3d> VN;
    QVector<face> F;
    void process(QString s);
};

#endif // OBJ3D_H
