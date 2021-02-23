#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "epycycloide.h"
#include "canvas.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    canvas *field;
    epycycloide *ep;


private slots:
    void on_move_btn_clicked();

    void on_scale_btn_clicked();

    void on_turn_btn_clicked();

    void on_back_btn_clicked();

private:
    Ui::MainWindow *ui;

    void write_center();
};
#endif // MAINWINDOW_H
