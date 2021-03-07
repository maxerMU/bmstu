#ifndef EDGE_H
#define EDGE_H

#include <stdio.h>
#include "point.h"

typedef struct
{
    point_t p1;
    point_t p2;
}edge_t;

typedef struct
{
    display_point_t p1;
    display_point_t p2;
}display_edge_t;

int read_edge(FILE *src, edge_t &edge);
void write_edge(FILE *dst, edge_t edge);
void move_edge(double dx, double dy, double dz, edge_t &edge);
void scale_edge(point_t c, double kx, double ky, double kz, edge_t &edge);
void rotate_edge(point_t c, double xy_ang, double xz_ang, double yz_ang, edge_t &edge);
void to_display_edge(display_edge_t &disp_edge, edge_t edge);

#endif // EDGE_H
