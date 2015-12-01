#include "glcanvas.h"

glCanvas::glCanvas(QGLWidget *parent) : QGLWidget(parent)
{
    obj = new obj3d();
}

glCanvas::~glCanvas(){
    delete obj;
}

void process_line(QString line){
    qDebug()<<line;
}

void glCanvas::open(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        obj->process(line);
    }
}

void glCanvas::paintGL()
{
    for(int i = 0; i < obj->F.size(); i++) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBegin(GL_TRIANGLES);
        glNormal3f(obj->VN[obj->F[i].p1.vn].x,   obj->VN[obj->F[i].p1.vn].y,  obj->VN[obj->F[i].p1.vn].z);
        glVertex3d(obj->V[obj->F[i].p1.v].x,     obj->V[obj->F[i].p1.v].y,    obj->V[obj->F[i].p1.v].z);
        glNormal3f(obj->VN[obj->F[i].p2.vn].x,   obj->VN[obj->F[i].p2.vn].y,  obj->VN[obj->F[i].p2.vn].z);
        glVertex3d(obj->V[obj->F[i].p2.v].x,     obj->V[obj->F[i].p2.v].y,    obj->V[obj->F[i].p2.v].z);
        glNormal3f(obj->VN[obj->F[i].p3.vn].x,   obj->VN[obj->F[i].p3.vn].y,  obj->VN[obj->F[i].p3.vn].z);
        glVertex3d(obj->V[obj->F[i].p3.v].x,     obj->V[obj->F[i].p3.v].y,    obj->V[obj->F[i].p3.v].z);
        glEnd();
    }
}

void glCanvas::assemble()
{
    for(int i = 0; i < obj->F.size(); i++) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBegin(GL_TRIANGLES);
        glNormal3f(obj->VN[obj->F[i].p1.vn].x,   obj->VN[obj->F[i].p1.vn].y,  obj->VN[obj->F[i].p1.vn].z);
        glVertex3d(obj->V[obj->F[i].p1.v].x,     obj->V[obj->F[i].p1.v].y,    obj->V[obj->F[i].p1.v].z);
        glNormal3f(obj->VN[obj->F[i].p2.vn].x,   obj->VN[obj->F[i].p2.vn].y,  obj->VN[obj->F[i].p2.vn].z);
        glVertex3d(obj->V[obj->F[i].p2.v].x,     obj->V[obj->F[i].p2.v].y,    obj->V[obj->F[i].p2.v].z);
        glNormal3f(obj->VN[obj->F[i].p3.vn].x,   obj->VN[obj->F[i].p3.vn].y,  obj->VN[obj->F[i].p3.vn].z);
        glVertex3d(obj->V[obj->F[i].p3.v].x,     obj->V[obj->F[i].p3.v].y,    obj->V[obj->F[i].p3.v].z);
        glEnd();
    }
}
