#include "convert.h"
#include "point.h"
#include "edge.h"
#include "errors.h"

int read_edge(FILE *src, edge_t &edge)
{
    int rc = read_point(src, edge.p1);
    if (!rc)
        rc = read_point(src, edge.p2);

    return rc;
}

void write_edge(FILE *dst, const edge_t &edge)
{
    write_point(dst, edge.p1);
    fprintf(dst, " ");
    write_point(dst, edge.p2);
}

void move_edge(const move_t &move, edge_t &edge)
{
    move_point(move, edge.p1);
    move_point(move, edge.p2);
}

void scale_edge(const scale_t &scale, edge_t &edge)
{
    scale_point(scale, edge.p1);
    scale_point(scale, edge.p2);
}

void rotate_edge(const rotate_t &rotate, edge_t &edge)
{
    rotate_point(rotate, edge.p1);
    rotate_point(rotate, edge.p2);
}

void to_display_edge(display_edge_t &disp_edge, edge_t edge)
{
    to_display_point(disp_edge.p1, edge.p1);
    to_display_point(disp_edge.p2, edge.p2);
}
