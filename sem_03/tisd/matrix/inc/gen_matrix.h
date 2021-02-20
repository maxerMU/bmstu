#ifndef GEN_MATRIX_H
#define GEN_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void fgen_matrix(FILE *dst, size_t rows, size_t columns, double percent, int min, int max);
void fgen_vector(FILE *dst, size_t rows, double percent, int min, int max);

#endif // GEN_MATRIX_H
