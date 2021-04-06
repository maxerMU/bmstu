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
    params.field->draw_line(x1, y1, x2, y2, params.fg, params.bg, 1);
}

void plot_point(const plot_params_t &params, long x, long y)
{
    params.field->draw_point(x, y, params.fg, params.bg, 1);
}
