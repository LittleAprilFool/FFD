#ifndef GLCANVAS_H
#define GLCANVAS_H

#include <QWidget>
#include <QPainter>
#include <QString>
#include <QDebug>
#include <QPoint>
#include <QVector3D>
#include "obj3d.h"
#include "controlpoint.h"
#include "glpaint.h"

using namespace glPaint;

class glCanvas : public QGLWidget
{
    Q_OBJECT
public:
    explicit glCanvas(QGLWidget *parent = 0);
    ~glCanvas();
    void open(QString fileName);
    void updateControlPoint(int x, int y, int z, float size);
    void updateFocusPoint(int x, int y, int z);
    void updateFocusPointPosition(int x, int y, int z);
    QVector3D getFocusPointPosition(int x, int y, int z);
    void reset();
    void troggleColor();

signals:

public slots:

protected:
    void paintGL() override;
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    obj3d *obj;
    controlPoint *control_point;
    bool mouse_caputured;
    QPoint mouse_ori_pos;
    QVector3D focus_point;
    QVector3D x0;
    QVector3D convertPoint(QVector3D point);
    QVector3D revertPoint(QVector3D point);
    void updateOBJ();
    bool isColor;
};

#endif // GLCANVAS_H
