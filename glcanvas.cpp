#include "glcanvas.h"

glCanvas::glCanvas(QGLWidget *parent) : QGLWidget(parent)
{
    obj = new obj3d();
    control_point = new controlPoint();
    mouse_caputured = false;
    focus_point = QVector3D(0, 0, 0);
    control_point->setColor(focus_point, GREEN);
    isColor = true;
    qDebug()<<glGetString(GL_VERSION);
}

glCanvas::~glCanvas(){
}

//open an .obj file and store the data into obj
void glCanvas::open(QString fileName)
{
    obj->clear();
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        obj->process(line);
    }
    reset();
    updateGL();
}

void glCanvas::updateControlPoint(int x, int y, int z, float size)
{
    control_point->update(x, y, z, size);
    control_point->setColor(focus_point, GREEN);
    updateGL();
}

void glCanvas::updateFocusPoint(int x, int y, int z)
{
    control_point->setColor(focus_point, RED);
    focus_point = QVector3D(x, y, z);
    control_point->setColor(focus_point, GREEN);
    updateGL();
}

void glCanvas::updateFocusPointPosition(int x, int y, int z)
{
    control_point->updatePoint(focus_point, QVector3D((x - 50) / 100.00, (y - 50) / 100.00, (z - 50) / 100.00));
    updateOBJ();
    updateGL();
}

QVector3D glCanvas::getFocusPointPosition(int x, int y, int z)
{
    QVector3D result =  (control_point->getPosition(x, y, z) - control_point->getOriPosition(x, y, z)) * 100 + QVector3D(50, 50, 50);
    return result;
}

float Bernstein(int n, int i, float u){
    int j = n-i;
    float v = 1-u;
    int mul_n = 1;
    int mul_j = 1;
    int mul_i = 1;
    float mul_u = 1;
    float mul_v = 1;
    for(int k =1; k <= n; k++){
        if(k <= j) { mul_j *=k; mul_v *=v;}
        if(k <= i) { mul_i *=k; mul_u *=u;}
        mul_n *=k;
    }
    float result = mul_u * mul_v * mul_n / (mul_i * mul_j);
    return result;
}

QVector3D glCanvas::convertPoint(QVector3D point)
{
    x0 = QVector3D(-control_point->size(),-control_point->size(),-control_point->size());
    QVector3D result = (point - x0) / (2 * control_point->size());
    return result;
}

QVector3D glCanvas::revertPoint(QVector3D point)
{
    x0 = QVector3D(-control_point->size(),-control_point->size(),-control_point->size());
    QVector3D result = x0 + 2 * control_point->size() * point;
    return result;
}

void glCanvas::updateOBJ()
{
    int nPoint = obj->V.size();
    int l = control_point->x();
    int m = control_point->y();
    int n = control_point->z();

    for(int p = 0; p < nPoint; p ++){
        QVector3D obj_p = convertPoint(obj->ori_V[p]);
        float s,t,u;
        s = obj_p.x();
        t = obj_p.y();
        u = obj_p.z();

        QVector3D newp = QVector3D(0,0,0);

        for(int i = 0; i < l; i ++)
            for(int j = 0; j < m; j ++)
                for(int k = 0; k < n; k ++){
                    QVector3D control_p = convertPoint(control_point->getPosition(i, j, k));
                    float Bi = Bernstein(l-1,i,s);
                    float Bj = Bernstein(m-1,j,t);
                    float Bk = Bernstein(n-1,k,u);
                    newp = newp + Bi * Bj * Bk * control_p;
                }
        obj->V[p] = revertPoint(newp);
    }
}

void glCanvas::troggleColor(){
    isColor = !isColor;
    updateGL();
}

void glCanvas::reset(){
    obj->reset();
    control_point->reset();
    updateGL();
}

