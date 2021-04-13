#ifndef PLOT_FUNCS_H
#define PLOT_FUNCS_H

#include <QPoint>
#include <QColor>
#include "canvas.h"

struct plot_params_t
{
    canvas *field;
    QColor fg;
    QColor bg;

    explicit plot_params_t(canvas *field, QColor fg, QColor bg);
};

void set_intence(plot_params_t &params, int intence);
void plot_line(const plot_params_t &params, long x1, long y1, long x2, long y2);
void plot_point(const plot_params_t &params, long x, long y);
void plot_circle(const plot_params_t &params, long xc, long yc, long r);
void plot_ellipse(const plot_params_t &params, long xc, long yc, long a, long b);
void plot_mirror_points(const plot_params_t &params, long x, long y, long xc, long yc);

#endif // PLOT_FUNCS_H
