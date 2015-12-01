#ifndef CANVAS_H
#define CANVAS_H

#include <QtOpenGL>
#include <QWidget>
#include <QFileDialog>
#include <QDebug>

#include "glcanvas.h"

namespace Ui {
class Canvas;
}

class Canvas : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = 0);
    ~Canvas();

private slots:
    void on_openButton_clicked();

private:
    Ui::Canvas *ui;
    glCanvas myCanvas;
    // an opengl widget
};

#endif // CANVAS_H
