#include <QString>
#include <QPainter>
#include <QImage>
#include <QPixmap>
#include <QGraphicsScene>
#include <QMessageBox>
#include <stdio.h>
#include "figure.h"
#include "errors.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->dx_input->setPlaceholderText(QString("dx"));
    ui->dy_input->setPlaceholderText(QString("dy"));
    ui->dz_input->setPlaceholderText(QString("dz"));
    ui->sxc_input->setPlaceholderText(QString("xc"));
    ui->syc_input->setPlaceholderText(QString("yc"));
    ui->szc_input->setPlaceholderText(QString("zc"));
    ui->kx_input->setPlaceholderText(QString("kx"));
    ui->ky_input->setPlaceholderText(QString("ky"));
    ui->kz_input->setPlaceholderText(QString("kz"));
    ui->rxc_input->setPlaceholderText(QString("xc"));
    ui->ryc_input->setPlaceholderText(QString("yc"));
    ui->rzc_input->setPlaceholderText(QString("zc"));
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
}


void MainWindow::on_read_btn_clicked()
{
    FILE *f = fopen(ui->infile_input->text().toStdString().c_str(), "r");
    if (!f)
        no_file_msg();
    else
    {
        int rc = figure_manager(READ, f);
        if (rc == EMPTY_FIGURE)
            wrong_format_msg();
        else
            draw();

        fclose(f);
    }
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
    FILE *f = fopen(ui->outfile_input->text().toStdString().c_str(), "w");
    figure_manager(WRITE, f);
    fclose(f);
}

void MainWindow::draw()
{
    ui->graphicsView->items().clear();
    QImage image(761, 751, QImage::Format_RGB32);
    image.fill(0);
    QPainter painter(&image);
    painter.setPen(QColor(255, 255, 255));

    display_edge_t edge;
    int rc = figure_manager(GET_DISP_EDGE, 0, &edge);
    for (size_t i = 1; rc != WRONG_EDGE_INDEX; i++)
    {
        painter.drawLine(edge.p1.x, edge.p1.y, edge.p2.x, edge.p2.y);
        rc = figure_manager(GET_DISP_EDGE, i, &edge);
    }


    QPixmap pixmap = QPixmap::fromImage(image);
    scene->addPixmap(pixmap);

    ui->graphicsView->setScene(scene);
}

void MainWindow::on_move_btn_clicked()
{
    move_t move;
    move.dx = ui->dx_input->text().toDouble();
    move.dy = ui->dy_input->text().toDouble();
    move.dz = ui->dz_input->text().toDouble();

    figure_manager(MOVE, move);

    draw();
}

void MainWindow::on_scale_btn_clicked()
{
    scale_t scale;
    scale.xc = ui->sxc_input->text().toDouble();
    scale.yc = ui->syc_input->text().toDouble();
    scale.zc = ui->szc_input->text().toDouble();
    scale.kx = ui->kx_input->text().toDouble();
    scale.ky = ui->ky_input->text().toDouble();
    scale.kz = ui->kz_input->text().toDouble();

    figure_manager(SCALE, scale);

    draw();
}


void MainWindow::on_rotate_btn_clicked()
{
    rotate_t rotate;
    rotate.xc = ui->rxc_input->text().toDouble();
    rotate.yc = ui->ryc_input->text().toDouble();
    rotate.zc = ui->rzc_input->text().toDouble();
    rotate.xy_angle = ui->xy_ang_input->text().toDouble();
    rotate.xz_angle = ui->xz_ang_input->text().toDouble();
    rotate.yz_angle = ui->yz_ang_input->text().toDouble();

    figure_manager(ROTATE, rotate);

    draw();
}
