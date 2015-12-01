#include "canvas.h"
#include "ui_canvas.h"

Canvas::Canvas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Canvas)
{
    ui->setupUi(this);
    ui->layout->addWidget(&myCanvas);
}

Canvas::~Canvas()
{
    delete ui;
}

void Canvas::on_openButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("open file"), " ",  tr("obj_file(*.obj)"));
    myCanvas.open(fileName);
}
