#ifndef FIGURE_H
#define FIGURE_H

#include <stdio.h>

#define FIGURE_SUCCESS 0
#define EMPTY_FIGURE 1
#define WRONG_EDGE_INDEX 2

typedef struct
{
    long x1;
    long y1;
    long x2;
    long y2;
}draw_edge_t;

typedef enum
{
    READ, // FILE *src
    WRITE, // FILE *dst
    GET_DISP_EDGE, // size_t edge_index, display_edge_t &display_edge
    MOVE, // double dx, double dy, double dz
    SCALE, // double xc, double yc, double zc, double kx, double ky, double kz
    ROTATE, // double xc, double yc, double zc, double xy, double xz, double yz
}action_t;

int figure_manager(action_t action, ...);

#endif // FIGURE_H
