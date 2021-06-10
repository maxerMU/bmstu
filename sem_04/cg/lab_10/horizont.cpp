#include <math.h>

#include "horizont.h"

horizont::horizont(QObject *parent) : QObject(parent)
{
    funcs.push_back(f0);
    funcs.push_back(f1);
}

void horizont::set_func_index(int ind)
{
    func_index = ind;
}

void horizont::set_xmin(QString x)
{
    xmin = x.toDouble();
}

void horizont::set_xmax(QString x)
{
    xmax = x.toDouble();
}

void horizont::set_xstep(double step)
{
    xstep = step;
}

void horizont::set_zmax(QString z)
{
    zmax = z.toDouble();
}

void horizont::set_zmin(QString z)
{
    zmin = z.toDouble();
}

void horizont::set_zstep(double step)
{
    zstep = step;
}

void horizont::set_xangle(int angle)
{
    xangle = angle * M_PI / 180;
}

void horizont::set_yangle(int angle)
{
    yangle = angle * M_PI / 180;
}

void horizont::set_zangle(int angle)
{
    zangle = angle * M_PI / 180;
}

void horizont::find_limits(double &xmin_conv, double &xmax_conv, double &ymin, double &ymax) const
{
    double x_buf = xmin;
    double z_buf = zmax;
    ymin = funcs[func_index](xmin, zmax);

    rotate(x_buf, ymin, z_buf);
    ymax = ymin;

    xmin_conv = x_buf, xmax_conv = x_buf;

    for (double z = zmax; z > zmin || fabs(z - zmin) < EPS; z -= zstep)
    {
        for (double x = xmin; x < xmax || fabs(x - xmax) < EPS; x += xstep)
        {
            double y = funcs[func_index](x, z);
            z_buf = z;
            x_buf = x;
            rotate(x_buf, y, z_buf);
            if (y < ymin)
                ymin = y;
            else if (y > ymax)
                ymax = y;
            if (x_buf < xmin_conv)
                xmin_conv = x_buf;
            else if (x_buf > xmax_conv)
                xmax_conv = x_buf;
        }
    }
}

void horizont::find_scale_coefs(long &xc, long &yc, long &k, const canvas &field) const
{
    double ymin, ymax, xmin_conv, xmax_conv;
    find_limits(xmin_conv, xmax_conv, ymin, ymax);

    long ky = (field.height() * (1 - OFFSET * 2)) / (ymax - ymin);
    long kx = (field.width() * (1 - OFFSET * 2)) / (xmax_conv - xmin_conv);

    //yc = field.height() * OFFSET + ymax * ky;
    yc = field.height() / 2;
    xc = field.width() * OFFSET - xmin_conv * kx;

    if (ky < kx)
        k = ky;
    else
        k = kx;
}

void horizont::convert_coords(double &x, double &y, long xc, long yc, long k) const
{
    x = xc + x * k;
    y = yc - y * k;
}

void horizont::edge_handling(long &xprev, long &yprev, std::vector<long> &top,
                             std::vector<long> &bottom, long x, long y) const
{
    if (xprev == -1)
    {
        xprev = x;
        yprev = y;
    }
    else
        hor(top, bottom, xprev, yprev, x, y);
}

void horizont::is_visible(long &flag, long x, long y, const std::vector<long> &top,
                          const std::vector<long> &bottom) const
{
    flag = 0;

    if (y >= top[x])
        flag = 1;
    if (y <= bottom[x])
        flag = -1;
}

template <typename T>
static T min(const T &x, const T &y)
{
    if (x < y)
        return x;

    return y;
}

template <typename T>
static T max(const T &x, const T &y)
{
    if (x > y)
        return x;

    return y;
}

void horizont::hor(std::vector<long> &top, std::vector<long> &bottom, long x1, long y1, long x2, long y2) const
{
    if (x2 == x1)
    {
        top[x2] = max<long>(top[x2], y2);
        bottom[x2] = min<long>(bottom[x2], y2);
    }
    else
    {
        double m = (y2 - y1) / (double) (x2 - x1);
        for (long x = x1; x <= x2; x++)
        {
            long y = m * (x - x1) + y1;
            top[x] = max<long>(top[x], y);
            bottom[x] = min<long>(bottom[x], y);
        }
    }
}

static long sign(double x)
{
    if (fabs(x) < EPS)
        return 0;
    if (x < 0)
        return -1;

    return 1;
}

void horizont::find_inter(long &xi, long &yi, long x1, long y1,
                          long x2, long y2, const std::vector<long> &hor) const
{
    if (x2 == x1)
    {
        xi = x2;
        yi = hor[x2];
    }
    else
    {
        double m = (y2 - y1) / (double) (x2 - x1);
        long ysign = sign(y1 + m - hor[x1 + 1]);
        long csign = ysign;
        long x = x1 + 1, y = y1 + m;
        while (csign == ysign && x <= x2 + 1)
        {
            x++;
            y += m;
            ysign = sign(y - hor[x]);
        }
        if (fabs(y - m - hor[x - 1]) < fabs(y - hor[x]))
        {
            y -= m;
            x--;
        }
        if (x < x1 || x > x2)
        {
            xi = -1;
            yi = -1;
        }
        else
        {
            yi = y;
            xi = x;
        }
    }
}

