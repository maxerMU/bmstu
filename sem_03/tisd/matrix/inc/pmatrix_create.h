#ifndef PMATRIX_CREATE_H
#define PMATRIX_CREATE_H

#include <stdio.h>
#include <stdlib.h>

#define MEM_ER 10

struct row_start
{
    size_t index;
    struct row_start *next;
};

typedef struct row_start row_start_t;

typedef int pelem_t;

typedef struct
{
    pelem_t *values;
    size_t *columns_numbers;
    size_t columns;
    size_t columns_allocated;
    row_start_t *head_row_starts;
}pmatrix_t;

typedef struct
{
    pelem_t *values;
    size_t *columns_numbers;
    size_t columns;
    size_t columns_allocated;
}pvector_t;

int allocate_rows_start(row_start_t **rs);
void free_pmatrix(pmatrix_t *pmtr);
int allocate_pmatrix(pmatrix_t *pmtr);
int change_pmcolumn_size(pmatrix_t *pmtr, size_t columns);
int allocate_pvector(pvector_t *pvec);
void free_pvector(pvector_t *pvec);
int change_pvcolumn_size(pvector_t *pvec, size_t columns);

#endif // PMATRIX_CREATE_H