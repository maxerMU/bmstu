#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
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

private slots:
    void on_seg_col_btn_clicked();

    void on_vis_part_col_btn_clicked();

    void on_cut_col_btn_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QColor seg_col = QColor(0, 0, 0);
    QColor vis_col = QColor(255, 0, 0);
    QColor cut_col = QColor(0, 127, 0);
};
#endif // MAINWINDOW_H
