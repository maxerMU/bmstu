#ifndef EDGES_H
#define EDGES_H

#include "edge.h"

struct edges_t
{
    edge_t *edges;
    size_t size;
};

edges_t init_edges();
int edges_dup(edges_t &dst, const edges_t &src);
int read_edges(edges_t &edges, FILE *const src);
void write_edges(FILE *const dst, const edges_t &edges);
bool are_coorect_edges(const edges_t &edges, size_t max_num);
int realloc_edges(edges_t &edges, const size_t size);
void free_edges(edges_t &edges);

#endif // EDGES_H
