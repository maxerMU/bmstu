#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_bg_button_clicked();

    void on_fg_button_clicked();

    void on_paint_button_clicked();

    void on_delay_button_clicked();

    void on_add_point_button_clicked();

    void on_paint_fig_button_clicked();

    void on_add_hole_clicked();

    void on_pushButton_clicked();

    void on_time_button_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
