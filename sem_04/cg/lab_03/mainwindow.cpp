#include <iostream>
#include <math.h>
#include <QColorDialog>
#include <QColor>
#include <QString>
#include "methods_time.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

enum method_t
{
    CDA,
    BREZ_REAL,
    BREZ_INT,
    BREZ_DEL,
    WU,
    LIB,
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene();

    fg = new color_view(this);
    fg->setGeometry(QRect(610, 40, 21, 21));
    fg->set_color(QColor(0, 0, 0));
    bg = new color_view(this);
    bg->setGeometry(QRect(610, 80, 21, 21));

    field = new canvas(this);
    field->setGeometry(QRect(10, 20, 491, 531));

    ui->method_select->addItem(QString("ЦДА"));
    ui->method_select->addItem(QString("Брезенхем действительный"));
    ui->method_select->addItem(QString("Брезенхем целочисленный"));
    ui->method_select->addItem(QString("Брезенхем с устранением ступенчатости"));
    ui->method_select->addItem(QString("Ву"));
    ui->method_select->addItem(QString("Библиотечный"));

    ui->x1_input->setPlaceholderText(QString("x1"));
    ui->y1_input->setPlaceholderText(QString("y1"));
    ui->x2_input->setPlaceholderText(QString("x2"));
    ui->y2_input->setPlaceholderText(QString("y2"));
    ui->xc_input->setPlaceholderText(QString("xc"));
    ui->yc_input->setPlaceholderText(QString("yc"));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete fg;
    delete bg;
    delete field;
}


void MainWindow::on_pick_fg_color_btn_clicked()
{
    QColorDialog dialog;
    dialog.show();
    dialog.exec();
    QColor clr = dialog.selectedColor();
    fg->set_color(clr);
}

void MainWindow::on_pick_bg_color_btn_clicked()
{
    QColorDialog dialog;
    dialog.show();
    dialog.exec();
    QColor clr = dialog.selectedColor();
    bg->set_color(clr);
}

void MainWindow::on_draw_line_btn_clicked()
{
    QColor fg_color;
    fg->get_color(fg_color);

    QColor bg_color;
    bg->get_color(bg_color);

    if (ui->method_select->currentIndex() == CDA)
        draw(fg_color, bg_color, cda);
    else if (ui->method_select->currentIndex() == BREZ_REAL)
        draw(fg_color, bg_color, brezenhem_real);
    else if (ui->method_select->currentIndex() == BREZ_INT)
        draw(fg_color, bg_color, brezenhem_int);
    else if (ui->method_select->currentIndex() == BREZ_DEL)
        draw(fg_color, bg_color, brezenhem_del_stair);
    else if (ui->method_select->currentIndex() == WU)
        draw(fg_color, bg_color, wu);
    else if (ui->method_select->currentIndex() == LIB)
        draw(fg_color, bg_color, lib);
}

void MainWindow::draw(const QColor &fg, const QColor &bg, draw_func_t draw_func)
{
    int x1 = ui->x1_input->text().toInt();
    int x2 = ui->x2_input->text().toInt();
    int y1 = ui->y1_input->text().toInt();
    int y2 = ui->y2_input->text().toInt();

    field->set_bg(bg);
    plot_params_t params(field, fg, bg);

    draw_func(params, x1, y1, x2, y2);
}

void MainWindow::on_draw_spectr_btn_clicked()
{
    QColor fg_color;
    fg->get_color(fg_color);

    QColor bg_color;
    bg->get_color(bg_color);

    if (ui->method_select->currentIndex() == CDA)
        draw_spectr(fg_color, bg_color, cda);
    else if (ui->method_select->currentIndex() == BREZ_REAL)
        draw_spectr(fg_color, bg_color, brezenhem_real);
    else if (ui->method_select->currentIndex() == BREZ_INT)
        draw_spectr(fg_color, bg_color, brezenhem_int);
    else if (ui->method_select->currentIndex() == BREZ_DEL)
        draw_spectr(fg_color, bg_color, brezenhem_del_stair);
    else if (ui->method_select->currentIndex() == WU)
        draw_spectr(fg_color, bg_color, wu);
    else if (ui->method_select->currentIndex() == LIB)
        draw_spectr(fg_color, bg_color, lib);
}

void MainWindow::draw_spectr(const QColor &fg, const QColor &bg, draw_func_t draw_func)
{
    int xc = ui->xc_input->text().toInt();
    int yc = ui->yc_input->text().toInt();
    double angle = ui->angle_input->text().toDouble();
    angle = (angle * M_PI) / 180.0;
    double r = ui->radius_input->text().toDouble();

    field->set_bg(bg);
    plot_params_t params(field, fg, bg);

    for (double iang = 0; iang < 2 * M_PI; iang += angle)
    {
        int xe = xc + r * cos(iang);
        int ye = yc - r * sin(iang);

        draw_func(params, xc, yc, xe, ye);
    }

}

void MainWindow::on_time_btn_clicked()
{
    const char *file_name = "time_res.txt";
    time_table(file_name, 15, 50000);
}
