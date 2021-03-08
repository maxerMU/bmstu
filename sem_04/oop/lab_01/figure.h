#ifndef FIGURE_H
#define FIGURE_H

// #include <stdio.h>
// #include <stdarg.h>
// #include <vector>
// #include <math.h>

typedef enum
{
    READ, // FILE *src
    WRITE, // FILE *dst
    GET_DISP_EDGE, // size_t edge_index, draw_edge_t &display_edge
    MOVE, // move_t
    SCALE, // scale_t
    ROTATE, // rotate_t
}action_t;

int figure_manager(action_t action, ...);

#endif // FIGURE_H
