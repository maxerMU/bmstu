#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QColor>
#include <QPainter>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <QMouseEvent>
#include <QKeyEvent>

#include "polygon.h"
#include "figure.h"

enum add_state_t
{
    NEW,
    ADD,
};

class canvas : public QWidget
{
    Q_OBJECT
public:
    explicit canvas(QWidget *parent = nullptr);
    ~canvas();
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void finish_figure();
    void add_hole();

    void get_times(std::vector<double> &times);

    void clear();

    void set_bg(const QColor &color);
    void set_fg(const QColor &color);
    void set_paint_col(const QColor &color);

    void set_delay(size_t delay);

    void add_point(long x, long y);

private:
    void redraw();
    QImage *image = nullptr;

    std::vector<polygon *> shapes;

    QColor bg;
    QColor fg;
    QColor paint_col;

    size_t delay = 0;

    add_state_t add_state = NEW;
    bool fill_state = false;
signals:

};

#endif // CANVAS_H
