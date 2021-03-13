#ifndef DISPLAY_EDGE_H
#define DISPLAY_EDGE_H

#include "edge.h"
#include "display_point.h"

struct display_edge_t
{
    display_point_t p1;
    display_point_t p2;
};

int to_display_edge(display_edge_t &disp_edge, const edge_t &edge);

#endif // DISPLAY_EDGE_H
