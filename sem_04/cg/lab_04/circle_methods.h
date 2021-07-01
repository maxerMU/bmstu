#ifndef CIRCLE_METHODS_H
#define CIRCLE_METHODS_H

#include "plot_funcs.h"

typedef void (*circle_func)(const plot_params_t &, long, long, long);

void circle_lib(const plot_params_t &params, long x, long y, long r);
void circle_canon(const plot_params_t &params, long x, long y, long r);
void circle_param(const plot_params_t &params, long x, long y, long r);
void circle_brez(const plot_params_t &params, long x, long y, long r);
void circle_mid(const plot_params_t &params, long x, long y, long r);

#endif // CIRCLE_METHODS_H
