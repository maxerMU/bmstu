#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "figure.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_read_btn_clicked();

    void on_write_btn_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    void draw();

    void no_file_msg();
    void wrong_format_msg();
};
#endif // MAINWINDOW_H