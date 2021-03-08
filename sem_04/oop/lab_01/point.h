#ifndef POINT_CPP
#define POINT_CPP

// #include <math.h>

#include <stdio.h>
#include "convert.h"

typedef struct
{
    double x;
    double y;
    double z;
}point_t;

int read_point(FILE *src, point_t &point);
void write_point(FILE *dst, const point_t &point);
void move_point(const move_t &move, point_t &point);
void scale_point(const scale_t &scale, point_t &point);
void rotate_point(const rotate_t &rotate, point_t &point);
void to_display_point(display_point_t &disp_point, const point_t &point);

#endif // POINT_CPP
