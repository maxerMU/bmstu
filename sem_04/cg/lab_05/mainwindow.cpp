#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColor>
#include <QColorDialog>
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->fg_view->set_color(QColor(0, 0, 255));
    ui->paint_view->set_color(QColor(255, 0, 0));

    ui->field->set_bg(ui->bg_view->get_color());
    ui->field->set_fg(ui->fg_view->get_color());
    ui->field->set_paint_col(ui->paint_view->get_color());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
        ui->field->finish_figure();
    else if (event->key() == Qt::Key_Shift)
        ui->field->add_hole();
}

void MainWindow::on_bg_button_clicked()
{
    QColorDialog dialog;
    dialog.show();
    dialog.exec();
    ui->bg_view->set_color(dialog.selectedColor());

    ui->field->set_bg(dialog.selectedColor());
}

void MainWindow::on_fg_button_clicked()
{
    QColorDialog dialog;
    dialog.show();
    dialog.exec();
    ui->fg_view->set_color(dialog.selectedColor());

    ui->field->set_fg(dialog.selectedColor());
}

void MainWindow::on_paint_button_clicked()
{
    QColorDialog dialog;
    dialog.show();
    dialog.exec();
    ui->paint_view->set_color(dialog.selectedColor());

    ui->field->set_paint_col(dialog.selectedColor());
}

void MainWindow::on_delay_button_clicked()
{
    ui->field->set_delay(ui->delay_input->text().toInt());
}

void MainWindow::on_add_point_button_clicked()
{
    ui->field->add_point(ui->x_input->text().toInt(), ui->y_input->text().toInt());
}

void MainWindow::on_paint_fig_button_clicked()
{
    ui->field->finish_figure();
}

void MainWindow::on_add_hole_clicked()
{
    ui->field->add_hole();
}

void MainWindow::on_pushButton_clicked()
{
    ui->field->clear();
}

void MainWindow::on_time_button_clicked()
{
    ui->time_list->clear();

    std::vector<double> times;
    ui->field->get_times(times);

    for (double time : times)
        ui->time_list->addItem(QString::number(time));
}
