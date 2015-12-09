#include "canvas.h"
#include "ui_canvas.h"

Canvas::Canvas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Canvas)
{
    ui->setupUi(this);
    ui->layout->addWidget(&myCanvas);
    reset();
}

Canvas::~Canvas()
{
    delete ui;
}

void Canvas::reset(){
    myCanvas.reset();
    ui->x_side->setText("2");
    ui->y_side->setText("2");
    ui->z_side->setText("2");
    ui->xyz_size->setText("0.5");
    ui->spin_x->setRange(0,1);
    ui->spin_y->setRange(0,1);
    ui->spin_z->setRange(0,1);
    ui->cp_x->setRange(1,100);
    ui->cp_y->setRange(1,100);
    ui->cp_z->setRange(1,100);
    update_cp(50, 50, 50);
}

void Canvas::update_cp(int x, int y, int z)
{
    ui->cp_x->setValue(x);
    ui->cp_y->setValue(y);
    ui->cp_z->setValue(z);
}

void Canvas::update_cp(QVector3D p)
{
    ui->cp_x->setValue(int(p.x()));
    ui->cp_y->setValue(int(p.y()));
    ui->cp_z->setValue(int(p.z()));
}

void Canvas::on_openButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("open file"), " ",  tr("obj_file(*.obj)"));
    myCanvas.open(fileName);
    reset();
}

void Canvas::on_x_side_editingFinished()
{
    myCanvas.updateControlPoint(ui->x_side->text().toInt(), ui->y_side->text().toInt(), ui->z_side->text().toInt(),ui->xyz_size->text().toFloat());
    ui->spin_x->setRange(0,ui->x_side->text().toInt()-1);
    myCanvas.reset();
    update_cp(50, 50, 50);
}

void Canvas::on_y_side_editingFinished()
{
    myCanvas.updateControlPoint(ui->x_side->text().toInt(), ui->y_side->text().toInt(), ui->z_side->text().toInt(),ui->xyz_size->text().toFloat());
    ui->spin_y->setRange(0,ui->y_side->text().toInt()-1);
    myCanvas.reset();
    update_cp(50, 50, 50);
}

void Canvas::on_z_side_editingFinished()
{
    myCanvas.updateControlPoint(ui->x_side->text().toInt(), ui->y_side->text().toInt(), ui->z_side->text().toInt(),ui->xyz_size->text().toFloat());
    ui->spin_z->setRange(0,ui->z_side->text().toInt()-1);
    myCanvas.reset();
    update_cp(50, 50, 50);
}

void Canvas::on_spin_x_editingFinished()
{
    myCanvas.updateFocusPoint(ui->spin_x->text().toInt(),ui->spin_y->text().toInt(),ui->spin_z->text().toInt());
    QVector3D newposition = myCanvas.getFocusPointPosition(ui->spin_x->text().toInt(),ui->spin_y->text().toInt(),ui->spin_z->text().toInt());
    update_cp(newposition);
}

void Canvas::on_spin_y_editingFinished()
{
    myCanvas.updateFocusPoint(ui->spin_x->text().toInt(),ui->spin_y->text().toInt(),ui->spin_z->text().toInt());
    QVector3D newposition = myCanvas.getFocusPointPosition(ui->spin_x->text().toInt(),ui->spin_y->text().toInt(),ui->spin_z->text().toInt());
    update_cp(newposition);
}

void Canvas::on_spin_z_editingFinished()
{
    myCanvas.updateFocusPoint(ui->spin_x->text().toInt(),ui->spin_y->text().toInt(),ui->spin_z->text().toInt());
    QVector3D newposition = myCanvas.getFocusPointPosition(ui->spin_x->text().toInt(),ui->spin_y->text().toInt(),ui->spin_z->text().toInt());
    update_cp(newposition);
}

void Canvas::on_cp_x_sliderMoved(int position)
{
    myCanvas.updateFocusPointPosition(ui->cp_x->value(),ui->cp_y->value(),ui->cp_z->value());
}

void Canvas::on_cp_y_sliderMoved(int position)
{
    myCanvas.updateFocusPointPosition(ui->cp_x->value(),ui->cp_y->value(),ui->cp_z->value());
}

void Canvas::on_cp_z_sliderMoved(int position)
{
    myCanvas.updateFocusPointPosition(ui->cp_x->value(),ui->cp_y->value(),ui->cp_z->value());
}

void Canvas::on_cp_x_sliderReleased()
{
    myCanvas.updateFocusPointPosition(ui->cp_x->value(),ui->cp_y->value(),ui->cp_z->value());
}

void Canvas::on_cp_y_sliderReleased()
{
    myCanvas.updateFocusPointPosition(ui->cp_x->value(),ui->cp_y->value(),ui->cp_z->value());
}

void Canvas::on_cp_z_sliderReleased()
{
    myCanvas.updateFocusPointPosition(ui->cp_x->value(),ui->cp_y->value(),ui->cp_z->value());
}


void Canvas::on_xyz_size_editingFinished()
{

}

void Canvas::on_reset_clicked()
{
    reset();
}

void Canvas::on_pushButton_clicked()
{
     myCanvas.updateFocusPointPosition(50,50,50);
}

void Canvas::on_color_clicked()
{
    myCanvas.troggleColor();
}
