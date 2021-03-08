#include <stdio.h>
#include <stdarg.h>
#include <vector>
#include <math.h>
#include "point.h"
#include "edge.h"
#include "figure.h"
#include "errors.h"

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
    else if (feof(src))
        rc = SUCCESS;

    return rc;
}

void write_figure(FILE *dst, const figure_t &figure)
{
    for (edge_t edge : figure.edges)
    {
        write_edge(dst, edge);
        fprintf(dst, "\n");
    }
}

int get_display_edge(const size_t index, display_edge_t &edge, const figure_t &figure)
{
    int rc = SUCCESS;
    if (index >= figure.edges.size())
        rc = WRONG_EDGE_INDEX;
    else
    {
        to_display_edge(edge, figure.edges[index]);
    }

    return rc;
}

void move_figure(const move_t &move, figure_t &figure)
{
    for (size_t i = 0; i < figure.edges.size(); i++)
        move_edge(move, figure.edges[i]);
}

void scale_figure(const scale_t &scale, figure_t &figure)
{
    for (size_t i = 0; i < figure.edges.size(); i++)
        scale_edge(scale, figure.edges[i]);
}

void rotate_figure(const rotate_t &rotate, figure_t &figure)
{
    for (size_t i = 0; i < figure.edges.size(); i++)
        rotate_edge(rotate, figure.edges[i]);
}


int figure_manager(action_t action, ...)
{
    static figure_t figure;

    int rc = SUCCESS;

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
    else if (action == MOVE)
    {
        const move_t move = va_arg(vl, move_t);
        move_figure(move, figure);
    }
    else if (action == SCALE)
    {
        const scale_t scale = va_arg(vl, scale_t);
        scale_figure(scale, figure);
    }
    else if (action == ROTATE)
    {
        const rotate_t rotate = va_arg(vl, rotate_t);
        rotate_figure(rotate, figure);
    }

    va_end(vl);

    return rc;
}
