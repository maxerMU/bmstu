#include <stdio.h>
#include <math.h>
#include "point.h"
#include "convert.h"
#include "errors.h"

int read_point(point_t &point, FILE *src)
{
    int rc = SUCCESS;
    if (fscanf(src, "%lf", &(point.x)) != 1)
        rc = POINT_READ_ER;
    else if (fscanf(src, "%lf", &(point.y)) != 1)
        rc = POINT_READ_ER;
    else if (fscanf(src, "%lf", &(point.z)) != 1)
        rc = POINT_READ_ER;

    return rc;
}

int write_point(FILE *dst, const point_t &point)
{
    fprintf(dst, "%lf %lf %lf", point.x, point.y, point.z);

    return SUCCESS;
}

int move_point(point_t &point, const move_t &move)
{
    point.x += move.dx;
    point.y += move.dy;
    point.z += move.dz;

    return SUCCESS;
}

int scale_point(point_t &point, const scale_t &scale, const point_t &c)
{
    point.x = point.x * scale.kx + (1 - scale.kx) * c.x;
    point.y = point.y * scale.ky + (1 - scale.ky) * c.y;
    point.z = point.z * scale.kz + (1 - scale.kz) * c.z;

    return SUCCESS;
}

int rotate_xy(point_t &point, const double angle, const point_t &c)
{
    double xy_angle = (angle * M_PI) / 180;

    double x = point.x;
    double y = point.y;

    point.x = c.x + (x - c.x) * cos(xy_angle) - (y - c.y) * sin(xy_angle);
    point.y = c.y + (x - c.x) * sin(xy_angle) + (y - c.y) * cos(xy_angle);

    return SUCCESS;
}

int rotate_xz(point_t &point, const double angle, const point_t &c)
{
    double xz_angle = (angle * M_PI) / 180;

    double x = point.x;
    double z = point.z;

    point.x = c.x + (x - c.x) * cos(xz_angle) + (z - c.z) * sin(xz_angle);
    point.z = c.z - (x - c.x) * sin(xz_angle) + (z - c.z) * cos(xz_angle);

    return SUCCESS;
}

int rotate_yz(point_t &point, const double angle, const point_t &c)
{
    double yz_angle = (angle * M_PI) / 180;

    double y = point.y;
    double z = point.z;

    point.y = c.y - (z - c.z) * sin(yz_angle) + (y - c.y) * cos(yz_angle);
    point.z = c.z + (z - c.z) * cos(yz_angle) + (y - c.y) * sin(yz_angle);

    return SUCCESS;
}

int rotate_point(point_t &point, const rotate_t &rotate, const point_t &c)
{
    int rc = rotate_xy(point, rotate.xy_angle, c);
    if (rc)
        return rc;

    rc = rotate_xz(point, rotate.xz_angle, c);
    if (rc)
        return rc;

    rc = rotate_yz(point, rotate.yz_angle, c);
    if (rc)
        return rc;

    return SUCCESS;
}
