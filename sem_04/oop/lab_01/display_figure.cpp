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
    display_points_mem_manager(figure.points, 0);
    edges_mem_manager(figure.edges, 0);

    return SUCCESS;
}

int to_display_figure(display_figure_t &display_figure, const figure_t &figure)
{
    display_figure_t temp = init_display_figure();

    int rc = edges_dup(temp.edges, figure.edges);
    if (rc)
        return rc;

    rc = display_points_mem_manager(temp.points, figure.points.size);
    if (rc)
    {
        free_display_figure(temp);
        return rc;
    }

    to_display_points(temp.points, figure.points);

    display_figure = temp;

    return rc;
}
