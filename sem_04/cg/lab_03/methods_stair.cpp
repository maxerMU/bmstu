#include <stdio.h>
#include <math.h>
#include "methods_stair.h"

static int sign(int x)
{
    return x / abs(x);
}

size_t cda_stairs(int x1, int y1, int x2, int y2)
{
    size_t stairs = 0;
    if (x1 == x2 && y1 == y2)
    {
        // plot_point(params, x1, y1);
        return 0;
    }
    int length = abs(x2 - x1);
    if (abs(y2 - y1) > length)
        length = abs(y2 - y1);

    double x = x1, y = y1;
    double dx = (x2 - x1) / (double) length;
    double dy = (y2 - y1) / (double) length;
    double prev = y1;
    if (dx < dy)
        prev = x1;

    for (int i = 1; i <= length + 1; i++)
    {
        // plot_point(params, round(x), round(y));
        x += dx;
        y += dy;
        if (fabs(dx) < fabs(dy))
        {
            if (fabs(round(prev) - round(x)) > 0)
                stairs++;
        }
        else
        {
            if (fabs(round(prev) - round(y)) > 0)
                stairs++;
        }

        prev = y;
        if (fabs(dx) < fabs(dy))
            prev = x;
    }

    return stairs;
}

size_t brezenhem_real_stairs(int x1, int y1, int x2, int y2)
{
    size_t stairs = 0;
    if (x1 == x2 && y1 == y2)
    {
        // plot_point(params, x1, y1);
        return 0;
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
            stairs++;
        }
        if (swap)
            y = y + sy;
        else
            x = x + sx;
        e += m;
    }

    return stairs;
}


size_t brezenhem_int_stairs(int x1, int y1, int x2, int y2)
{
    size_t stairs = 0;
    if (x1 == x2 && y1 == y2)
    {
        // plot_point(params, x1, y1);
        return 0;
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
            stairs++;
        }
        if (swap)
            y = y + sy;
        else
            x = x + sx;
        e += 2 * dy;
    }

    return stairs;
}

size_t brezenhem_del_stair_stairs(int x1, int y1, int x2, int y2)
{
    size_t stairs = 0;
    if (x1 == x2 && y1 == y2)
    {
        // plot_point(params, x1, y1);
        return 0;
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
        //set_intence(params, round(f));
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

            stairs++;
        }
    }

    return stairs;
}

size_t wu_stairs(int x1, int y1, int x2, int y2)
{
    size_t stairs = 0;
    if (x1 == x2 && y1 == y2)
    {
        // plot_point(params, x1, y1);
        return 0;
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

    int ipart_prev = trunc(nb);
    for (int i = 1; i <= dx + 1; i++)
    {
        int ipart = trunc(nb);
        if (abs(ipart - ipart_prev) != 0)
            stairs++;
        ipart_prev = ipart;
        double fpart = fabs(nb - ipart);

        if (!swap)
        {
            // set_intence(params, I * (1 - fpart));
            // plot_point(params, b, ipart);
            // set_intence(params, I * fpart);
            // plot_point(params, b, ipart + sy);

            b += sx;
            nb += sy * m;
        }
        else
        {
            // set_intence(params, I * (1 - fpart));
            // plot_point(params, ipart, b);
            // set_intence(params, I * fpart);
            // plot_point(params, ipart + sx, b);

            b += sy;
            nb += sx * m;
        }

    }

    return stairs;
}

int stairs_table(const char *file_name, double angle_step, double r, stairs_func_t func)
{
    FILE *f = fopen(file_name, "w");
    if (!f)
        return STAIRS_OPEN_ER;

    fprintf(f, "%lf\n", r);
    fprintf(f, "%lf\n", angle_step);

    angle_step = (angle_step * M_PI) / 180.0;
    for (double iang = 0; iang < 2 * M_PI; iang += angle_step)
    {
        int xe = r * cos(iang);
        int ye = r * sin(iang);

        size_t stairs = func(0, 0, xe, ye);
        fprintf(f, "%zu\n", stairs);
    }

    fclose(f);

    return EXIT_SUCCESS;
}
