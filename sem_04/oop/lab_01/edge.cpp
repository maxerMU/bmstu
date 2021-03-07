#include <fstream>
#include "point.h"
#include "edge.h"

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

void move_edge(double dx, double dy, double dz, edge_t &edge)
{
    move_point(dx, dy, dz, edge.p1);
    move_point(dx, dy, dz, edge.p2);
}

void scale_edge(point_t c, double kx, double ky, double kz, edge_t &edge)
{
    scale_point(c, kx, ky, kz, edge.p1);
    scale_point(c, kx, ky, kz, edge.p2);
}

void rotate_edge(point_t c, double xy_ang, double xz_ang, double yz_ang, edge_t &edge)
{
    rotate_point(c, xy_ang, xz_ang, yz_ang, edge.p1);
    rotate_point(c, xy_ang, xz_ang, yz_ang, edge.p2);
}

void to_display_edge(display_edge_t &disp_edge, edge_t edge)
{
    to_display_point(disp_edge.p1, edge.p1);
    to_display_point(disp_edge.p2, edge.p2);
}
