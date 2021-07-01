#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(this, SIGNAL(button_presed(long)), &_lift, SLOT(floor_but_clicked(long)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    emit button_presed(1);
}

void MainWindow::on_pushButton_2_clicked()
{
    emit button_presed(2);
}

void MainWindow::on_pushButton_3_clicked()
{
    emit button_presed(3);
}

void MainWindow::on_pushButton_4_clicked()
{
    emit button_presed(4);
}

void MainWindow::on_pushButton_5_clicked()
{
    emit button_presed(5);
}
