#include "display_points.h"
#include "errors.h"

display_points_t disp_points_init()
{
    display_points_t disp_points;
    disp_points.disp_points = NULL;
    disp_points.size = 0;

    return disp_points;
}

bool are_correct_disp_points(const display_points_t &points)
{
    return (points.disp_points) && (points.size);
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

int to_display_points(display_points_t &disp_points, const points_t &points)
{
    if (!are_correct_disp_points(disp_points))
        return INCORRECT_DISP_POINTS;

    int rc = SUCCESS;

    for (size_t i = 0; i < disp_points.size && !rc; i++)
        rc = to_display_point(disp_points.disp_points[i], points.points[i]);

    return rc;
}
