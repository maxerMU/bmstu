#include <stdio.h>
#include <math.h>
#include "point.h"
#include "convert.h"
#include "errors.h"

int read_point(FILE *src, point_t &point)
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

void write_point(FILE *dst, const point_t &point)
{
    fprintf(dst, "%lf %lf %lf", point.x, point.y, point.z);
}

void move_point(const move_t &move, point_t &point)
{
    point.x += move.dx;
    point.y += move.dy;
    point.z += move.dz;
}

void scale_point(const scale_t &scale, point_t &point)
{
    const point_t c = {scale.xc, scale.yc, scale.zc};

    point.x = point.x * scale.kx + (1 - scale.kx) * c.x;
    point.y = point.y * scale.ky + (1 - scale.ky) * c.y;
    point.z = point.z * scale.kz + (1 - scale.kz) * c.z;
}

void rotate_point(const rotate_t &rotate, point_t &point)
{
    const point_t c = {rotate.xc, rotate.yc, rotate.zc};

    double xy_angle = (rotate.xy_angle * M_PI) / 180;

    double x = point.x;
    double y = point.y;

    point.x = c.x + (x - c.x) * cos(xy_angle) - (y - c.y) * sin(xy_angle);
    point.y = c.y + (x - c.x) * sin(xy_angle) + (y - c.y) * cos(xy_angle);

    double xz_angle = (rotate.xz_angle * M_PI) / 180;

    x = point.x;
    double z = point.z;

    point.x = c.x + (x - c.x) * cos(xz_angle) + (z - c.z) * sin(xz_angle);
    point.z = c.z - (x - c.x) * sin(xz_angle) + (z - c.z) * cos(xz_angle);

    double yz_angle = (rotate.yz_angle * M_PI) / 180;

    y = point.y;
    z = point.z;

    point.y = c.y - (z - c.z) * sin(yz_angle) + (y - c.y) * cos(yz_angle);
    point.z = c.z + (z - c.z) * cos(yz_angle) + (y - c.y) * sin(yz_angle);
}

void to_display_point(display_point_t &disp_point, const point_t &point)
{
    disp_point.x = point.y - point.x / sqrt(2);
    disp_point.y = point.x / sqrt(2) - point.z;
}
