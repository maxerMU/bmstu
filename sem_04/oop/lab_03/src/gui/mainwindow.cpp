#include <QMessageBox>
#include <QString>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "base_exception.h"
#include "ui_exceptions.h"
#include "commands.h"
#include "abstract_factory.h"
#include "qt_factory.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setup_scene();
    ui->file_inp->setText(QString("data/cube.txt"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setup_scene()
{
    _scene = std::shared_ptr<QGraphicsScene>(new QGraphicsScene(this));
    ui->graphicsView->setScene(_scene.get());
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    _scene->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());

    std::shared_ptr<abstract_factory> factory(new qt_factory(_scene));
    _drawer = factory->create_drawer();
}

void MainWindow::render_scene()
{
    std::shared_ptr<base_command> com(new draw_scene_command(_drawer));

    try
    {
        _facade.execute_command(com);
    }
    catch (base_exception &ex)
    {
        QMessageBox::warning(this, "Error", QString(ex.what()));
    }
}

void MainWindow::on_load_mod_but_clicked()
{
    std::shared_ptr<base_command> com(new load_command(ui->file_inp->text().toStdString()));

    try
    {
        _facade.execute_command(com);
        ui->model_pick->addItem(ui->file_inp->text());

        render_scene();
    }
    catch (base_exception &ex)
    {
        QMessageBox::warning(this, "Error", QString(ex.what()));
    }
}

void MainWindow::on_remove_mod_but_clicked()
{
    std::shared_ptr<base_command> com(new remove_model_command(ui->model_pick->currentIndex()));

    try
    {
        _facade.execute_command(com);
        ui->model_pick->removeItem(ui->model_pick->currentIndex());

        render_scene();
    }
    catch (base_exception &ex)
    {
        QMessageBox::warning(this, "Error", QString(ex.what()));
    }
}

void MainWindow::on_add_cam_but_clicked()
{
    point cam_pos(-ui->graphicsView->width() / 2, -ui->graphicsView->height() / 2, 50);
    std::shared_ptr<base_command> com(new add_camera_command(cam_pos));

    try
    {
        _facade.execute_command(com);

        cams_count++;
        QString str = QString::asprintf("%s%zu", "Camera №", cams_count);
        ui->cam_pick->addItem(str);
    }
    catch (base_exception &ex)
    {
        QMessageBox::warning(this, "Error", QString(ex.what()));
    }
}

void MainWindow::on_set_cam_but_clicked()
{
    std::shared_ptr<base_command> com(new set_camera_command(ui->cam_pick->currentIndex()));

    try
    {
        _facade.execute_command(com);

        render_scene();
    }
    catch (base_exception &ex)
    {
        QMessageBox::warning(this, "Error", QString(ex.what()));
    }
}

void MainWindow::on_remove_cam_but_clicked()
{
    std::shared_ptr<base_command> com(new remove_camera_command(ui->cam_pick->currentIndex()));

    try
    {
        _facade.execute_command(com);
        ui->cam_pick->removeItem(ui->cam_pick->currentIndex());
    }
    catch (base_exception &ex)
    {
        QMessageBox::warning(this, "Error", QString(ex.what()));
    }
}

void MainWindow::scan_move_model_params(double &dx, double &dy, double &dz) const
{
    bool is_double;

    dx = ui->mod_dx_inp->text().toDouble(&is_double);
    if (!is_double)
        throw ui_field_format_exception();

    dy = ui->mod_dy_inp->text().toDouble(&is_double);
    if (!is_double)
        throw ui_field_format_exception();

    dz = ui->mod_dz_inp->text().toDouble(&is_double);
    if (!is_double)
        throw ui_field_format_exception();
}

void MainWindow::scan_scale_model_params(double &kx, double &ky, double &kz) const
{
    bool is_double;

    kx = ui->mod_kx_inp->text().toDouble(&is_double);
    if (!is_double)
        throw ui_field_format_exception();

    ky = ui->mod_ky_inp->text().toDouble(&is_double);
    if (!is_double)
        throw ui_field_format_exception();

    kz = ui->mod_kz_inp->text().toDouble(&is_double);
    if (!is_double)
        throw ui_field_format_exception();
}

void MainWindow::scan_rotate_model_params(double &ox, double &oy, double &oz) const
{
    bool is_double;

    ox = ui->mod_ox_inp->text().toDouble(&is_double);
    if (!is_double)
        throw ui_field_format_exception();

    oy = ui->mod_oy_inp->text().toDouble(&is_double);
    if (!is_double)
        throw ui_field_format_exception();

    oz = ui->mod_oz_inp->text().toDouble(&is_double);
    if (!is_double)
        throw ui_field_format_exception();
}

void MainWindow::on_move_mod_but_clicked()
{
    try
    {
        double dx, dy, dz;
        scan_move_model_params(dx, dy, dz);
        point move(dx, dy, dz);
        size_t index = ui->model_pick->currentIndex();
        std::shared_ptr<base_command> com(new move_model_command(index, move));

        _facade.execute_command(com);

        render_scene();
    }
    catch (base_exception &ex)
    {
        QMessageBox::warning(this, "Error", QString(ex.what()));
    }
}

void MainWindow::on_scale_mod_but_clicked()
{
    try
    {
        double kx, ky, kz;
        scan_scale_model_params(kx, ky, kz);
        point scale(kx, ky, kz);
        size_t index = ui->model_pick->currentIndex();
        std::shared_ptr<base_command> com(new scale_model_command(index, scale));

        _facade.execute_command(com);

        render_scene();
    }
    catch (base_exception &ex)
    {
        QMessageBox::warning(this, "Error", QString(ex.what()));
    }
}

void MainWindow::on_rotate_mod_inp_clicked()
{
    try
    {
        double ox, oy, oz;
        scan_rotate_model_params(ox, oy, oz);
        point rotate(ox, oy, oz);
        size_t index = ui->model_pick->currentIndex();
        std::shared_ptr<base_command> com(new rotate_model_command(index, rotate));

        _facade.execute_command(com);

        render_scene();
    }
    catch (base_exception &ex)
    {
        QMessageBox::warning(this, "Error", QString(ex.what()));
    }
}

void MainWindow::scan_move_camera_params(double &dx, double &dy, double &dz) const
{
    bool is_double;

    dx = ui->cam_dx_inp->text().toDouble(&is_double);
    if (!is_double)
        throw ui_field_format_exception();

    dy = ui->cam_dy_inp->text().toDouble(&is_double);
    if (!is_double)
        throw ui_field_format_exception();

    dz = ui->cam_dz_inp->text().toDouble(&is_double);
    if (!is_double)
        throw ui_field_format_exception();
}

void MainWindow::on_move_cam_but_clicked()
{
    try
    {
        double dx, dy, dz;
        scan_move_camera_params(dx, dy, dz);
        point move(dx, dy, dz);
        size_t index = ui->cam_pick->currentIndex();
        std::shared_ptr<base_command> com(new move_camera_command(index, move));

        _facade.execute_command(com);

        render_scene();
    }
    catch (base_exception &ex)
    {
        QMessageBox::warning(this, "Error", QString(ex.what()));
    }
}
