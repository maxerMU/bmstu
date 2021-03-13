#ifndef DISPLAY_FIGURE_H
#define DISPLAY_FIGURE_H

#include "figure.h"
#include "display_points.h"
#include "edges.h"

struct display_figure_t
{
    display_points_t points;
    edges_t edges;
};

int to_display_figure(display_figure_t &display_figure, const figure_t &figure);
display_figure_t init_display_figure();
int free_display_figure(display_figure_t &figure);

#endif // DISPLAY_FIGURE_H
