#include <iostream>
#include <math.h>
#include <QMessageBox>
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

    ep = new epycycloide(0, 2 * M_PI, M_PI / 96, 20, 60, *field);
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
    bool ok;
    double dx = ui->dx_input->text().toDouble(&ok);
    if (!ok)
    {
        type_error_msg();
        return;
    }
    double dy = ui->dy_input->text().toDouble(&ok);
    if (!ok)
    {
        type_error_msg();
        return;
    }

    ep->move(dx, dy, true);
    //ep->draw();
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
    bool ok;
    double xm = ui->xc_input->text().toDouble(&ok);
    if (!ok)
    {
        type_error_msg();
        return;
    }
    double ym = ui->yc_input->text().toDouble(&ok);
    if (!ok)
    {
        type_error_msg();
        return;
    }
    double kx = ui->kx_input->text().toDouble(&ok);
    if (!ok)
    {
        type_error_msg();
        return;
    }
    double ky = ui->ky_input->text().toDouble(&ok);
    if (!ok)
    {
        type_error_msg();
        return;
    }

    ep->scale(xm, ym, kx, ky, true);
    //ep->draw();
    write_center();
}

void MainWindow::on_turn_btn_clicked()
{
    bool ok;
    double xm = ui->xc_input->text().toDouble(&ok);
    if (!ok)
    {
        type_error_msg();
        return;
    }
    double ym = ui->yc_input->text().toDouble(&ok);
    if (!ok)
    {
        type_error_msg();
        return;
    }
    double angle = ui->angle_input->text().toDouble(&ok);
    if (!ok)
    {
        type_error_msg();
        return;
    }

    ep->rotate(xm, ym, angle, true);
    //ep->draw();
    write_center();
}

void MainWindow::on_back_btn_clicked()
{
    if (!ep->is_empty_history())
    {
        ep->back();
        write_center();
    }
    else
        empty_history_msg();
}

void MainWindow::on_center_btn_clicked()
{
    ep->move_to_center(true);
    //ep->draw();
    write_center();
}

void MainWindow::on_start_btn_clicked()
{
    ep->to_begining(true);
    //ep->draw();
    write_center();
}

void MainWindow::empty_history_msg()
{
    QMessageBox msg;
    msg.setText(QString("Вы находитесь в начальном состоянии"));
    msg.exec();
}

void MainWindow::task_msg()
{
    QMessageBox msg;
    msg.setText(QString("Нарисовать эпициклоиду, осуществить ее перенос, масштабирование и поворот.\n"
                        "Используется экранная система координат."));
    msg.exec();
}

void MainWindow::type_error_msg()
{
    QMessageBox msg;
    msg.setText(QString("В качестве параметров преобразования допускаются только числа.\n"
                        "Для отделения целой части от дробной в вещественных числах использовать точку."));
    msg.exec();
}

void MainWindow::on_task_btn_clicked()
{
    task_msg();
}
