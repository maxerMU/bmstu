#include <stdlib.h>
#include "errors.h"
#include "points.h"

points_t init_points()
{
    points_t points;
    points.points = NULL;
    points.size = 0;

    return points;
}

int points_mem_manager(points_t &points, size_t new_size)
{
    point_t *temp = (point_t *) realloc(points.points, new_size * sizeof(point_t));

    if (!temp)
        return POINTS_ALLOC_ER;

    points.points = temp;
    points.size = new_size;

    return SUCCESS;
}

int scan_points_size(size_t *size, FILE *const src)
{
    int rc = SUCCESS;
    if (fscanf(src, "%zu", size) != 1)
        rc = POINTS_READ_ER;

    return rc;
}

void print_points_size(FILE *const dst, const size_t size)
{
    fprintf(dst, "%zu\n", size);
}

int scan_points(points_t &points, FILE *const src)
{
    int rc = SUCCESS;

    for (size_t i = 0; i < points.size && !rc; i++)
        rc = read_point(points.points[i], src);

    return rc;
}

void print_points(FILE *const dst, const points_t &points)
{
    for (size_t i = 0; i < points.size; i++)
    {
        write_point(dst, points.points[i]);
        fprintf(dst, "\n");
    }
}

int read_points(points_t &points, FILE *const src)
{
    size_t size;

    int rc = scan_points_size(&size, src);
    if (rc)
        return rc;

    rc = points_mem_manager(points, size);
    if (rc)
        return rc;

    rc = scan_points(points, src);
    if (rc)
    {
        points_mem_manager(points, 0);
        return rc;
    }

    return SUCCESS;
}

void write_points(FILE *const dst, const points_t &points)
{
    print_points_size(dst, points.size);
    print_points(dst, points);
}

int move_points(points_t &points, const move_t &move)
{
    for (size_t i = 0; i < points.size; i++)
        move_point(points.points[i], move);

    return SUCCESS;
}


int scale_points(points_t &points, const scale_t &scale, const point_t &c)
{
    for (size_t i = 0; i < points.size; i++)
        scale_point(points.points[i], scale, c);

    return SUCCESS;
}


int rotate_points(points_t &points, const rotate_t &rotate, const point_t &c)
{
    for (size_t i = 0; i < points.size; i++)
        rotate_point(points.points[i], rotate, c);

    return SUCCESS;
}
