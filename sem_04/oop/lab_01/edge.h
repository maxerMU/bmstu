#ifndef EDGE_H
#define EDGE_H

#include <stdio.h>
#include "point.h"
#include "convert.h"

struct edge_t
{
    size_t p1;
    size_t p2;
};

int read_edge(edge_t &edge, FILE * const src);
void write_edge(FILE * const dst, const edge_t &edge);
bool is_correct_edge(const edge_t &edge, size_t max_num);
int move_edge(edge_t &edge, const move_t &move);
int scale_edge(edge_t &edge, const scale_t &scale, const point_t &c);
int rotate_edge(edge_t &edge, const rotate_t &rotate, const point_t &c);

#endif // EDGE_H
