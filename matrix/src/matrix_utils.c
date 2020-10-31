#include "matrix_utils.h"
#include "read_funcs.h"

int fread_matrix(matrix_t *mtr, FILE *src)
{
    int n, m;
    if (fread_signed_int(&n, src) || n <= 0)
        return INPUT_ER;

    if (fread_signed_int(&m, src) || m <= 0)
        return INPUT_ER;
    
    int rc = allocate_matrix(mtr, n, m);

    if (rc)
        return rc;

    for (size_t i = 0; i < mtr->rows; i++)
        for (size_t j = 0; j < mtr->columns; j++)
            if (fread_signed_int(&mtr->matrix[i][j], src))
            {
                free_matrix(mtr);
                return INPUT_ER;
            }

    return EXIT_SUCCESS;
}

void fwrite_matrix(matrix_t mtr, FILE *dst)
{
    for (size_t i = 0; i < mtr.rows; i++)
    {
        for (size_t j = 0; j < mtr.columns - 1; j++)
            fprintf(dst, EL_PRN" ", mtr.matrix[i][j]);
        fprintf(dst, EL_PRN"\n", mtr.matrix[i][mtr.columns - 1]);
    }
}

int fread_vector(column_t *vector, FILE *src)
{
    int n;
    if (fread_signed_int(&n, src) || n <= 0)
        return INPUT_ER;
    
    int rc = allocate_column(n, vector);

    if (rc)
        return rc;

    for (size_t i = 0; i < vector->rows; i++)
        if (fread_signed_int(&vector->column[i], src))
        {
            free_column(*vector);
            return INPUT_ER;
        }

    return EXIT_SUCCESS; 
}

void fwrite_vector(column_t vector, FILE *dst)
{
    for (size_t i = 0; i < vector.rows; i++)
        fprintf(dst, EL_PRN"\n", vector.column[i]);
}

int mlt_mtr_vec(matrix_t mtr, column_t column, column_t *res)
{
    for (size_t i = 0; i < mtr.rows; i++)
    {
        res->column[i] = 0;
        for (size_t j = 0; j < column.rows; j++)
            res->column[i] += mtr.matrix[i][j] * column.column[j];
    }

    return EXIT_SUCCESS;
}