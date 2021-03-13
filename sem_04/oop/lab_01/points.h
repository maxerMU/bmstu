#ifndef POINTS_H
#define POINTS_H

#include "point.h"

struct points_t
{
    point_t *points;
    size_t size;
};

points_t init_points();
int points_mem_manager(points_t &points, size_t new_size);
int read_points(points_t &points, FILE *const src);
void write_points(FILE *const dst, const points_t &points);
int move_points(points_t &points, const move_t &move);
int scale_points(points_t &points, const scale_t &scale, const point_t &c);
int rotate_points(points_t &points, const rotate_t &rotate, const point_t &c);

#endif // POINTS_H
