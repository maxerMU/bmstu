#include "pmatrix_create.h"

int allocate_rows_start(row_start_t **rs)
{
    *rs = malloc(sizeof(row_start_t));
    if (!*rs)
        return MEM_ER;
    (*rs)->next = NULL;

    return EXIT_SUCCESS;
}

void free_rows_start(row_start_t *rs)
{
    free(rs);
}

void free_pmatrix(pmatrix_t *pmtr)
{
    free(pmtr->columns_numbers);
    free(pmtr->values);
    pmtr->values = NULL;
    pmtr->columns_numbers = NULL;
    while (pmtr->head_row_starts)
    {
        row_start_t *next = pmtr->head_row_starts->next;
        free(pmtr->head_row_starts);
        pmtr->head_row_starts = next;
    }
    pmtr->head_row_starts = NULL;
    pmtr->columns_allocated = 0;
    pmtr->columns = 0;
}

int allocate_pmatrix(pmatrix_t *pmtr)
{
    pmtr->columns = 0;
    pmtr->columns_allocated = 0;
    pmtr->values = NULL;
    pmtr->columns_numbers = NULL;
    int rc = allocate_rows_start(&pmtr->head_row_starts);
    if (rc)
    {
        free_pmatrix(pmtr);
        return rc;
    }

    return EXIT_SUCCESS;
}

int change_pmcolumn_size(pmatrix_t *pmtr, size_t columns)
{
    pelem_t *pvalues = realloc(pmtr->values, columns * sizeof(pelem_t));
    if (!pvalues)
        return MEM_ER;
    pmtr->values = pvalues;
    
    size_t *pcolumns = realloc(pmtr->columns_numbers, columns * sizeof(size_t));
    if (!pcolumns)
        return MEM_ER;
    pmtr->columns_numbers = pcolumns;
    
    pmtr->columns_allocated = columns;
    
    return EXIT_SUCCESS;
}

int allocate_pvector(pvector_t *pvec)
{
    pvec->columns = 0;
    pvec->columns_allocated = 0;
    pvec->values = NULL;
    pvec->columns_numbers = NULL;
    return EXIT_SUCCESS;
}

void free_pvector(pvector_t *pvec)
{
    free(pvec->columns_numbers);
    free(pvec->values);
    pvec->values = NULL;
    pvec->columns_numbers = NULL;
    pvec->columns_allocated = 0;
    pvec->columns = 0;
}

int change_pvcolumn_size(pvector_t *pvec, size_t columns)
{
    pelem_t *pvalues = realloc(pvec->values, columns * sizeof(pelem_t));
    if (!pvalues)
        return MEM_ER;
    pvec->values = pvalues;
    
    size_t *pcolumns = realloc(pvec->columns_numbers, columns * sizeof(size_t));
    if (!pcolumns)
        return MEM_ER;
    pvec->columns_numbers = pcolumns;
    
    pvec->columns_allocated = columns;
    
    return EXIT_SUCCESS;
}