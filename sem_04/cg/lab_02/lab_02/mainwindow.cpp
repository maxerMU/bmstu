#include <iostream>
#include <math.h>
#include <QString>
#include <QDebug>
#include <QStringList>
#include <QTableWidgetItem>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvas.h"
#include "epycycloide.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dx_input->setPlaceholderText(QString("dx"));
    ui->dy_input->setPlaceholderText(QString("dy"));
    ui->xc_input->setPlaceholderText(QString("xc"));
    ui->yc_input->setPlaceholderText(QString("yc"));
    ui->kx_input->setPlaceholderText(QString("kx"));
    ui->ky_input->setPlaceholderText(QString("ky"));
    ui->angle_input->setPlaceholderText(QString("angle"));
    QStringList labels;
    labels.append(QString("x"));
    labels.append(QString("y"));
    ui->center_table->setHorizontalHeaderLabels(labels);

    field = new canvas(this);
    field->setGeometry(QRect(10, 30, 731, 731));

    ep = new epycycloide(0, 2 * M_PI, M_PI / 96, 50, 150, *field);
    write_center();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete field;
    delete ep;
}


void MainWindow::on_move_btn_clicked()
{
    double dx = ui->dx_input->text().toDouble();
    double dy = ui->dy_input->text().toDouble();

    ep->move(dx, dy, true);
    ep->draw();
    write_center();
}

void MainWindow::write_center()
{
    double xc, yc;
    ep->find_center(xc, yc);

    QString xstr;
    xstr = xstr.asprintf("%.2lf", xc);
    QTableWidgetItem *itx = new QTableWidgetItem(xstr);
    ui->center_table->setItem(0, 0, itx);

    QString ystr;
    ystr = ystr.asprintf("%.2lf", yc);
    QTableWidgetItem *ity = new QTableWidgetItem(ystr);
    ui->center_table->setItem(0, 1, ity);
}

void MainWindow::on_scale_btn_clicked()
{
    double xm = ui->xc_input->text().toDouble();
    double ym = ui->yc_input->text().toDouble();
    double kx = ui->kx_input->text().toDouble();
    double ky = ui->ky_input->text().toDouble();

    ep->scale(xm, ym, kx, ky, true);
    ep->draw();
    write_center();
}

void MainWindow::on_turn_btn_clicked()
{
    double xm = ui->xc_input->text().toDouble();
    double ym = ui->yc_input->text().toDouble();
    double angle = ui->angle_input->text().toDouble();

    ep->rotate(xm, ym, angle, true);
    ep->draw();
    write_center();
}

void MainWindow::on_back_btn_clicked()
{
    ep->back();
    write_center();
}