void horizont::rotate_x(double &y, double &z) const
{
    double buf = y;
    y = cos(xangle) * y - sin(xangle) * z;
    z = cos(xangle) * z + sin(xangle) * buf;
}


void horizont::rotate_y(double &x, double &z) const
{
    double buf = x;
    x = cos(yangle) * x - sin(yangle) * z;
    z = cos(yangle) * z + sin(yangle) * buf;
}


void horizont::rotate_z(double &x, double &y) const
{
    double buf = x;
    x = cos(zangle) * x - sin(zangle) * y;
    y = cos(zangle) * y + sin(zangle) * buf;
}

void horizont::rotate(double &x, double &y, double &z) const
{
    rotate_x(y, z);
    rotate_y(x, z);
    rotate_z(x, y);
}

void horizont::find_horizonts(canvas &field) const
{
    long xc, yc, k;
    find_scale_coefs(xc, yc, k, field);

    std::vector<long> top, bottom;
    for (long x = 1; x <= field.width(); x++)
    {
        top.push_back(0);
        bottom.push_back(field.height());
    }

    long xl = -1, yl = -1, xr = -1, yr = -1;
    for (double z = zmax; z > zmin || fabs(z - zmin) < EPS; z -= zstep)
    {
        double x = xmin, y = funcs[func_index](x, z);
        double z_buf = z;
        rotate(x, y, z_buf);
        convert_coords(x, y, xc, yc, k);
        long xprev = x, yprev = y;

        edge_handling(xl, yl, top, bottom, xprev, yprev);
        long prevflag;
        is_visible(prevflag, xprev, yprev, top, bottom);

        for (double x = xmin; x < xmax || fabs(x - xmax) < EPS; x += xstep)
        {
            double x_doub = x;
            double y_doub = funcs[func_index](x, z);
            double z_buf = z;
            rotate(x_doub, y_doub, z_buf);
            convert_coords(x_doub, y_doub, xc, yc, k);

            long x_conv = x_doub, y_conv = y_doub;
            long cur_flag;
            is_visible(cur_flag, x_conv, y_conv, top, bottom);

            if (cur_flag == prevflag)
            {
                if (cur_flag == 1 || cur_flag == -1)
                {
                    field.draw_line(xprev, yprev, x_conv, y_conv, DRAW_COLOR);
                    hor(top, bottom, xprev, yprev, x_conv, y_conv);
                }
            }
            else if (cur_flag == 0)
            {
                long xi, yi;
                if (prevflag == 1)
                    find_inter(xi, yi, xprev, yprev, x_conv, y_conv, top);
                else
                    find_inter(xi, yi, xprev, yprev, x_conv, y_conv, bottom);
                if (xi != -1)
                {
                    field.draw_line(xprev, yprev, xi, yi, DRAW_COLOR);
                    hor(top, bottom, xprev, yprev, xi, yi);
                }
            }
            else if (cur_flag == 1)
            {
                long xi, yi;
                if (prevflag == 0)
                {
                    find_inter(xi, yi, xprev, yprev, x_conv, y_conv, top);
                    if (xi != -1)
                    {
                        field.draw_line(xi, yi, x_conv, y_conv, DRAW_COLOR);
                        hor(top, bottom, xi, yi, x_conv, y_conv);
                    }
                }
                else //prev_flag == -1
                {
                    find_inter(xi, yi, xprev, yprev, x_conv, y_conv, bottom);
                    if (xi != -1)
                    {
                        field.draw_line(xprev, yprev, xi, yi, DRAW_COLOR);
                        hor(top, bottom, xprev, yprev, xi, yi);
                    }
                    find_inter(xi, yi, xprev, yprev, x_conv, y_conv, top);
                    if (xi != -1)
                    {
                        field.draw_line(xi, yi, x_conv, y_conv, DRAW_COLOR);
                        hor(top, bottom, xi, yi, x_conv, y_conv);
                    }
                }
            }
            else //cur_flag == -1
            {
                long xi, yi;
                if (prevflag == 0)
                {
                    find_inter(xi, yi, xprev, yprev, x_conv, y_conv, bottom);
                    if (xi != -1)
                    {
                        field.draw_line(xi, yi, x_conv, y_conv, DRAW_COLOR);
                        hor(top, bottom, xi, yi, x_conv, y_conv);
                    }
                }
                else
                {
                    find_inter(xi, yi, xprev, yprev, x_conv, y_conv, top);
                    if (xi != -1)
                    {
                        field.draw_line(xprev, yprev, xi, yi, DRAW_COLOR);
                        hor(top, bottom, xprev, yprev, xi, yi);
                    }
                    find_inter(xi, yi, xprev, yprev, x_conv, y_conv, bottom);
                    if (xi != -1)
                    {
                        field.draw_line(xi, yi, x_conv, y_conv, DRAW_COLOR);
                        hor(top, bottom, xi, yi, x_conv, y_conv);
                    }
                }
            }

            prevflag = cur_flag;
            xprev = x_conv;
            yprev = y_conv;
        }

        edge_handling(xr, yr, top, bottom, xprev, yprev);
    }
}
