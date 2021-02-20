#ifndef MATRIX_CREATE_H
#define MATRIX_CREATE_H

#include <stdio.h>
#include <stdlib.h>

#define MEM_ER 10

#define ELEM_LEN "6"
#define EL_SCN "%d"
#define EL_PRN "%"ELEM_LEN"d"

typedef int elem_t;

typedef struct
{
    size_t rows;
    size_t columns;
    elem_t **matrix;
}matrix_t;

typedef struct
{
    size_t rows;
    elem_t *column;
}column_t;


void free_matrix(matrix_t *mtr);
int allocate_matrix(matrix_t *mtr, size_t n, size_t m);
int allocate_column(size_t rows, column_t *column);
void free_column(column_t column);

#endif //MATRIX_CREATE_H