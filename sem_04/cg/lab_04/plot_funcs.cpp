#include "plot_funcs.h"

plot_params_t::plot_params_t(canvas *field, QColor fg, QColor bg)
    : field(field), fg(fg), bg(bg)
{
}

void set_intence(plot_params_t &params, int intence)
{
    params.fg.setAlpha(intence);
}

void plot_line(const plot_params_t &params, long x1, long y1, long x2, long y2)
{
    params.field->draw_line(x1, y1, x2, y2, params.fg, params.bg);
}

void plot_point(const plot_params_t &params, long x, long y)
{
    params.field->draw_point(x, y, params.fg, params.bg);
}

void plot_mirror_points(const plot_params_t &params, long x, long y, long xc, long yc)
{
    plot_point(params, x + xc, y + yc);
    plot_point(params, xc - x, y + yc);
    plot_point(params, x + xc, yc - y);
    plot_point(params, xc - x, yc - y);
}

void plot_circle(const plot_params_t &params, long xc, long yc, long r)
{
    params.field->draw_ellipse(xc - r, yc - r, 2 * r, 2 * r, params.fg, params.bg);
}

void plot_ellipse(const plot_params_t &params, long xc, long yc, long a, long b)
{
    params.field->draw_ellipse(xc - a, yc - b, 2 * a, 2 * b, params.fg, params.bg);
}
