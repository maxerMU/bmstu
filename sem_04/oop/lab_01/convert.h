#ifndef CONVERT_H
#define CONVERT_H

#include <stdlib.h>

struct move_t
{
    double dx;
    double dy;
    double dz;
};

struct scale_t
{
    double kx;
    double ky;
    double kz;
};

struct rotate_t
{
    double xy_angle;
    double xz_angle;
    double yz_angle;
};

#endif // CONVERT_H
