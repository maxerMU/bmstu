#ifndef METHODS_H
#define METHODS_H

#include "plot_funcs.h"

typedef void (*draw_func_t)(plot_params_t &, int, int, int, int);

void lib(plot_params_t &params, int x1, int y1, int x2, int y2);
void cda(plot_params_t &params, int x1, int y1, int x2, int y2);
void brezenhem_real(plot_params_t &params, int x1, int y1, int x2, int y2);
void brezenhem_int(plot_params_t &params, int x1, int y1, int x2, int y2);
void brezenhem_del_stair(plot_params_t &params, int x1, int y1, int x2, int y2);
void wu(plot_params_t &params, int x1, int y1, int x2, int y2);

#endif // METHODS_H
