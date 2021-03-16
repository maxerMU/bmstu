#include <stdarg.h>
#include "manager.h"
#include "figure.h"
#include "errors.h"

int figure_manager(display_figure_t &display_figure, const action_t &action, const parameters_t &params)
{
    static figure_t figure = figure_init();

    int rc = SUCCESS;

    if (action == READ)
    {
        rc = read_figure(figure, params.file_name);
    }
    else if (action == WRITE)
    {
        rc = write_figure(figure, params.file_name);
    }
    else if (action == GET_DISP_FIGURE)
    {
        rc = to_display_figure(display_figure, figure);
    }
    else if (action == MOVE)
    {
        rc = move_figure(figure, params.move_params);
    }
    else if (action == SCALE)
    {
        rc = scale_figure(figure, params.scale_params);
    }
    else if (action == ROTATE)
    {
        rc = rotate_figure(figure, params.rotate_params);
    }
    else if (action == FREE)
    {
        rc = free_figure(figure);
    }
    else
    {
        rc = WRONG_COMMAND;
    }

    return rc;
}
