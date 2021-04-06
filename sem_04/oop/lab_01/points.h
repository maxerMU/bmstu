#ifndef POINTS_H
#define POINTS_H

#include "point.h"

struct points_t
{
    point_t *points;
    size_t size;
};

points_t init_points();
bool are_correct_points(const points_t &points);
int realloc_points(points_t &points, size_t new_size);
void free_points(points_t &points);
int read_points(points_t &points, FILE *const src);
void write_points(FILE *const dst, const points_t &points);
int move_points(points_t &points, const move_t &move);
int scale_points(points_t &points, const scale_t &scale, const point_t &c);
int rotate_points(points_t &points, const rotate_t &rotate, const point_t &c);

#endif // POINTS_H
