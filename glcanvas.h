#ifndef GLCANVAS_H
#define GLCANVAS_H

#include <QWidget>
#include <QPainter>
#include <QtOpenGL>
#include <QString>
#include <QDebug>
#include "obj3d.h"

class glCanvas : public QGLWidget
{
    Q_OBJECT
public:
    explicit glCanvas(QGLWidget *parent = 0);
    ~glCanvas();
    void open(QString fileName);

signals:

public slots:

protected:
    void paintGL();
    obj3d *obj;
private:
    void assemble();
};

#endif // GLCANVAS_H
