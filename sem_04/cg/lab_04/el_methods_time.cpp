#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <QColor>
#include <time.h>
#include "el_methods_time.h"
#include "plot_funcs.h"

typedef void (*time_draw_ellipse_func_t)(long, long, long, long);
typedef void (*ellipse_brez_step_func_t)(long &, long &, long &, long, long);

void ellipse_canon_time(long xc, long yc, long px, long py)
{
    long xfirst = 0, xlast = round(px * px / sqrt(px * px + py * py));

    for (long xi = xfirst; xi <= xlast; xi += 1)
    {
        long yi = round(py * sqrt(1 - (xi * xi) / (double) (px * px)));

        // 1 quad dec, 4 quad disp
        //plot_point(params, xi + xc, yi + yc);
        //plot_point(params, xc - xi, yi + yc);
        //plot_point(params, xi + xc, yc - yi);
        //plot_point(params, xc - xi, yc - yi);
    }

    long yfirst = round(py * py / sqrt(px * px + py * py)) + 1, ylast = 0;

    for (long yi = yfirst; yi >= ylast; yi += -1)
    {
        long xi = round(px * sqrt(1 - (yi * yi) / (double) (py * py)));

        // 1 quad dec, 4 quad disp
        //plot_point(params, xi + xc, yi + yc);
        //plot_point(params, xc - xi, yi + yc);
        //plot_point(params, xi + xc, yc - yi);
        //plot_point(params, xc - xi, yc - yi);
    }
}

void ellipse_param_time(long xc, long yc, long px, long py)
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
        //plot_point(params, xi + xc, yi + yc);
        //plot_point(params, xc - xi, yi + yc);
        //plot_point(params, xi + xc, yc - yi);
        //plot_point(params, xc - xi, yc - yi);
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

void ellipse_brez_time(long xc, long yc, long px, long py)
{
    long xi = 0, yi = py;
    long di = py*py + px*px * (py - 1) * (py - 1) - px*px*py*py;
    long ye = 0;
    while (yi >= ye)
    {
        // 1 quad dec, 4 quad disp
        //plot_point(params, xi + xc, yi + yc);
        //plot_point(params, xc - xi, yi + yc);
        //plot_point(params, xi + xc, yc - yi);
        //plot_point(params, xc - xi, yc - yi);

        ellipse_brez_step_func_t step_func = brez_diag_step;

        if (di < 0)
        {
            long d1 = 2 * di + (2 * yi - 1) * px * px;
            if (d1 < 0)
                step_func = brez_hor_step;
        }
        else if (di > 0)
        {
            long d2 = 2 * di + (2 * xi + 1) * py * py;
            if (d2 > 0)
                step_func = brez_ver_step;
        }

        step_func(xi, yi, di, px, py);
    }
}

void ellipse_mid_time(long xc, long yc, long px, long py)
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
        //plot_point(params, xi + xc, yi + yc);
        //plot_point(params, xc - xi, yi + yc);
        //plot_point(params, xi + xc, yc - yi);
        //plot_point(params, xc - xi, yc - yi);


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
        //plot_point(params, xi + xc, yi + yc);
        //plot_point(params, xc - xi, yi + yc);
        //plot_point(params, xi + xc, yc - yi);
        //plot_point(params, xc - xi, yc - yi);

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

static double get_time(long rx, long ry, time_draw_ellipse_func_t func)
{
    clock_t el_clc = clock();
    for (size_t i = 0; i < EL_TIME_ITERATIONS; i++)
    {
        func(0, 0, rx, ry);
    }
    el_clc = clock() - el_clc;
    double el_time = ((double)el_clc / CLOCKS_PER_SEC) / EL_TIME_ITERATIONS;

    return el_time;
}

int ellipse_time_table(const char *file_name, long rx, long ry, long step, long n)
{
    FILE *f = fopen(file_name, "w");
    if (!f)
        return EXIT_FAILURE;

    fprintf(f, "%ld\n", rx);
    fprintf(f, "%ld\n", ry);
    fprintf(f, "%ld\n", step);
    fprintf(f, "%ld\n", n);

    bool flag = (ry > rx);

    double e_sqr;
    if (flag)
        e_sqr = 1 - (rx * rx) / double (ry * ry);
    else
        e_sqr = 1 - (ry * ry) / double (rx * rx);

    for (long i = 0, px = rx, py = ry; i < n; i++)
    {
        double t = get_time(px, py, ellipse_canon_time);
        fprintf(f, "%lf\n", t);

        px += step;
        if (flag)
            py = round(sqrt(px * px / (1 - e_sqr)));
        else
            py = round(sqrt(px * px * (1 - e_sqr)));
    }

    for (long i = 0, px = rx, py = ry; i < n; i++)
    {
        double t = get_time(px, py, ellipse_param_time);
        fprintf(f, "%lf\n", t);

        px += step;
        if (flag)
            py = round(sqrt(px * px / (1 - e_sqr)));
        else
            py = round(sqrt(px * px * (1 - e_sqr)));
    }

    for (long i = 0, px = rx, py = ry; i < n; i++)
    {
        double t = get_time(px, py, ellipse_brez_time);
        fprintf(f, "%lf\n", t);

        px += step;
        if (flag)
            py = round(sqrt(px * px / (1 - e_sqr)));
        else
            py = round(sqrt(px * px * (1 - e_sqr)));
    }

    for (long i = 0, px = rx, py = ry; i < n; i++)
    {
        double t = get_time(px, py, ellipse_mid_time);
        fprintf(f, "%lf\n", t);

        px += step;
        if (flag)
            py = round(sqrt(px * px / (1 - e_sqr)));
        else
            py = round(sqrt(px * px * (1 - e_sqr)));
    }

    fclose(f);

    return EXIT_SUCCESS;
}
