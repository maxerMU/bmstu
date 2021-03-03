#include <fstream>
#include "point.h"
#include "edge.h"


edge_t *create_edge()
{
    return new edge_t;
}

void delete_edge(edge_t *edge)
{
    delete edge;
}

int read_edge(FILE *src, edge_t &edge)
{
    int rc = read_point(src, edge.p1);
    if (!rc)
        rc = read_point(src, edge.p2);

    return rc;
}

void write_edge(FILE *dst, edge_t edge)
{
    write_point(dst, edge.p1);
    fprintf(dst, " ");
    write_point(dst, edge.p2);
}
