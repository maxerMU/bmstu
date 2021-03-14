#include <string.h>
#include <QString>
#include <QPainter>
#include <QImage>
#include <QPixmap>
#include <QGraphicsScene>
#include <QMessageBox>
#include <stdio.h>
#include "manager.h"
#include "errors.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      display_figure(init_display_figure())
{
    ui->setupUi(this);

    ui->dx_input->setPlaceholderText(QString("dx"));
    ui->dy_input->setPlaceholderText(QString("dy"));
    ui->dz_input->setPlaceholderText(QString("dz"));
    ui->kx_input->setPlaceholderText(QString("kx"));
    ui->ky_input->setPlaceholderText(QString("ky"));
    ui->kz_input->setPlaceholderText(QString("kz"));
    ui->xy_ang_input->setPlaceholderText(QString("xy angle"));
    ui->xz_ang_input->setPlaceholderText(QString("xz angle"));
    ui->yz_ang_input->setPlaceholderText(QString("yz angle"));
    ui->infile_input->setPlaceholderText(QString("input file name"));
    ui->outfile_input->setPlaceholderText(QString("out file name"));

    scene = new QGraphicsScene();
}

MainWindow::~MainWindow()
{
    delete ui;

    delete scene;

    parameters_t params;
    figure_manager(display_figure, FREE, params);
}


void MainWindow::on_read_btn_clicked()
{
    parameters_t params;
    params.file_name = strdup(ui->infile_input->text().toStdString().c_str());
    int rc = figure_manager(display_figure, READ, params);
    if (rc == OPEN_ER)
        no_file_msg();
    else if (rc == FIGURE_READ_ER)
        wrong_format_msg();
    else if (!rc)
        draw();
}

void MainWindow::no_file_msg()
{
    QMessageBox msg;
    msg.setText(QString("no such file"));
    msg.exec();
}

void MainWindow::wrong_format_msg()
{
    QMessageBox msg;
    msg.setText(QString("wrong format"));
    msg.exec();
}

void MainWindow::on_write_btn_clicked()
{
    parameters_t params;
    params.file_name = strdup(ui->outfile_input->text().toStdString().c_str());
    figure_manager(display_figure, WRITE, params);
}

void MainWindow::draw()
{
    ui->graphicsView->items().clear();
    QImage image(761, 751, QImage::Format_RGB32);
    image.fill(0);
    QPainter painter(&image);
    painter.setPen(QColor(255, 255, 255));

    parameters_t params;
    figure_manager(display_figure, GET_DISP_FIGURE, params);
    for (size_t i = 0; i < display_figure.edges.size; i++)
    {
        painter.drawLine(display_figure.points.disp_points[display_figure.edges.edges[i].p1].x,
                         display_figure.points.disp_points[display_figure.edges.edges[i].p1].y,
                         display_figure.points.disp_points[display_figure.edges.edges[i].p2].x,
                         display_figure.points.disp_points[display_figure.edges.edges[i].p2].y);

    }


    QPixmap pixmap = QPixmap::fromImage(image);
    scene->addPixmap(pixmap);

    ui->graphicsView->setScene(scene);

    free_display_figure(display_figure);
}

void MainWindow::on_move_btn_clicked()
{
    move_t move;
    move.dx = ui->dx_input->text().toDouble();
    move.dy = ui->dy_input->text().toDouble();
    move.dz = ui->dz_input->text().toDouble();

    parameters_t params;
    params.move_params = move;

    figure_manager(display_figure, MOVE, params);

    draw();
}

void MainWindow::on_scale_btn_clicked()
{
    scale_t scale;
    scale.kx = ui->kx_input->text().toDouble();
    scale.ky = ui->ky_input->text().toDouble();
    scale.kz = ui->kz_input->text().toDouble();

    parameters_t params;
    params.scale_params = scale;

    figure_manager(display_figure, SCALE, params);

    draw();
}


void MainWindow::on_rotate_btn_clicked()
{
    rotate_t rotate;
    rotate.xy_angle = ui->xy_ang_input->text().toDouble();
    rotate.xz_angle = ui->xz_ang_input->text().toDouble();
    rotate.yz_angle = ui->yz_ang_input->text().toDouble();

    parameters_t params;
    params.rotate_params = rotate;

    figure_manager(display_figure, ROTATE, params);

    draw();
}
