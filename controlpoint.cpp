#include "controlpoint.h"

controlPoint::controlPoint()
{
    update(2, 2, 2, 0.5);
}

void controlPoint::reset(){
    for(int i = 0; i < num_x;i++)
        for(int j = 0; j < num_y;j++)
            for(int k = 0; k < num_z;k++)
                point[i][j][k].position = point[i][j][k].ori_position;
}

QVector3D controlPoint::getPosition(QVector3D p){
    QVector3D result;
    result = point[int(p.x())][int(p.y())][int(p.z())].position;
    return result;
}

QVector3D controlPoint::getPosition(int x, int y, int z){
    QVector3D result;
    result = point[x][y][z].position;
    return result;
}

QVector3D controlPoint::getOriPosition(int x, int y, int z){
    QVector3D result = point[x][y][z].ori_position;
    return result;
}

QVector3D controlPoint::getColor(QVector3D p)
{
    return point[int(p.x())][int(p.y())][int(p.z())].color;
}

QVector3D controlPoint::getColor(int x, int y, int z)
{
    return point[x][y][z].color;
}

float controlPoint::size(){
    return pSize;
}

int controlPoint::x(){
    return num_x;
}

int controlPoint::y(){
    return num_y;
}

int controlPoint::z(){
    return num_z;
}

void controlPoint::setColor(QVector3D p, QVector3D color)
{
    point[int(p.x())][int(p.y())][int(p.z())].color = color;
}

void controlPoint::updatePoint(QVector3D p, QVector3D add)
{
    point[int(p.x())][int(p.y())][int(p.z())].position = point[int(p.x())][int(p.y())][int(p.z())].ori_position + add;
}

void controlPoint::update(int x, int y, int z, float s){
    num_x = x;
    num_y = y;
    num_z = z;
    pSize = s;
    point.clear();
    for(int i = 0; i < x; i ++) {
        QVector<QVector<apoint> > ppp;
        for(int j = 0; j < y; j ++) {
            QVector<apoint> pp;
            for(int k = 0; k < z; k ++) {
              QVector3D position(-s + 2 * s / (x-1) * i, -s + 2 * s / (y-1) * j, -s + 2 * s / (z-1) * k);
              QVector3D color(1,0,0);
              QVector3D ori = position;
              apoint p;
              p.position = position;
              p.color = color;
              p.ori_position = position;
              pp.append(p);
            }
            ppp.append(pp);
        }
        point.append(ppp);
    }
}

