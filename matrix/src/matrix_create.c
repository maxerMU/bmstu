#include "matrix_create.h"

void free_matrix(matrix_t *mtr)
{
    for (size_t i = 0; i < mtr->rows; i++)
        free(mtr->matrix[i]);
    free(mtr->matrix);
    mtr->matrix = NULL;
    mtr->rows = 0;
    mtr->columns = 0; 
}

int allocate_matrix(matrix_t *mtr, size_t n, size_t m)
{
    mtr->matrix = malloc(n * sizeof(elem_t *));
    
    if (mtr->matrix)
    {
        mtr->rows = 0;
        mtr->columns = m;
        
        for (size_t i = 0; i < n; i++)
        {
            mtr->matrix[i] = malloc(m * sizeof(elem_t));
            if (!mtr->matrix[i])
            {
                free_matrix(mtr);
                return MEM_ER;
            }
            mtr->rows++;
        }
    }
    else
        return MEM_ER;
    
    return EXIT_SUCCESS;
}

int allocate_column(size_t rows, column_t *column)
{
    column->column = malloc(rows * sizeof(elem_t));
    if (!column->column)
        return MEM_ER;
    column->rows = rows;
    
    return EXIT_SUCCESS;
}

void free_column(column_t column)
{
    free(column.column);
}