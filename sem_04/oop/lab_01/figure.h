#ifndef FIGURE_H
#define FIGURE_H

#include "convert.h"
#include "point.h"
#include "edge.h"
#include "points.h"
#include "edges.h"

struct figure_t
{
    bool is_loaded;
    point_t center;
    edges_t edges;
    points_t points;
};

figure_t figure_init();
int free_figure(figure_t &figure);
int read_figure(figure_t &figure, const char *file_name);
int write_figure(const figure_t &figure, const char *file_name);
int move_figure(figure_t &figure, const move_t &move);
int scale_figure(figure_t &figure, const scale_t &scale);
int rotate_figure(figure_t &figure, const rotate_t &rotate);

#endif // FIGURE_H
