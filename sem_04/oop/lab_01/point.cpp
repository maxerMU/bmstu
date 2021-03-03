#include <stdio.h>
#include "point.h"

point_t *create_point()
{
    return new point_t;
}

void delete_point(point_t *point)
{
    delete point;
}

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

void write_point(FILE *dst, point_t point)
{
    fprintf(dst, "%lf %lf %lf", point.x, point.y, point.z);
}
