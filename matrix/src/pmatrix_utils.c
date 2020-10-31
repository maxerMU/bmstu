#include "pmatrix_utils.h"
#include "matrix_create.h"
#include "read_funcs.h"

int fread_pmatrix(pmatrix_t *pmtr, FILE *src)
{
    int n, m;
    if (fread_signed_int(&n, src) || n <= 0)
        return INPUT_ER;

    if (fread_signed_int(&m, src) || m <= 0)
        return INPUT_ER;
 
    int rc = allocate_pmatrix(pmtr);
    if (rc)
        return rc;
    
    row_start_t *current = pmtr->head_row_starts;
    pmtr->head_row_starts->index = 0;
    for (long i = 0; i < n; i++)
    {
        rc = allocate_rows_start(&current->next);
        if (rc)
        {
            free_pmatrix(pmtr);
            return rc;
        }

        for (long j = 0; j < m; j++)
        {
            pelem_t digit;
            rc = fread_signed_int(&digit, src);
            if (rc)
            {
                free_pmatrix(pmtr);
                return rc;
            }
            if (!digit)
                continue;
            if (pmtr->columns + 1 > pmtr->columns_allocated)
            {
                rc = change_pmcolumn_size(pmtr, pmtr->columns_allocated ? pmtr->columns_allocated * INC_SIZE : 1);
                if (rc)
                {
                    free_pmatrix(pmtr);
                    return rc;
                }
            }
            pmtr->values[pmtr->columns] = digit;
            pmtr->columns_numbers[pmtr->columns++] = j;
        }
        
        current->next->index = pmtr->columns;
        current = current->next;
    }

    return EXIT_SUCCESS;
}

void fwrite_pmatrix(pmatrix_t pmtr, FILE *dst)
{
    fputs("values:           ", dst);
    for (size_t j = 0; j < pmtr.columns; j++)
        fprintf(dst, "%6d ", pmtr.values[j]);
    fputs("\ncolumn_numbers:   ", dst);
    for (size_t j = 0; j < pmtr.columns; j++)
        fprintf(dst, "%6zu ", pmtr.columns_numbers[j]);
    fputs("\nrow starts indexes", dst);
    while (pmtr.head_row_starts)
    {
        fprintf(dst, "%6zu ", pmtr.head_row_starts->index);
        pmtr.head_row_starts = pmtr.head_row_starts->next;
    }
    fprintf(dst, "\n");
}

int read_pmatrix_from_matrix(pmatrix_t *pmtr, matrix_t mtr)
{
    int rc = allocate_pmatrix(pmtr);
    if (rc)
        return rc;
    
    row_start_t *current = pmtr->head_row_starts;
    pmtr->head_row_starts->index = 0;
    for (size_t i = 0; i < mtr.rows; i++)
    {
        rc = allocate_rows_start(&current->next);
        if (rc)
        {
            free_pmatrix(pmtr);
            return rc;
        }

        for (size_t j = 0; j < mtr.columns; j++)
        {
            pelem_t digit = mtr.matrix[i][j];
            if (!digit)
                continue;
            if (pmtr->columns + 1 > pmtr->columns_allocated)
            {
                rc = change_pmcolumn_size(pmtr, pmtr->columns_allocated ? pmtr->columns_allocated * INC_SIZE : 1);
                if (rc)
                {
                    free_pmatrix(pmtr);
                    return rc;
                }
            }
            pmtr->values[pmtr->columns] = digit;
            pmtr->columns_numbers[pmtr->columns++] = j;
        }
        
        current->next->index = pmtr->columns;
        current = current->next;
    }

    return EXIT_SUCCESS;
}

