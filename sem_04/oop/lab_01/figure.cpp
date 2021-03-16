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

bool is_correct_figure(const figure_t &figure)
{
    bool correct = figure.is_loaded;
    if (correct)
        correct = are_coorect_edges(figure.edges, figure.points.size);

    if (correct)
        correct = are_correct_points(figure.points);

    return correct;
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
    if (!is_correct_figure(figure))
        return INCORRECT_FIGURE;

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
    FILE *f = fopen(file_name, "r");
    if (!f)
        return OPEN_ER;

    figure_t tmp = figure_init();

    int rc = read_point(tmp.center, f);
    if (!rc)
    {
        rc = read_points(tmp.points, f);
        if (!rc)
            rc = read_edges(tmp.edges, f);
    }

    fclose(f);

    if (!rc)
    {
        tmp.is_loaded = true;
        if (is_correct_figure(tmp))
        {
            free_figure(figure);
            figure = tmp;
        }
        else
            rc = INCORRECT_FIGURE;
    }

    if (rc)
        free_figure(tmp);


    return rc;
}

int move_figure(figure_t &figure, const move_t &move)
{
    if (!is_correct_figure(figure))
        return INCORRECT_FIGURE;

    int rc = move_point(figure.center, move);
    if (rc)
        return rc;

    rc = move_points(figure.points, move);

    return rc;
}

int scale_figure(figure_t &figure, const scale_t &scale)
{
    if (!is_correct_figure(figure))
        return INCORRECT_FIGURE;

    int rc = scale_points(figure.points, scale, figure.center);

    return rc;
}

int rotate_figure(figure_t &figure, const rotate_t &rotate)
{
    if (!is_correct_figure(figure))
        return INCORRECT_FIGURE;

    int rc = rotate_points(figure.points, rotate, figure.center);

    return rc;
}
