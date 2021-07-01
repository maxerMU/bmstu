#include <math.h>
#include "ellipse_methods.h"

typedef void (*ellipse_brez_step_func_t)(long &, long &, long &, long, long);

void ellipse_lib(const plot_params_t &params, long xc, long yc, long px, long py)
{
    plot_ellipse(params, xc, yc, px, py);
}

void ellipse_canon(const plot_params_t &params, long xc, long yc, long px, long py)
{
    long xfirst = 0, xlast = round(px * px / sqrt(px * px + py * py));

    for (long xi = xfirst; xi <= xlast; xi += 1)
    {
        long yi = round(py * sqrt(1 - (xi * xi) / (double) (px * px)));

        // 1 quad dec, 4 quad disp
        plot_mirror_points(params, xi, yi, xc, yc);
    }

    long yfirst = round(py * py / sqrt(px * px + py * py)) + 1, ylast = 0;

    for (long yi = yfirst; yi >= ylast; yi += -1)
    {
        long xi = round(px * sqrt(1 - (yi * yi) / (double) (py * py)));

        // 1 quad dec, 4 quad disp
        plot_mirror_points(params, xi, yi, xc, yc);
    }
}

void ellipse_param(const plot_params_t &params, long xc, long yc, long px, long py)
{
    double tfirst = 0, tlast = M_PI / 2;
    long maxp;
    if (py > px)
        maxp = py;
    else
        maxp = px;
    double step = 1.0 / maxp;

    size_t n = ceil((tlast - tfirst) / step);
    double t = tfirst;
    for (size_t i = 0; i <= n; i++, t += step)
    {
        long xi = round(px * cos(t));
        long yi = round(py * sin(t));
        // 1 quad dec, 4 quad disp
        plot_mirror_points(params, xi, yi, xc, yc);
    }
}

static void brez_hor_step(long &xi, long &yi, long &di, long px, long py)
{
    xi += 1;
    // yi = yi;
    di += (2 * xi + 1) * py * py;
}

static void brez_ver_step(long &xi, long &yi, long &di, long px, long py)
{
    // xi = xi;
    yi -= 1;
    di += (-2 * yi + 1) * px * px;
}

static void brez_diag_step(long &xi, long &yi, long &di, long px, long py)
{
    xi += 1;
    yi -= 1;
    di += (2 * xi + 1) * py * py + (-2 * yi + 1) * px * px;
}

void ellipse_brez(const plot_params_t &params, long xc, long yc, long px, long py)
{
    long xi = 0, yi = py;
    long di = py*py + px*px * (py - 1) * (py - 1) - px*px*py*py;
    long ye = 0;
    while (yi >= ye)
    {
        // 1 quad dec, 4 quad disp
        plot_mirror_points(params, xi, yi, xc, yc);

        ellipse_brez_step_func_t step_func = brez_diag_step;

        if (di < 0)
        {
            long d1 = 2 * di + (2 * yi - 1) * px * px;
            if (d1 <= 0)
                step_func = brez_hor_step;
        }
        else if (di > 0)
        {
            long d2 = 2 * di - (2 * xi + 1) * py * py;
            if (d2 > 0)
                step_func = brez_ver_step;
        }

        step_func(xi, yi, di, px, py);
    }
}

void ellipse_mid(const plot_params_t &params, long xc, long yc, long px, long py)
{
    long b2 = py * py;
    long b2s = 2 * b2;
    long a2 = px * px;
    long a2s = 2 * a2;

    long xi = 0, yi = py;
    long dx = 0; // 2 * py * py * x
    long dy = 2 * px * px * yi;
    long di = (int) (py * py - px * px * py + 0.25 * px * px);

    // vertical points
    while (dx < dy)
    {
        // 1 quad dec, 4 quad disp
        plot_mirror_points(params, xi, yi, xc, yc);

        if (di > 0)
        {
            yi--;
            dy -= a2s;
            di -= dy;
        }

        xi++;
        dx += b2s;
        di += dx + b2;
    }

    di += (int) (0.75 * (a2 - b2) - 0.5 * (b2s * xi + a2s * yi));
    while (yi >= 0)
    {
        // 1 quad dec, 4 quad disp
        plot_mirror_points(params, xi, yi, xc, yc);

        if (di < 0)
        {
            xi++;
            dx += b2s;
            di += dx;
        }

        yi--;
        dy -= a2s;
        di += (a2 - dy);
    }
}
