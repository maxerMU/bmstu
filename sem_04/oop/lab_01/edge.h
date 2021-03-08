#ifndef EDGE_H
#define EDGE_H

#include <stdio.h>
#include "point.h"
#include "convert.h"

typedef struct
{
    point_t p1;
    point_t p2;
}edge_t;

int read_edge(FILE *src, edge_t &edge);
void write_edge(FILE *dst, const edge_t &edge);
void move_edge(const move_t &move, edge_t &edge);
void scale_edge(const scale_t &scale, edge_t &edge);
void rotate_edge(const rotate_t &rotate, edge_t &edge);
void to_display_edge(display_edge_t &disp_edge, edge_t edge);

#endif // EDGE_H
