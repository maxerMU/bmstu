#ifndef DISPLAY_POINT_H
#define DISPLAY_POINT_H

#include "point.h"

struct display_point_t
{
    long x;
    long y;
};

int to_display_point(display_point_t &disp_point, const point_t &point);

#endif // DISPLAY_POINT_H
