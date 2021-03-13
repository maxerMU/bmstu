#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "manager.h"
#include "convert.h"

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

    void on_move_btn_clicked();

    void on_scale_btn_clicked();

    void on_rotate_btn_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    display_figure_t display_figure;

    void draw();

    void no_file_msg();
    void wrong_format_msg();
};
#endif // MAINWINDOW_H
