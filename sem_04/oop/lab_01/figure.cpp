#include <stdarg.h>
#include <vector>
#include <math.h>
#include "point.h"
#include "edge.h"
#include "figure.h"

typedef struct figure
{
    std::vector<edge_t> edges;
}figure_t;

int read_figure(FILE *src, figure_t &figure)
{
    edge_t edge;
    int rc = read_edge(src, edge);
    while (!rc)
    {
        figure.edges.push_back(edge);
        rc = read_edge(src, edge);
    }

    if (figure.edges.size() == 0)
        rc = EMPTY_FIGURE;
    else
        rc = FIGURE_SUCCESS;

    return rc;
}

void write_figure(FILE *dst, figure_t figure)
{
    for (edge_t edge : figure.edges)
    {
        write_edge(dst, edge);
        fprintf(dst, "\n");
    }
}

int get_display_edge(size_t index, draw_edge_t &edge, figure_t figure)
{
    int rc = FIGURE_SUCCESS;
    if (index >= figure.edges.size())
        rc = WRONG_EDGE_INDEX;
    else
    {
        display_edge_t disp_edge;
        to_display_edge(disp_edge, figure.edges[index]);
        edge.x1 = disp_edge.p1.x;
        edge.y1 = disp_edge.p1.y;
        edge.x2 = disp_edge.p2.x;
        edge.y2 = disp_edge.p2.y;
    }

    return rc;
}

void move_figure(double dx, double dy, double dz, figure_t &figure)
{
    for (size_t i = 0; i < figure.edges.size(); i++)
        move_edge(dx, dy, dz, figure.edges[i]);
}

void scale_figure(point_t c, double kx, double ky, double kz, figure_t &figure)
{
    for (size_t i = 0; i < figure.edges.size(); i++)
        scale_edge(c, kx, ky, kz, figure.edges[i]);
}

void rotate_figure(point_t c, double xy_ang, double xz_ang, double yz_ang, figure_t &figure)
{
    for (size_t i = 0; i < figure.edges.size(); i++)
        rotate_edge(c, xy_ang, xz_ang, yz_ang, figure.edges[i]);
}


int figure_manager(action_t action, ...)
{
    static figure_t figure;

    int rc = FIGURE_SUCCESS;

    va_list vl;
    va_start(vl, action);

    if (action == READ)
    {
        FILE *src = va_arg(vl, FILE *);
        rc = read_figure(src, figure);
    }
    else if (action == WRITE)
    {
        FILE *dst = va_arg(vl, FILE *);
        write_figure(dst, figure);
    }
    else if (action == GET_DISP_EDGE)
    {
        size_t index = va_arg(vl, size_t);
        draw_edge_t *edge = va_arg(vl, draw_edge_t *);
        rc = get_display_edge(index, *edge, figure);
    }
    else if (action == MOVE)
    {
        double dx = va_arg(vl, double);
        double dy = va_arg(vl, double);
        double dz = va_arg(vl, double);
        move_figure(dx, dy, dz, figure);
    }
    else if (action == SCALE)
    {
        point_t c;
        c.x = va_arg(vl, double);
        c.y = va_arg(vl, double);
        c.z = va_arg(vl, double);
        double kx = va_arg(vl, double);
        double ky = va_arg(vl, double);
        double kz = va_arg(vl, double);

        scale_figure(c, kx, ky, kz, figure);
    }
    else if (action == ROTATE)
    {
        point_t c;
        c.x = va_arg(vl, double);
        c.y = va_arg(vl, double);
        c.z = va_arg(vl, double);
        double xy_ang = va_arg(vl, double);
        double xz_ang = va_arg(vl, double);
        double yz_ang = va_arg(vl, double);

        rotate_figure(c, xy_ang, xz_ang, yz_ang, figure);
    }

    va_end(vl);

    return rc;
}
