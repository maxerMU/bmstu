#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <stdlib.h>
#include <memory>

#include "facade.h"
#include "base_drawer.h"

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
    void on_load_mod_but_clicked();

    void on_remove_mod_but_clicked();

    void on_add_cam_but_clicked();

    void on_set_cam_but_clicked();

    void on_remove_cam_but_clicked();

    void on_move_mod_but_clicked();

    void on_scale_mod_but_clicked();

    void on_rotate_mod_inp_clicked();

    void on_move_cam_but_clicked();

    void on_rotate_cam_btn_clicked();

private:
    void setup_scene();
    void render_scene();
    void scan_move_model_params(double &dx, double &dy, double &dz) const;
    void scan_scale_model_params(double &kx, double &ky, double &kz) const;
    void scan_rotate_model_params(double &ox, double &oy, double &oz) const;
    void scan_move_camera_params(double &dx, double &dy, double &dz) const;
    void scan_rotate_camera_params(double &ox, double &oy, double &oz) const;

    Ui::MainWindow *ui;

    facade _facade;

    size_t cams_count = 0;

    std::shared_ptr<QGraphicsScene> _scene;
    std::shared_ptr<base_drawer> _drawer;
};
#endif // MAINWINDOW_H
