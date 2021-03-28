#ifndef METHODS_STAIR_H
#define METHODS_STAIR_H

#define STAIRS_OPEN_ER 1

#include <stdlib.h>

typedef size_t(*stairs_func_t)(int, int, int, int);

int stairs_table(const char *file_name, double angle_step, double r, stairs_func_t func);
size_t cda_stairs(int x1, int y1, int x2, int y2);
size_t brezenhem_real_stairs(int x1, int y1, int x2, int y2);
size_t brezenhem_int_stairs(int x1, int y1, int x2, int y2);
size_t brezenhem_del_stair_stairs(int x1, int y1, int x2, int y2);
size_t wu_stairs(int x1, int y1, int x2, int y2);

#endif // METHODS_STAIR_H
