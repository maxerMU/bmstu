#include <math.h>
#include "methods.h"

int sign(int x)
{
    return x / abs(x);
}

void lib(plot_params_t &params, int x1, int y1, int x2, int y2)
{
    plot_line(params, x1, y1, x2, y2);
}

void cda(plot_params_t &params, int x1, int y1, int x2, int y2)
{
    if (x1 == x2 && y1 == y2)
    {
        plot_point(params, x1, y1);
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
        plot_point(params, round(x), round(y));
        x += dx;
        y += dy;
    }
}

void brezenhem_real(plot_params_t &params, int x1, int y1, int x2, int y2)
{
    if (x1 == x2 && y1 == y2)
    {
        plot_point(params, x1, y1);
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

    for (int i = 0; i < dx; i++)
    {
        plot_point(params, x, y);

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


void brezenhem_int(plot_params_t &params, int x1, int y1, int x2, int y2)
{
    if (x1 == x2 && y1 == y2)
    {
        plot_point(params, x1, y1);
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

    int e = 2 * dy - dx;
    int x = x1, y = y1;

    for (int i = 0; i < dx; i++)
    {
        plot_point(params, x, y);

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

void brezenhem_del_stair(plot_params_t &params, int x1, int y1, int x2, int y2)
{
    if (x1 == x2 && y1 == y2)
    {
        plot_point(params, x1, y1);
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
        plot_point(params, x, y);

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

void wu(plot_params_t &params, int x1, int y1, int x2, int y2)
{
    if (x1 == x2 && y1 == y2)
    {
        plot_point(params, x1, y1);
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
            plot_point(params, b, ipart);
            set_intence(params, I * fpart);
            plot_point(params, b, ipart + sy);

            b += sx;
            nb += sy * m;
        }
        else
        {
            set_intence(params, I * (1 - fpart));
            plot_point(params, ipart, b);
            set_intence(params, I * fpart);
            plot_point(params, ipart + sx, b);

            b += sy;
            nb += sx * m;
        }
    }
}
