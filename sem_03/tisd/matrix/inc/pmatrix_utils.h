#ifndef PMATRIX_UTILS_H
#define PMATRIX_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include "pmatrix_create.h"
#include "matrix_create.h"

#define INC_SIZE 2

#define INPUT_ER 20

int read_pmatrix_from_matrix(pmatrix_t *pmtr, matrix_t mtr);
int fread_pmatrix(pmatrix_t *pmtr, FILE *src);
void fwrite_pmatrix(pmatrix_t pmtr, FILE *dst);
int read_pvector_from_vector(pvector_t *pvec, column_t vec);
void fwrite_pvector(pvector_t pvec, FILE *dst);
int fread_pvector(pvector_t *pvec, FILE *src);
//int mlt_pmtr_pvec(pmatrix_t pmtr, pvector_t column, pvector_t *res);
int mlt_pmtr_pvec(pmatrix_t pmtr, pvector_t column, pvector_t *res, size_t *pi);

#endif // PMATRIX_UTILS_H