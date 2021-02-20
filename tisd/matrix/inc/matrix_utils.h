#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include "matrix_create.h"

#define INPUT_ER 20
#define SIZE_ER 21
#define SQR_ER 22
#define POW_ER 23

void gen_vector(column_t *vec, double percent, int min, int max);
void gen_matrix(matrix_t *mtr, double percent, int min, int max);
int fread_matrix(matrix_t *mtr, FILE *src);
void fwrite_matrix(matrix_t mtr, FILE *dst);
int fread_vector(column_t *vector, FILE *src);
void fwrite_vector(column_t vector, FILE *dst);
int mlt_mtr_vec(matrix_t mtr, column_t column, column_t *res);

#endif //MATRIX_UTILS_H