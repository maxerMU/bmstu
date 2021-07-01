#ifndef ELLIPSE_METHODS_H
#define ELLIPSE_METHODS_H

#include "plot_funcs.h"

typedef void (*ellipse_func_t)(const plot_params_t &, long, long, long, long);

void ellipse_lib(const plot_params_t &params, long xc, long yc, long px, long py);
void ellipse_canon(const plot_params_t &params, long xc, long yc, long px, long py);
void ellipse_param(const plot_params_t &params, long xc, long yc, long px, long py);
void ellipse_brez(const plot_params_t &params, long xc, long yc, long px, long py);
void ellipse_mid(const plot_params_t &params, long xc, long yc, long px, long py);

#endif // ELLIPSE_METHODS_H
