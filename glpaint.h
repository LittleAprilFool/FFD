#ifndef GLPAINT_H
#define GLPAINT_H

#include <QtOpenGL>
#include <QVector3D>

namespace glPaint {
    void glVertex3f(float i, float j, float k);
    void glVertex3f(QVector3D point);
    void glNormal3f(float i, float j, float k);
    void glNormal3f(QVector3D point);
    void glColor3f(float i, float j, float k);
    void glColor3f(QVector3D point);
    void glQuad(QVector3D A, QVector3D B, QVector3D C, QVector3D D);
    const QVector3D GREEN = QVector3D(0, 1, 0);
    const QVector3D RED = QVector3D(1, 0, 0);
}

#endif // GLPAINT_H
