#include <stdio.h>
#include <math.h>
#include "point.h"

int read_point(FILE *src, point_t &point)
{
    int rc = POINT_SUCCESS;
    if (fscanf(src, "%lf", &(point.x)) != 1)
        rc = POINT_READ_ER;
    else if (fscanf(src, "%lf", &(point.y)) != 1)
        rc = POINT_READ_ER;
    else if (fscanf(src, "%lf", &(point.z)) != 1)
        rc = POINT_READ_ER;

    return rc;
}

void write_point(FILE *dst, const point_t &point)
{
    fprintf(dst, "%lf %lf %lf", point.x, point.y, point.z);
}

void move_point(const double dx, const double dy, const double dz, point_t &point)
{
    point.x += dx;
    point.y += dy;
    point.z += dz;
}

void scale_point(point_t c, double kx, double ky, double kz, point_t &point)
{
    point.x = point.x * kx + (1 - kx) * c.x;
    point.y = point.y * ky + (1 - ky) * c.y;
    point.z = point.z * kz + (1 - kz) * c.z;
}

void rotate_point(point_t c, double xy_ang, double xz_ang, double yz_ang, point_t &point)
{
    xy_ang = (xy_ang * M_PI) / 180;

    double x = point.x;
    double y = point.y;

    point.x = c.x + (x - c.x) * cos(xy_ang) - (y - c.y) * sin(xy_ang);
    point.y = c.y + (x - c.x) * sin(xy_ang) + (y - c.y) * cos(xy_ang);

    xz_ang = (xz_ang * M_PI) / 180;

    x = point.x;
    double z = point.z;

    point.x = c.x + (x - c.x) * cos(xz_ang) + (z - c.z) * sin(xz_ang);
    point.z = c.z - (x - c.x) * sin(xz_ang) + (z - c.z) * cos(xz_ang);

    yz_ang = (yz_ang * M_PI) / 180;

    y = point.y;
    z = point.z;

    point.y = c.y - (z - c.z) * sin(yz_ang) + (y - c.y) * cos(yz_ang);
    point.z = c.z + (z - c.z) * cos(yz_ang) + (y - c.y) * sin(yz_ang);
}

void to_display_point(display_point_t &disp_point, const point_t &point)
{
    disp_point.x = point.y - point.x / sqrt(2);
    disp_point.y = point.x / sqrt(2) - point.z;
}
