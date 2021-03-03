#ifndef EDGE_H
#define EDGE_H

#include <stdio.h>
#include "point.h"

typedef struct
{
    point_t p1;
    point_t p2;
}edge_t;

edge_t *create_edge();
void delete_edge(edge_t *edge);
int read_edge(FILE *src, edge_t &edge);
void write_edge(FILE *dst, edge_t edge);

#endif // EDGE_H
