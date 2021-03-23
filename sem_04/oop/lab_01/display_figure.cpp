#include "display_figure.h"
#include "errors.h"

display_figure_t init_display_figure()
{
    display_figure_t disp_figure;
    disp_figure.points = disp_points_init();
    disp_figure.edges = init_edges();

    return disp_figure;
}

int free_display_figure(display_figure_t &figure)
{
    free_display_points(figure.points);
    free_edges(figure.edges);

    return SUCCESS;
}

int to_display_figure(display_figure_t &display_figure, const figure_t &figure)
{
    display_figure_t temp = init_display_figure();

    int rc = edges_dup(temp.edges, figure.edges);
    if (rc)
        return rc;

    rc = realloc_display_points(temp.points, figure.points.size);
    if (rc)
    {
        free_display_figure(temp);
        return rc;
    }

    rc = to_display_points(temp.points, figure.points);
    if (!rc)
        display_figure = temp;

    return rc;
}
