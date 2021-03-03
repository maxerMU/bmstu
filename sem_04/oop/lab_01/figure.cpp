#include <stdarg.h>
#include <vector>
#include <math.h>
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

int get_display_edge(size_t index, display_edge_t &edge, figure_t figure)
{
    int rc = FIGURE_SUCCESS;
    if (index >= figure.edges.size())
        rc = WRONG_EDGE_INDEX;
    else
    {
        edge.x1 = figure.edges[index].p1.x - figure.edges[index].p1.y / sqrt(2);
        edge.y1 = figure.edges[index].p1.y / sqrt(2) - figure.edges[index].p1.z;
        edge.x2 = figure.edges[index].p2.x - figure.edges[index].p2.y / sqrt(2);
        edge.y2 = figure.edges[index].p2.y / sqrt(2) - figure.edges[index].p2.z;
    }

    return rc;
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
        display_edge_t *edge = va_arg(vl, display_edge_t *);
        rc = get_display_edge(index, *edge, figure);
    }

    return rc;
}
