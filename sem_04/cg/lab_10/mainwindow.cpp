#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->func_ind, SIGNAL(currentIndexChanged(int)), &_horizont, SLOT(set_func_index(int)));
    QObject::connect(ui->x_min, SIGNAL(textChanged(QString)), &_horizont, SLOT(set_xmin(QString)));
    QObject::connect(ui->x_max, SIGNAL(textChanged(QString)), &_horizont, SLOT(set_xmax(QString)));
    QObject::connect(ui->x_step, SIGNAL(valueChanged(double)), &_horizont, SLOT(set_xstep(double)));
    QObject::connect(ui->z_min, SIGNAL(textChanged(QString)), &_horizont, SLOT(set_zmin(QString)));
    QObject::connect(ui->z_max, SIGNAL(textChanged(QString)), &_horizont, SLOT(set_zmax(QString)));
    QObject::connect(ui->z_step, SIGNAL(valueChanged(double)), &_horizont, SLOT(set_zstep(double)));

    QObject::connect(ui->x_slider, SIGNAL(valueChanged(int)), ui->x_spin, SLOT(setValue(int)));
    QObject::connect(ui->x_spin, SIGNAL(valueChanged(int)), ui->x_slider, SLOT(setValue(int)));
    QObject::connect(ui->y_slider, SIGNAL(valueChanged(int)), ui->y_spin, SLOT(setValue(int)));
    QObject::connect(ui->y_spin, SIGNAL(valueChanged(int)), ui->y_slider, SLOT(setValue(int)));
    QObject::connect(ui->z_slider, SIGNAL(valueChanged(int)), ui->z_spin, SLOT(setValue(int)));
    QObject::connect(ui->z_spin, SIGNAL(valueChanged(int)), ui->z_slider, SLOT(setValue(int)));

    QObject::connect(ui->x_slider, SIGNAL(valueChanged(int)), &_horizont, SLOT(set_xangle(int)));
    QObject::connect(ui->y_slider, SIGNAL(valueChanged(int)), &_horizont, SLOT(set_yangle(int)));
    QObject::connect(ui->z_slider, SIGNAL(valueChanged(int)), &_horizont, SLOT(set_zangle(int)));

    QObject::connect(ui->x_slider, SIGNAL(valueChanged(int)), ui->pushButton_2, SLOT(click()));
    QObject::connect(ui->y_slider, SIGNAL(valueChanged(int)), ui->pushButton_2, SLOT(click()));
    QObject::connect(ui->z_slider, SIGNAL(valueChanged(int)), ui->pushButton_2, SLOT(click()));

    QObject::connect(ui->field, SIGNAL(resize()), ui->pushButton_2, SLOT(click()));

    ui->func_ind->addItem(QString("cos(x) * sin(z)"));
    ui->func_ind->addItem(QString("exp(sin(sqrt(x * x + z * z)))"));
    ui->func_ind->addItem(QString("x * x - 2 * z"));
    ui->func_ind->addItem(QString("sin(x) * sin(z)"));
    ui->func_ind->addItem(QString("cos(x) * cos(z)"));
    ui->x_min->setText(QString("-5"));
    ui->x_max->setText(QString("5"));
    ui->z_min->setText(QString("-5"));
    ui->z_max->setText(QString("5"));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->field->clear();
    _horizont.find_horizonts(*(ui->field));
}
