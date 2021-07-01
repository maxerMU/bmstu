#include <math.h>
#include "point.h"

point::point()
    :x(0), y(0), z(0)
{
}

point::point(double x, double y, double z)
    :x(x), y(y), z(z)
{
}

double point::get_x() const
{
    return x;
}

void point::set_x(double x)
{
    this->x = x;
}

double point::get_y() const
{
    return y;
}

void point::set_y(double y)
{
    this->y = y;
}

double point::get_z() const
{
    return z;
}

void point::set_z(double z)
{
    this->z = z;
}

void point::move(const point &move)
{
    x += move.x;
    y += move.y;
    z += move.z;
}

void point::scale(const point &center, const point &scale)
{
    x = x * scale.x + (1 - scale.x) * center.x;
    y = y * scale.y + (1 - scale.y) * center.y;
    z = z * scale.z + (1 - scale.z) * center.z;
}

void point::rotate_xy(double angle)
{
    double xy_angle = (angle * M_PI) / 180;

    double x_prev = x;
    double y_prev = y;

    x = x_prev * cos(xy_angle) - y_prev * sin(xy_angle);
    y = x_prev * sin(xy_angle) + y_prev * cos(xy_angle);
}

void point::rotate_xz(double angle)
{
    double xz_angle = (angle * M_PI) / 180;

    double x_prev = x;
    double z_prev = z;

    x = x_prev * cos(xz_angle) + z_prev * sin(xz_angle);
    z = -x_prev * sin(xz_angle) + z_prev * cos(xz_angle);
}

void point::rotate_yz(double angle)
{
    double yz_angle = (angle * M_PI) / 180;

    double y_prev = y;
    double z_prev = z;

    y = -z_prev * sin(yz_angle) + y_prev * cos(yz_angle);
    z = z_prev * cos(yz_angle) + y_prev * sin(yz_angle);
}

void point::rotate(const point &center, const point &rotate)
{
    x -= center.x;
    y -= center.y;
    z -= center.z;

    rotate_yz(rotate.x);
    rotate_xz(rotate.y);
    rotate_xy(rotate.z);

    x += center.x;
    y += center.y;
    z += center.z;
}
