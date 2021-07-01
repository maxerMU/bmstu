#include <stdio.h>
#include <math.h>
#include <QColor>
#include <time.h>
#include "cir_methods_time.h"
#include "plot_funcs.h"

typedef void (*time_draw_circle_func_t)(const plot_params_t &, long, long, long);
typedef void (*circle_brez_step_func_t)(long &, long &, long &);

void circle_canon_time(const plot_params_t &params, long x, long y, long r)
{
    long xi = 0;
    long yi = r;
    while (xi <= yi)
    {
        // 2 oct dec 7 oct disp
        //plot_point(params, xi + x, yi + y);
        //plot_point(params, x - xi, yi + y);
        //plot_point(params, xi + x, y - yi);
        //plot_point(params, x - xi, y - yi);
        //plot_point(params, x + yi, y + xi);
        //plot_point(params, x - yi, y + xi);
        //plot_point(params, x + yi, y - xi);
        //plot_point(params, x - yi, y - xi);
        xi++;
        yi = round(sqrt(r * r - xi * xi));
    }
}

void circle_param_time(const plot_params_t &params, long x, long y, long r)
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
        //plot_point(params, xi + x, yi + y);
        //plot_point(params, x - xi, yi + y);
        //plot_point(params, xi + x, y - yi);
        //plot_point(params, x - xi, y - yi);
        //plot_point(params, x + yi, y + xi);
        //plot_point(params, x - yi, y + xi);
        //plot_point(params, x + yi, y - xi);
        //plot_point(params, x - yi, y - xi);
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

void circle_brez_time(const plot_params_t &params, long x, long y, long r)
{
    long xi = 0, yi = r, di = 2 * (1 - r);
    long ye = r / sqrt(2);
    while (yi >= ye)
    {
        // 2 oct dec 7 oct disp
        //plot_point(params, xi + x, yi + y);
        //plot_point(params, x - xi, yi + y);
        //plot_point(params, xi + x, y - yi);
        //plot_point(params, x - xi, y - yi);
        //plot_point(params, x + yi, y + xi);
        //plot_point(params, x - yi, y + xi);
        //plot_point(params, x + yi, y - xi);
        //plot_point(params, x - yi, y - xi);

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

void circle_mid_time(const plot_params_t &params, long x, long y, long r)
{
    long xi = 0, yi = r;
    long di = 6 - 4 * r;

    // vertical points
    while (xi <= yi)
    {
        // 2 oct dec 7 oct disp
        //plot_point(params, xi + x, yi + y);
        //plot_point(params, x - xi, yi + y);
        //plot_point(params, xi + x, y - yi);
        //plot_point(params, x - xi, y - yi);
        //plot_point(params, x + yi, y + xi);
        //plot_point(params, x - yi, y + xi);
        //plot_point(params, x + yi, y - xi);
        //plot_point(params, x - yi, y - xi);

        if (di > 0)
        {
            di += 8 * (xi - yi + 1);
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

static double get_time(long r, time_draw_circle_func_t func)
{
    plot_params_t params(NULL, QColor(0, 0, 0), QColor(255, 255, 255));

    clock_t circle_clc = clock();
    for (size_t i = 0; i < CIRCLE_TIME_ITERATIONS; i++)
    {
        func(params, 0, 0, r);
    }
    circle_clc = clock() - circle_clc;
    double circle_time = ((double)circle_clc / CLOCKS_PER_SEC);// / CIRCLE_TIME_ITERATIONS;

    return circle_time;
}

int circle_time_table(const char *file_name, long rmin, long rmax, long step)
{
    FILE *f = fopen(file_name, "w");
    if (!f)
        return OPEN_ER;

    fprintf(f, "%ld\n%ld\n%ld\n", rmin, rmax, step);

    for (long r = rmin; r < rmax; r += step)
    {
        double t = get_time(r, circle_canon_time);
        fprintf(f, "%lf\n", t);
    }

    for (long r = rmin; r < rmax; r += step)
    {
        double t = get_time(r, circle_param_time);
        fprintf(f, "%lf\n", t);
    }

    for (long r = rmin; r < rmax; r += step)
    {
        double t = get_time(r, circle_brez_time);
        fprintf(f, "%lf\n", t);
    }

    for (long r = rmin; r < rmax; r += step)
    {
        double t = get_time(r, circle_mid_time);
        fprintf(f, "%lf\n", t);
    }

    fclose(f);

    return EXIT_SUCCESS;
}