int fread_pvector(pvector_t *pvec, FILE *src)
{
    int n;
    if (fread_signed_int(&n, src) || n <= 0)
        return INPUT_ER;

    int rc = allocate_pvector(pvec);
    if (rc)
        return rc;
    
    for (long i = 0; i < n; i++)
    {
        pelem_t digit;
        rc = fread_signed_int(&digit, src);
        if (rc)
        {
            free_pvector(pvec);
            return rc;
        }
        if (!digit)
            continue;
        if (pvec->columns + 1 > pvec->columns_allocated)
        {
            rc = change_pvcolumn_size(pvec, pvec->columns_allocated ? pvec->columns_allocated * INC_SIZE : 1);
            if (rc)
            {
                free_pvector(pvec);
                return rc;
            }
        }
        pvec->values[pvec->columns] = digit;
        pvec->columns_numbers[pvec->columns++] = i;
    }

    return EXIT_SUCCESS;
}

void fwrite_pvector(pvector_t pvec, FILE *dst)
{
    fputs("values:           ", dst);
    for (size_t j = 0; j < pvec.columns; j++)
        fprintf(dst, "%6d ", pvec.values[j]);
    fputs("\ncolumn_numbers:   ", dst);
    for (size_t j = 0; j < pvec.columns; j++)
        fprintf(dst, "%6zu ", pvec.columns_numbers[j]);
    fprintf(dst, "\n");
}

int read_pvector_from_vector(pvector_t *pvec, column_t vec)
{
    int rc = allocate_pvector(pvec);
    if (rc)
        return rc;
    
    for (size_t i = 0; i < vec.rows; i++)
    {
        pelem_t digit;
        digit = vec.column[i];
        if (!digit)
            continue;
        if (pvec->columns + 1 > pvec->columns_allocated)
        {
            rc = change_pvcolumn_size(pvec, pvec->columns_allocated ? pvec->columns_allocated * INC_SIZE : 1);
            if (rc)
            {
                free_pvector(pvec);
                return rc;
            }
        }
        pvec->values[pvec->columns] = digit;
        pvec->columns_numbers[pvec->columns++] = i;
    }

    return EXIT_SUCCESS;
}

/*int mlt_pmtr_pvec(pmatrix_t pmtr, pvector_t column, pvector_t *res)
{
    res->columns = 0;
    size_t mvindex = 0;
    size_t rowindex = 0;
    for (pmtr.head_row_starts = pmtr.head_row_starts->next; pmtr.head_row_starts; pmtr.head_row_starts = pmtr.head_row_starts->next)
    {
        int result = 0;
        size_t k = 0;
        for (; mvindex < pmtr.head_row_starts->index; mvindex++)
        {
            for (; column.columns_numbers[k] < pmtr.columns_numbers[mvindex]; k++);
            if (pmtr.columns_numbers[mvindex] == column.columns_numbers[k])
                result += pmtr.values[mvindex] * column.values[k];
        }
        if (result)
        {
            res->values[res->columns] = result;
            res->columns_numbers[res->columns++] = rowindex;
        }
        rowindex++;
    }

    return EXIT_SUCCESS;
}*/

int mlt_pmtr_pvec(pmatrix_t pmtr, pvector_t column, pvector_t *res, size_t *pi)
{
    res->columns = 0;
    size_t mvindex = 0;
    size_t rowindex = 0;
    for (size_t i = 0; i < column.columns; i++)
        pi[column.columns_numbers[i]] = i + 1;
    for (pmtr.head_row_starts = pmtr.head_row_starts->next; pmtr.head_row_starts; pmtr.head_row_starts = pmtr.head_row_starts->next)
    {
        int result = 0;
        for (; mvindex < pmtr.head_row_starts->index; mvindex++)
        {
            if (pi[pmtr.columns_numbers[mvindex]])
                result += pmtr.values[mvindex] * column.values[pi[pmtr.columns_numbers[mvindex]] - 1];
        }
        if (result)
        {
            res->values[res->columns] = result;
            res->columns_numbers[res->columns++] = rowindex;
        }
        rowindex++;
    }

    return EXIT_SUCCESS;
}