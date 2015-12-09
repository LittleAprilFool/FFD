#include "glpaint.h"

namespace glPaint {
void glVertex3f(QVector3D point)
{
    ::glVertex3f(point.x(), point.y(), point.z());
}

void glVertex3f(float i, float j, float k){
    ::glVertex3f(i,j,k);
}

void glNormal3f(QVector3D point)
{
    ::glNormal3f(point.x(), point.y(), point.z());
}

void glNormal3f(float i, float j, float k)
{
    ::glNormal3f(i,j,k);
}

void glColor3f(QVector3D color)
{
    ::glColor3f(color.x(), color.y(), color.z());
}

void glColor3f(float i, float j, float k)
{
    ::glColor3f(i,j,k);
}

void glQuad(QVector3D A, QVector3D B, QVector3D C, QVector3D D)
{
    glVertex3f(A);
    glVertex3f(B);
    glVertex3f(C);
    glVertex3f(D);
}
}//end of namespace glPaint

