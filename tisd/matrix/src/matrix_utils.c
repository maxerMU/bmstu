#include <string.h>
#include <math.h>
#include "matrix_utils.h"
#include "read_funcs.h"

void gen_matrix(matrix_t *mtr, double percent, int min, int max)
{
    for (size_t i = 0; i < mtr->rows; i++)
        memset(mtr->matrix[i], 0, sizeof(elem_t) * mtr->columns);

    size_t pos_i, pos_j;
    long zeros = trunc(mtr->rows * percent * mtr->columns);
    while (zeros > 0)
    {
        pos_i = rand() % mtr->rows;
        pos_j = rand() % mtr->columns;
        if (mtr->matrix[pos_i][pos_j] == 0)
        {
            mtr->matrix[pos_i][pos_j] = rand() % (max - min + 1) + min;
            if (mtr->matrix[pos_i][pos_j] == 0)
                mtr->matrix[pos_i][pos_j]++;

            zeros--;
        }
    }
}

int mtr_read_by_coor(matrix_t *mtr)
{
    for (size_t i = 0; i < mtr->rows; i++)
        memset(mtr->matrix[i], 0, sizeof(elem_t) * mtr->columns);
    
    long r, c;
    printf("\nTo exit input -1\n");
    printf("Input coordinats: ");
    if (scanf("%ld %ld", &r, &c) != 2)
        return EXIT_FAILURE;
    while (r >= 0 && c >= 0 && r < (long) mtr->rows && c < (long) mtr->columns)
    {
        elem_t value;
        printf("Input value: ");
        if (scanf(EL_SCN, &value) != 1)
            return EXIT_FAILURE;

        mtr->matrix[r][c] = value;
        printf("\nTo exit input -1\n");
        printf("Input coordinats: ");
        if (scanf("%ld %ld", &r, &c) != 2)
            return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

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

    if (src == stdin)
    {
        int choose;
        printf("If you want input matrix by coordinats, enter 1: ");
        if (scanf("%d", &choose) != 1)
            return INPUT_ER;
    
        if (choose == 1)
        {
            int rc = mtr_read_by_coor(mtr);
            return rc;
        }
    }

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

void gen_vector(column_t *vec, double percent, int min, int max)
{
    memset(vec->column, 0, sizeof(elem_t) * vec->rows);

    size_t pos_i;
    long zeros = trunc(vec->rows * percent);
    while (zeros > 0)
    {
        pos_i = rand() % vec->rows;
        if (vec->column[pos_i] == 0)
        {
            vec->column[pos_i] = rand() % (max - min + 1) + min;
            if (vec->column[pos_i] == 0)
                vec->column[pos_i]++;

            zeros--;
        }
    }
}

int vec_read_by_coor(column_t *vec)
{
    memset(vec->column, 0, sizeof(elem_t) * vec->rows);

    long r;
    printf("\nTo exit input -1\n");
    printf("Input coordinats: ");
    if (scanf("%ld", &r) != 1)
        return EXIT_FAILURE;
    while (r >= 0 && r < (long) vec->rows)
    {
        elem_t value;
        printf("Input value: ");
        if (scanf(EL_SCN, &value) != 1)
            return EXIT_FAILURE;

        vec->column[r] = value;
        printf("\nTo exit input -1\n");
        printf("Input coordinats: ");
        if (scanf("%ld", &r) != 1)
            return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

int fread_vector(column_t *vector, FILE *src)
{
    int n;
    if (fread_signed_int(&n, src) || n <= 0)
        return INPUT_ER;
    
    int rc = allocate_column(n, vector);

    if (rc)
        return rc;

    if (src == stdin)
    {
        int choose;
        printf("If you want input matrix by coordinats, enter 1: ");
        if (scanf("%d", &choose) != 1)
            return INPUT_ER;
    
        if (choose == 1)
        {
            int rc = vec_read_by_coor(vector);
            return rc;
        }
    }

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