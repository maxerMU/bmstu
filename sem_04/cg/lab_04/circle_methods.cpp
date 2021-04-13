#include <math.h>

#include "circle_methods.h"

#define EPS 1e-6

typedef void (*circle_brez_step_func_t)(long &, long &, long &);

void circle_lib(const plot_params_t &params, long x, long y, long r)
{
    plot_circle(params, x, y, r);
}

void circle_canon(const plot_params_t &params, long x, long y, long r)
{
    long xi = 0;
    long yi = r;
    while (xi <= yi)
    {
        // 2 oct dec 7 oct disp
        plot_mirror_points(params, xi, yi, x, y);
        plot_mirror_points(params, yi, xi, x, y);
        xi++;
        yi = round(sqrt(r * r - xi * xi));
    }
}

void circle_param(const plot_params_t &params, long x, long y, long r)
{
    double tfirst = M_PI / 4, tlast = M_PI / 2;
    double step = 1.0 / r;
    size_t n = ceil((tlast - tfirst) / step);
    double t = tfirst;
    for (size_t i = 0; i <= n; i++, t += step)
    {
        long xi = round(r * cos(t));
        long yi = round(r * sin(t));
        // 2 oct dec 7 oct disp
        plot_mirror_points(params, xi, yi, x, y);
        plot_mirror_points(params, yi, xi, x, y);
    }
}

static void brez_hor_step(long &xi, long &yi, long &di)
{
    xi += 1;
    // yi = yi;
    di += 2 * xi + 1;
}

static void brez_ver_step(long &xi, long &yi, long &di)
{
    // xi = xi;
    yi -= 1;
    di += -2 * yi + 1;
}

static void brez_diag_step(long &xi, long &yi, long &di)
{
    xi += 1;
    yi -= 1;
    di += 2 * xi - 2 * yi + 2;
}

void circle_brez(const plot_params_t &params, long x, long y, long r)
{
    long xi = 0, yi = r, di = 2 * (1 - r);
    long ye = r / sqrt(2);
    while (yi >= ye)
    {
        // 2 oct dec 7 oct disp
        plot_mirror_points(params, xi, yi, x, y);
        plot_mirror_points(params, yi, xi, x, y);

        circle_brez_step_func_t step_func = brez_diag_step;

        if (di < 0)
        {
            long d1 = 2 * di + 2 * yi - 1;
            if (d1 < 0)
                step_func = brez_hor_step;
        }
        else if (di > 0)
        {
            long d2 = 2 * di - 2 * xi - 1;
            if (d2 > 0)
                step_func = brez_ver_step;
        }

        step_func(xi, yi, di);
    }
}

void circle_mid(const plot_params_t &params, long x, long y, long r)
{
    long xi = 0, yi = r;
    long di = 5 - 4 * r;

    // vertical points
    while (xi <= yi)
    {
        // 2 oct dec 7 oct disp
        plot_mirror_points(params, xi, yi, x, y);
        plot_mirror_points(params, yi, xi, x, y);

        if (di > 0)
        {
            di += 8 * (xi - yi) + 12;
            xi++;
            yi--;
        }
        else
        {
            di += 8 * xi + 4;
            xi++;
        }

    }
}
