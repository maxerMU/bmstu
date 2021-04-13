#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "color_view.h"
#include "canvas.h"
#include "plot_funcs.h"
#include "circle_methods.h"
#include "ellipse_methods.h"

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
    void on_pick_fg_color_btn_clicked();

    void on_pick_bg_color_btn_clicked();

    void on_time_btn_clicked();

    void on_clr_btn_clicked();

    void on_draw_circle_btn_clicked();

    void on_draw_ellipse_btn_clicked();

    void on_draw_concircle_btn_clicked();

    void on_draw_con_ellipse_btn_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    color_view *fg;
    color_view *bg;
    canvas *field;

    void draw_con_circle(const plot_params_t &params, circle_func draw_func);
    void draw_con_ellipse(const plot_params_t &params, ellipse_func_t draw_func);
};
#endif // MAINWINDOW_H
