#include <iostream>
#include <math.h>
#include <QColorDialog>
#include <QColor>
#include <QString>
#include "cir_methods_time.h"
#include "el_methods_time.h"
#include "circle_methods.h"
#include "ellipse_methods.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

enum method_t
{
    CANONIC,
    PARAM,
    BREZ,
    MID_POINT,
    LIB,
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene();

    fg = new color_view(this);
    fg->setGeometry(QRect(1110, 40, 21, 21));
    fg->set_color(QColor(0, 0, 0));
    bg = new color_view(this);
    bg->setGeometry(QRect(1110, 80, 21, 21));

    field = new canvas(this);
    field->setGeometry(QRect(10, 20, 971, 961));

    ui->method_select->addItem(QString("Каноническое уравнение"));
    ui->method_select->addItem(QString("Параметрическое уравнение"));
    ui->method_select->addItem(QString("Брезенхем"));
    ui->method_select->addItem(QString("Средняя точка"));
    ui->method_select->addItem(QString("Библиотечный"));

    ui->xcec_input->setPlaceholderText(QString("xc"));
    ui->ycec_input->setPlaceholderText(QString("yc"));
    ui->xce_input->setPlaceholderText(QString("xc"));
    ui->yce_input->setPlaceholderText(QString("yc"));
    ui->xcoc_input->setPlaceholderText(QString("xc"));
    ui->ycoc_input->setPlaceholderText(QString("yc"));
    ui->xco_input->setPlaceholderText(QString("xc"));
    ui->yco_input->setPlaceholderText(QString("yc"));

//    ui->xce_input->setText(QString("500"));
//    ui->yce_input->setText(QString("400"));
//    ui->a_input->setText(QString("100"));
//    ui->b_input->setText(QString("50"));
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

void MainWindow::on_time_btn_clicked()
{
    //const char *circle_file_name = "circle_time_res.txt";
    //circle_time_table(circle_file_name, 10, 400, 1);
    //const char *ellipse_file_name = "ellipse_time_res.txt";
    //ellipse_time_table(ellipse_file_name, 10, 5, 1, 390);
    system("python3 time.py");
}

void MainWindow::on_clr_btn_clicked()
{
    field->clear();
}

void MainWindow::on_draw_circle_btn_clicked()
{
    QColor fg_color;
    fg->get_color(fg_color);

    QColor bg_color;
    bg->get_color(bg_color);

    int x = ui->xco_input->text().toInt();
    int y = ui->yco_input->text().toInt();
    int r = ui->r_input->text().toInt();

    field->set_bg(bg_color);
    plot_params_t params(field, fg_color, bg_color);

    if (ui->method_select->currentIndex() == CANONIC)
        circle_canon(params, x, y, r);
    else if (ui->method_select->currentIndex() == PARAM)
        circle_param(params, x, y, r);
    else if (ui->method_select->currentIndex() == BREZ)
        circle_brez(params, x, y, r);
    else if (ui->method_select->currentIndex() == MID_POINT)
        circle_mid(params, x, y, r);
    else if (ui->method_select->currentIndex() == LIB)
        circle_lib(params, x, y, r);
}

void MainWindow::on_draw_ellipse_btn_clicked()
{
    QColor fg_color;
    fg->get_color(fg_color);

    QColor bg_color;
    bg->get_color(bg_color);

    long xc = ui->xce_input->text().toInt();
    long yc = ui->yce_input->text().toInt();
    long px = ui->a_input->text().toInt();
    long py = ui->b_input->text().toInt();

    field->set_bg(bg_color);
    plot_params_t params(field, fg_color, bg_color);

    if (ui->method_select->currentIndex() == CANONIC)
        ellipse_canon(params, xc, yc, px, py);
    else if (ui->method_select->currentIndex() == PARAM)
        ellipse_param(params, xc, yc, px, py);
    else if (ui->method_select->currentIndex() == BREZ)
        ellipse_brez(params, xc, yc, px, py);
    else if (ui->method_select->currentIndex() == MID_POINT)
        ellipse_mid(params, xc, yc, px, py);
    else if (ui->method_select->currentIndex() == LIB)
        ellipse_lib(params, xc, yc, px, py);
}

void MainWindow::on_draw_concircle_btn_clicked()
{
    QColor fg_color;
    fg->get_color(fg_color);

    QColor bg_color;
    bg->get_color(bg_color);

    field->set_bg(bg_color);
    plot_params_t params(field, fg_color, bg_color);

    if (ui->method_select->currentIndex() == CANONIC)
        draw_con_circle(params, circle_canon);
    else if (ui->method_select->currentIndex() == PARAM)
        draw_con_circle(params, circle_param);
    else if (ui->method_select->currentIndex() == BREZ)
        draw_con_circle(params, circle_brez);
    else if (ui->method_select->currentIndex() == MID_POINT)
        draw_con_circle(params, circle_mid);
    else if (ui->method_select->currentIndex() == LIB)
        draw_con_circle(params, circle_lib);
}

void MainWindow::draw_con_circle(const plot_params_t &params, circle_func draw_func)
{
    long xc = ui->xcoc_input->text().toInt();
    long yc = ui->ycoc_input->text().toInt();
    long rmin = ui->rstart_input->text().toInt();
    long rmax = ui->rend_input->text().toInt();
    long step = ui->rstep_input->text().toInt();

    for (long r = rmin; r < rmax; r += step)
        draw_func(params, xc, yc, r);
}

void MainWindow::on_draw_con_ellipse_btn_clicked()
{
    QColor fg_color;
    fg->get_color(fg_color);

    QColor bg_color;
    bg->get_color(bg_color);

    field->set_bg(bg_color);
    plot_params_t params(field, fg_color, bg_color);

    if (ui->method_select->currentIndex() == CANONIC)
        draw_con_ellipse(params, ellipse_canon);
    else if (ui->method_select->currentIndex() == PARAM)
        draw_con_ellipse(params, ellipse_param);
    else if (ui->method_select->currentIndex() == BREZ)
        draw_con_ellipse(params, ellipse_brez);
    else if (ui->method_select->currentIndex() == MID_POINT)
        draw_con_ellipse(params, ellipse_mid);
    else if (ui->method_select->currentIndex() == LIB)
        draw_con_ellipse(params, ellipse_lib);
}

void MainWindow::draw_con_ellipse(const plot_params_t &params, ellipse_func_t draw_func)
{
    long xc = ui->xcec_input->text().toInt();
    long yc = ui->ycec_input->text().toInt();
    long px = ui->mina_input->text().toInt();
    long py = ui->minb_input->text().toInt();
    long step = ui->step_a_input->text().toInt();
    long n = ui->n_input->text().toInt();

    bool flag = (py > px);

    double e_sqr;
    if (flag)
        e_sqr = 1 - (px * px) / double (py * py);
    else
        e_sqr = 1 - (py * py) / double (px * px);

    for (long i = 0; i < n; i++)
    {
        draw_func(params, xc, yc, px, py);

        px += step;
        if (flag)
            py = round(sqrt(px * px / (1 - e_sqr)));
        else
            py = round(sqrt(px * px * (1 - e_sqr)));
    }
}
