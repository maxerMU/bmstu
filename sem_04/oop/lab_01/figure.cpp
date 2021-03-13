#include <stdio.h>
#include <math.h>
#include "point.h"
#include "edge.h"
#include "figure.h"
#include "errors.h"

figure_t figure_init()
{
    figure_t figure;
    figure.edges = init_edges();
    figure.points = init_points();
    figure.is_loaded = false;

    return figure;
}

int free_figure(figure_t &figure)
{
    points_mem_manager(figure.points, 0);
    edges_mem_manager(figure.edges, 0);

    figure = figure_init();

    return SUCCESS;
}

int write_figure(const figure_t &figure, const char *file_name)
{
    if (!figure.is_loaded)
        return UNINIT_FIGURE;

    FILE *dst = fopen(file_name, "w");
    if (!dst)
        return OPEN_ER;

    write_point(dst, figure.center);
    fprintf(dst, "\n");
    write_points(dst, figure.points);
    write_edges(dst, figure.edges);

    fclose(dst);

    return SUCCESS;
}

int read_figure(figure_t &figure, const char *file_name)
{
    figure_t tmp = figure_init();

    FILE *f = fopen(file_name, "r");
    if (!f)
        return OPEN_ER;

    int rc = read_point(tmp.center, f);
    if (rc)
    {
        fclose(f);
        return rc;
    }

    rc = read_points(tmp.points, f);
    if (rc)
    {
        fclose(f);
        return rc;
    }

    rc = read_edges(tmp.edges, f);
    if (rc)
    {
        fclose(f);
        free_figure(tmp);
        return rc;
    }

    if (!are_coorect_edges(figure.edges, figure.points.size))
    {
        rc = INCORRECT_EDGES;
        free_figure(tmp);
    }
    else
    {
        tmp.is_loaded = true;
        free_figure(figure);
        figure = tmp;
    }

    fclose(f);

    return rc;
}

int move_figure(figure_t &figure, const move_t &move)
{
    if (!figure.is_loaded)
        return UNINIT_FIGURE;

    int rc = move_point(figure.center, move);
    if (rc)
        return rc;

    rc = move_points(figure.points, move);

    return rc;
}

int scale_figure(figure_t &figure, const scale_t &scale)
{
    if (!figure.is_loaded)
        return UNINIT_FIGURE;

    int rc = scale_points(figure.points, scale, figure.center);

    return rc;
}

int rotate_figure(figure_t &figure, const rotate_t &rotate)
{
    if (!figure.is_loaded)
        return UNINIT_FIGURE;

    int rc = rotate_points(figure.points, rotate, figure.center);

    return rc;
}
