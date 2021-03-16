#include <iostream>
#include <QColorDialog>
#include <QColor>
#include <QString>
#include "mainwindow.h"
#include "ui_mainwindow.h"

enum method_t
{
    CDA,
    BREZ_REAL,
    BREZ_INT,
    BREZ_DEL,
    VU,
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
    bg = new color_view(this);
    bg->setGeometry(QRect(610, 80, 21, 21));

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
    else if (ui->method_select->currentIndex() == LIB)
        draw(fg_color, bg_color, lib);
}

void MainWindow::draw(const QColor &fg, const QColor &bg, draw_func_t draw_func)
{
    ui->graphicsView->items().clear();
    QImage image(481, 521, QImage::Format_RGB32);
    image.fill(bg);
    QPainter painter(&image);
    painter.setPen(fg);

    int x1 = ui->x1_input->text().toInt();
    int x2 = ui->x2_input->text().toInt();
    int y1 = ui->y1_input->text().toInt();
    int y2 = ui->y2_input->text().toInt();
    QPoint p1(x1, y1);
    QPoint p2(x2, y2);

    draw_func(painter, p1, p2);

    QPixmap pixmap = QPixmap::fromImage(image);
    scene->addPixmap(pixmap);

    ui->graphicsView->setScene(scene);
}
