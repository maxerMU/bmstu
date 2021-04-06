#include <stdio.h>
#include <math.h>
#include <QColor>
#include "methods_time.h"
#include "plot_funcs.h"

typedef void (*time_draw_func_t)(plot_params_t &, int, int, int, int);

static int sign(int x)
{
    return x / abs(x);
}

void cda_time(plot_params_t &params, int x1, int y1, int x2, int y2)
{
    if (x1 == x2 && y1 == y2)
    {
        // plot_point(params, x1, y1);
        return;
    }
    int length = abs(x2 - x1);
    if (abs(y2 - y1) > length)
        length = abs(y2 - y1);

    double x = x1, y = y1;
    double dx = (x2 - x1) / (double) length;
    double dy = (y2 - y1) / (double) length;

    for (int i = 1; i <= length + 1; i++)
    {
        // plot_point(params, round(x), round(y));
        x += dx;
        y += dy;
    }
}

void brezenhem_real_time(plot_params_t &params, int x1, int y1, int x2, int y2)
{
    if (x1 == x2 && y1 == y2)
    {
        // plot_point(params, x1, y1);
        return;
    }
    int dx = x2 - x1, dy = y2 - y1;

    int sx = sign(dx), sy = sign(dy);

    dx = abs(dx);
    dy = abs(dy);

    bool swap = false;
    if (dy >= dx)
    {
        int temp = dx;
        dx = dy;
        dy = temp;
        swap = true;
    }

    double m = (double) dy / (double) dx;

    double e = m - 0.5;
    int x = x1, y = y1;

    for (int i = 1; i <= dx + 1; i++)
    {
        // plot_point(params, x, y);

        if (e > 0)
        {
            if (swap)
                x = x + sx;
            else
                y = y + sy;
            e -= 1;
        }
        if (swap)
            y = y + sy;
        else
            x = x + sx;
        e += m;
    }
}


void brezenhem_int_time(plot_params_t &params, int x1, int y1, int x2, int y2)
{
    if (x1 == x2 && y1 == y2)
    {
        // plot_point(params, x1, y1);
        return;
    }

    int dx = x2 - x1, dy = y2 - y1;

    int sx = sign(dx), sy = sign(dy);

    dx = abs(dx);
    dy = abs(dy);

    bool swap = false;
    if (dy > dx)
    {
        int temp = dx;
        dx = dy;
        dy = temp;
        swap = true;
    }

    int e = 2 * dx - dx;
    int x = x1, y = y1;

    for (int i = 1; i <= dx + 1; i++)
    {
        // plot_point(params, x, y);

        if (e > 0)
        {
            if (swap)
                x = x + sx;
            else
                y = y + sy;
            e -= 2 * dx;
        }
        if (swap)
            y = y + sy;
        else
            x = x + sx;
        e += 2 * dy;
    }
}

void brezenhem_del_stair_time(plot_params_t &params, int x1, int y1, int x2, int y2)
{
    if (x1 == x2 && y1 == y2)
    {
        // plot_point(params, x1, y1);
        return;
    }

    int dx = x2 - x1, dy = y2 - y1;
    int I = 255;

    int sx = sign(dx), sy = sign(dy);

    dx = abs(dx);
    dy = abs(dy);

    bool swap = false;
    if (dy >= dx)
    {
        int temp = dx;
        dx = dy;
        dy = temp;
        swap = true;
    }

    double m = (double) dy / (double) dx * I;

    double f = I / 2.0;
    double w = I - m;
    int x = x1, y = y1;

    for (int i = 1; i <= dx + 1; i++)
    {
        set_intence(params, round(f));
        // plot_point(params, x, y);

        if (f < w)
        {
            if (swap)
                y = y + sy;
            else
                x = x + sx;
            f += m;
        }
        else
        {
            y = y + sy;
            x = x + sx;
            f -= w;
        }
    }
}

void wu_time(plot_params_t &params, int x1, int y1, int x2, int y2)
{
    if (x1 == x2 && y1 == y2)
    {
        // plot_point(params, x1, y1);
        return;
    }

    int dx = x2 - x1, dy = y2 - y1;
    int I = 255;

    int sx = sign(dx), sy = sign(dy);

    dx = abs(dx);
    dy = abs(dy);

    bool swap = false;
    if (dy >= dx)
    {
        int temp = dx;
        dx = dy;
        dy = temp;
        swap = true;
    }

    double m = (double) dy / (double) dx;

    double nb;
    int b;

    if (swap)
    {
        nb = y1;
        b = x1;
    }
    else
    {
        nb = x1;
        b = y1;
    }

    for (int i = 1; i <= dx + 1; i++)
    {
        int ipart = trunc(nb);
        double fpart = fabs(nb - ipart);

        if (!swap)
        {
            set_intence(params, I * (1 - fpart));
            // plot_point(params, b, ipart);
            set_intence(params, I * fpart);
            // plot_point(params, b, ipart + sy);

            b += sx;
            nb += sy * m;
        }
        else
        {
            set_intence(params, I * (1 - fpart));
            // plot_point(params, ipart, b);
            set_intence(params, I * fpart);
            // plot_point(params, ipart + sx, b);

            b += sy;
            nb += sx * m;
        }
    }
}

double get_avg_angle(double angle, double r, time_draw_func_t func)
{
    angle = (angle * M_PI) / 180.0;
    size_t k = 0;
    plot_params_t params(NULL, QColor(0, 0, 0), QColor(255, 255, 255));


    double t = 0;

    for (double iang = 0; iang < 2 * M_PI; iang += angle)
    {
        int xe = r * cos(iang);
        int ye = r * sin(iang);

        clock_t cur_ang_clc = clock();
        for (size_t i = 0; i < TIME_ITERATIONS; i++)
        {
            func(params, 0, 0, xe, ye);
        }
        cur_ang_clc = clock() - cur_ang_clc;
        double cur_ang_time = ((double)cur_ang_clc / CLOCKS_PER_SEC) / TIME_ITERATIONS;

        t += cur_ang_time;

        k++;
    }

    return t / k;
}

int time_table(const char *file_name, double angle, double r)
{
    FILE *f = fopen(file_name, "w");
    if (!f)
        return OPEN_ER;

    fprintf(f, "%lf\n", r);

    double t = get_avg_angle(angle, r, cda_time);
    fprintf(f, "%lf\n", t);

    t = get_avg_angle(angle, r, brezenhem_real_time);
    fprintf(f, "%lf\n", t);

    t = get_avg_angle(angle, r, brezenhem_int_time);
    fprintf(f, "%lf\n", t);

    t = get_avg_angle(angle, r, brezenhem_del_stair_time);
    fprintf(f, "%lf\n", t);

    t = get_avg_angle(angle, r, wu_time);
    fprintf(f, "%lf\n", t);

    fclose(f);

    return EXIT_SUCCESS;
}
