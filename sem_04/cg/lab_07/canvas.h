#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QColor>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <stdio.h>
#include <vector>
#include <stdlib.h>

#include "figures.h"
#include "cutter.h"

class canvas : public QWidget
{
    Q_OBJECT
public:
    explicit canvas(QWidget *parent = nullptr);
    ~canvas();
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void clear();
//    void draw_point(long x, long y, QColor fg, QColor bg);
//    void draw_line(long x1, long y1, long x2, long y2, QColor fg, QColor bg);
    void set_bg(const QColor &color);
    void set_seg_col(const QColor &color);
    void set_vis_col(const QColor &color);
    void set_cut_col(const QColor &color);
    void cut();

private:
    QColor bg = QColor(100, 100, 100);
    cutter _cutter = cutter(QColor(0, 0, 0), QColor(0, 0, 0), QColor(0, 0, 0));

signals:

};

#endif // CANVAS_H
