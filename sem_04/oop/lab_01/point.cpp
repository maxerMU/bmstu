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

int rotate_xy(point_t &point, const double angle)
{
    double xy_angle = (angle * M_PI) / 180;

    double x = point.x;
    double y = point.y;

    point.x = x * cos(xy_angle) - y * sin(xy_angle);
    point.y = x * sin(xy_angle) + y * cos(xy_angle);

    return SUCCESS;
}

int rotate_xz(point_t &point, const double angle)
{
    double xz_angle = (angle * M_PI) / 180;

    double x = point.x;
    double z = point.z;

    point.x = x * cos(xz_angle) + z * sin(xz_angle);
    point.z = x * sin(xz_angle) + z * cos(xz_angle);

    return SUCCESS;
}

int rotate_yz(point_t &point, const double angle)
{
    double yz_angle = (angle * M_PI) / 180;

    double y = point.y;
    double z = point.z;

    point.y = z * sin(yz_angle) + y * cos(yz_angle);
    point.z = z * cos(yz_angle) + y * sin(yz_angle);

    return SUCCESS;
}

int rotate_point(point_t &point, const rotate_t &rotate, const point_t &c)
{
    point.x -= c.x;
    point.y -= c.y;
    point.z -= c.z;
    int rc = rotate_xy(point, rotate.xy_angle);
    if (rc)
        return rc;

    rc = rotate_xz(point, rotate.xz_angle);
    if (rc)
        return rc;

    rc = rotate_yz(point, rotate.yz_angle);
    if (rc)
        return rc;

    point.x += c.x;
    point.y += c.y;
    point.z += c.z;

    return SUCCESS;
}
