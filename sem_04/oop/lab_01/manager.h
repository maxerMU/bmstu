#ifndef MANAGER_H
#define MANAGER_H

#include "convert.h"
#include "display_figure.h"

enum action_t
{
    READ, // char *src
    WRITE, // char *dst
    GET_DISP_FIGURE, // size_t edge_index, display_figure_t *display_figure
    MOVE, // move_t
    SCALE, // scale_t
    ROTATE, // rotate_t
    FREE,
};

union parameters_t
{
    char *file_name;
    move_t move_params;
    scale_t scale_params;
    rotate_t rotate_params;
};

int figure_manager(display_figure_t &display_figure, const action_t &action, const parameters_t &params);

#endif // MANAGER_H
