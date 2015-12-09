#ifndef CANVAS_H
#define CANVAS_H

#include <QtOpenGL>
#include <QWidget>
#include <QFileDialog>
#include <QDebug>
#include <QVector3D>

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

    //open an obj file
    void on_openButton_clicked();

    //editing number of control points
    void on_x_side_editingFinished();

    void on_y_side_editingFinished();

    void on_z_side_editingFinished();

    //editing focus control point
    void on_spin_x_editingFinished();

    void on_spin_y_editingFinished();

    void on_spin_z_editingFinished();

    //editing position of focused control point
    void on_cp_x_sliderMoved(int position);

    void on_cp_y_sliderMoved(int position);

    void on_cp_z_sliderMoved(int position);

    void on_cp_x_sliderReleased();

    void on_cp_y_sliderReleased();

    void on_cp_z_sliderReleased();

    //reset everything
    void on_reset_clicked();

    void on_xyz_size_editingFinished();

    void on_pushButton_clicked();

    void on_color_clicked();

private:
    Ui::Canvas *ui;
    glCanvas myCanvas;
    void reset();
    void update_cp(int x, int y, int z);
    void update_cp(QVector3D p);
    // an opengl widget
};

#endif // CANVAS_H
