#ifndef DISPLAY_POINTS_H
#define DISPLAY_POINTS_H

#include "display_point.h"
#include "points.h"

struct display_points_t
{
    display_point_t *disp_points;
    size_t size;
};

display_points_t disp_points_init();
void to_display_points(display_points_t &disp_points, const points_t &points);
int display_points_mem_manager(display_points_t &disp_points, size_t size);

#endif // DISPLAY_POINTS_H
