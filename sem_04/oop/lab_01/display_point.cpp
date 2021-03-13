#include <math.h>
#include "display_point.h"
#include "errors.h"

int to_display_point(display_point_t &disp_point, const point_t &point)
{
    disp_point.x = point.y - point.x / sqrt(2);
    disp_point.y = point.x / sqrt(2) - point.z;

    return SUCCESS;
}
