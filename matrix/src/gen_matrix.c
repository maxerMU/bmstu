#include <math.h>
#include "gen_matrix.h"

void fgen_matrix(FILE *dst, size_t rows, size_t columns, double percent, int min, int max)
{
    fprintf(dst, "%zu %zu\n", rows, columns);
    size_t zeros = trunc(rows * percent * columns);
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            int zero_percent = trunc (100 * (zeros / (double) ((rows - i) * (columns - j))));
            int digit = 0;
            if (rand() % 101 <= zero_percent)
                zeros--;
            else
            {
                digit = rand() % (max - min + 1) + min;
                if (digit == 0)
                    digit++;
            }
            fprintf(dst, "%d ", digit);
        }
        fprintf(dst, "\n");
    }
}

void fgen_vector(FILE *dst, size_t rows, double percent, int min, int max)
{
    fprintf(dst, "%zu\n", rows);
    size_t zeros = trunc(rows * percent);
    for (size_t i = 0; i < rows; i++)
    {
        int zero_percent = trunc (100 * (zeros / (double) (rows - i)));
        int digit = 0;
        if (rand() % 101 <= zero_percent)
            zeros--;
        else
        {
            digit = rand() % (max - min + 1) + min;
            if (digit == 0)
                digit++;
        }
        fprintf(dst, "%d", digit);
        fprintf(dst, "\n");
    }
}