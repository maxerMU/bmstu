#include "display_points.h"
#include "errors.h"

display_points_t disp_points_init()
{
    display_points_t disp_points;
    disp_points.disp_points = NULL;
    disp_points.size = 0;

    return disp_points;
}

int display_points_mem_manager(display_points_t &disp_points, size_t size)
{
    display_point_t *temp = (display_point_t *) realloc(disp_points.disp_points, size * sizeof(display_point_t));

    if (!temp)
        return DISP_POINTS_ALLOC_ER;

    disp_points.disp_points = temp;
    disp_points.size = size;

    return SUCCESS;
}

void to_display_points(display_points_t &disp_points, const points_t &points)
{
    for (size_t i = 0; i < disp_points.size; i++)
        to_display_point(disp_points.disp_points[i], points.points[i]);
}