void glCanvas::initializeGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(1.0,1.0,1.0,0.0);
    glClearDepth(1.0);

    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);

    glEnableClientState(GL_VERTEX_ARRAY);

    GLfloat light_position[] = { 0.4, 0.5,-0.8,0.0 };
    GLfloat light_ambient [] = { 0.8, 0.4, 0.8, 1.0 };
    GLfloat light_diffuse [] = { 0.5, 0.6, 1.0, 1.0 };
    GLfloat light_specular[] = { 0.8, 0.8, 0.8, 1.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT , light_ambient );
    glLightfv(GL_LIGHT0, GL_DIFFUSE , light_diffuse );
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);


    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void glCanvas::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    glRotatef(obj->rotateX,1,0,0);
    glRotatef(obj->rotateY,0,1,0);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // draw the obj
    for(int i = 0; i < obj->F.size(); i++) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if(obj->F[i].size() == 3){
            glBegin(GL_TRIANGLES);
            if(isColor) glColor3d( 0.0, 0.0, 1.0);
            glNormal3f(obj->VN[obj->F[i][0].vn]);
            glVertex3f(obj->V[obj->F[i][0].v]);

            if(isColor) glColor3d( 1.0, 0.0, 1.0 );
            glNormal3f(obj->VN[obj->F[i][1].vn]);
            glVertex3f(obj->V[obj->F[i][1].v]);

            if(isColor) glColor3d( 1.0, 1.0, 0.0 );
            glNormal3f(obj->VN[obj->F[i][2].vn]);
            glVertex3f(obj->V[obj->F[i][2].v]);
            glEnd();
        }
        else{
            glBegin(GL_QUADS);

            if(isColor) glColor3d( 0.0, 0.0, 1.0);
            glNormal3f(obj->VN[obj->F[i][0].vn]);
            glVertex3f(obj->V[obj->F[i][0].v]);

            if(isColor) glColor3d( 1.0, 0.0, 1.0 );
            glNormal3f(obj->VN[obj->F[i][1].vn]);
            glVertex3f(obj->V[obj->F[i][1].v]);

            if(isColor) glColor3d( 1.0, 1.0, 0.0 );
            glNormal3f(obj->VN[obj->F[i][2].vn]);
            glVertex3f(obj->V[obj->F[i][2].v]);

            if(isColor) glColor3d( 0.0, 1.0, 1.0 );
            glNormal3f(obj->VN[obj->F[i][3].vn]);
            glVertex3f(obj->V[obj->F[i][3].v]);

            glEnd();
        }
    }

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    //draw the lines
    glLineWidth(3.0f);
    glColor3d(0.5, 0.5, 0.5);
    glPolygonMode(GL_FRONT_AND_BACK   ,GL_LINE);

    QVector3D A = control_point->getPosition(0,0,0);
    QVector3D B = control_point->getPosition(0,0,control_point->z() - 1);
    QVector3D C = control_point->getPosition(0, control_point->y() - 1, control_point->z() - 1);
    QVector3D D = control_point->getPosition(0, control_point->y() - 1, 0);
    QVector3D E = control_point->getPosition(control_point->x() - 1, 0, 0);
    QVector3D F = control_point->getPosition(control_point->x() - 1, 0, control_point->z() - 1);
    QVector3D G = control_point->getPosition(control_point->x() - 1, control_point->y() - 1, control_point->z() - 1);
    QVector3D H = control_point->getPosition(control_point->x() - 1, control_point->y() - 1, 0);

    glBegin(GL_QUADS);
        //draw quad ABCD
        glQuad(A, B, C, D);
        //draw line BFGC
        glQuad(B, F, G, C);
        //draw line CGHD
        glQuad(C, G, H, D);
        //draw line DHEA
        glQuad(D, H, E, A);
        //draw line EFBA
        glQuad(E, F, B, A);
        //draw line FEHG
        glQuad(F, E, H, G);
    glEnd();

    //draw the points
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    for(int i = 0; i < control_point->x(); i ++) {
        for(int j = 0; j < control_point->y(); j ++) {
            for(int k = 0; k < control_point->z(); k ++) {
                glColor3f(control_point->getColor(i,j,k));
                glVertex3f(control_point->getPosition(i,j,k));
            }
        }
    }
    glEnd();


    glPointSize(14.0f);
    glColor3d(1.0, 0, 0);
    glBegin(GL_POINT);
    glVertex3d(0,0,0);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3d(1,0,0);
    glVertex3d(0,0,0);
    glVertex3d(1,0,0);
    glColor3d(0,1,0);
    glVertex3d(0,0,0);
    glVertex3d(0,1,0);
    glColor3d(0,0,1);
    glVertex3d(0,0,0);
    glVertex3d(0,0,1);
    glEnd();

}

void glCanvas::mousePressEvent(QMouseEvent *event) {
    mouse_caputured = true;
    mouse_ori_pos = event->pos();
}

void glCanvas::mouseReleaseEvent(QMouseEvent *event) {
    mouse_caputured = false;
}

void glCanvas::mouseMoveEvent(QMouseEvent *event) {
    if(mouse_caputured) {
        float gap_x = event->pos().x() - mouse_ori_pos.x();
        float gap_y = event->pos().y() - mouse_ori_pos.y();
        obj->rotateX -= gap_y / 100;
        obj->rotateY -= gap_x / 100;
    }
    updateGL();
}
