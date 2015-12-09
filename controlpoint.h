#ifndef CONTROLPOINT_H
#define CONTROLPOINT_H

#include <QVector>
#include <QVector3D>
#include <QDebug>

typedef struct aPoint{
    QVector3D position;
    QVector3D ori_position;
    QVector3D color;
} apoint;

class controlPoint
{
public:
    controlPoint();
    void update(int x, int y, int z, float s);
    void reset();
    QVector3D getPosition(QVector3D p);
    QVector3D getPosition(int x, int y, int z);
    QVector3D getOriPosition(int x, int y, int z);
    void setColor(QVector3D p, QVector3D color);
    QVector3D getColor(QVector3D p);
    QVector3D getColor(int x, int y, int z);
    void updatePoint(QVector3D p, QVector3D add);
    float size();
    int x();
    int y();
    int z();
private:
    QVector<QVector<QVector<apoint> > > point;
    float pSize;
    int num_x;
    int num_y;
    int num_z;
};

#endif // CONTROLPOINT_H
