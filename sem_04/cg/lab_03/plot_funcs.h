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

#endif // PLOT_FUNCS_H
