#ifndef POINT_CPP
#define POINT_CPP

// #include <math.h>

#include <stdio.h>
#include "convert.h"

struct point_t
{
    double x;
    double y;
    double z;
};

int read_point(point_t &point, FILE *src);
int write_point(FILE *dst, const point_t &point);
int move_point(point_t &point, const move_t &move);
int scale_point(point_t &point, const scale_t &scale, const point_t &c);
int rotate_point(point_t &point, const rotate_t &rotate, const point_t &c);

#endif // POINT_CPP
