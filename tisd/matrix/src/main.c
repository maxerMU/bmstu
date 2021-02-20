#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix_create.h"
#include "matrix_utils.h"
#include "read_funcs.h"
#include "gen_matrix.h"
#include "pmatrix_utils.h"
#include "pmatrix_create.h"

#define MATRIX_FILE "matrix.txt"
#define VECTOR_FILE "vector.txt"
#define TIME_ITERATIONS 10000

int create_matrix_file(void)
{
    int n, m;
    printf("rows must be > 0\ninput rows: ");
    int rc = fread_signed_int(&n, stdin);
    if (rc || n <= 0)
    {
        printf("wrong rows\n");
        return EXIT_FAILURE;
    }

    printf("columns must be > 0\ninput columns: ");
    rc = fread_signed_int(&m, stdin);
    if (rc || m <= 0)
    {
        printf("wrong columns\n");
        return EXIT_FAILURE;
    }

    int min, max;
    printf("min must be != 0\ninput min: ");
    rc = fread_signed_int(&min, stdin);
    if (rc || !min)
    {
        printf("wrong min\n");
        return EXIT_FAILURE;
    }

    printf("max must be != 0\ninput max: ");
    rc = fread_signed_int(&max, stdin);
    if (rc || !max)
    {
        printf("wrong max\n");
        return EXIT_FAILURE;
    }

    if (min > max)
    {
        printf("wrong min max\n");
        return EXIT_FAILURE;
    }

    int percent;
    printf("percent must be >= 0 and <= 100\ninput percent: ");
    rc = fread_signed_int(&percent, stdin);
    if (rc || percent < 0 || percent > 100)
    {
        printf("wrong percent\n");
        return EXIT_FAILURE;
    }

    FILE *f = fopen(MATRIX_FILE, "w");

    if (f)
    {
        fgen_matrix(f, n, m, percent / 100.0, min, max);
        fclose(f);
    }
    else
    {
        printf("open error\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int read_gen_matrix(matrix_t *matrix)
{
    FILE *f = fopen(MATRIX_FILE, "r");
    if (f)
    {
        int rc = fread_matrix(matrix, f);
        fclose(f);
        if (rc)
            return rc;
    }
    else
        return EXIT_FAILURE;
    
    return EXIT_SUCCESS;
}

int read_gen_pmatrix(pmatrix_t *pmtr)
{
    FILE *f = fopen(MATRIX_FILE, "r");
    if (f)
    {
        int rc = fread_pmatrix(pmtr, f);
        fclose(f);
        if (rc)
            return rc;
    }
    else
        return EXIT_FAILURE;
    
    return EXIT_SUCCESS;
}

int create_vector_file(void)
{
    int n;
    printf("rows must be > 0\ninput rows: ");
    int rc = fread_signed_int(&n, stdin);
    if (rc || n <= 0)
    {
        printf("wrong rows\n");
        return EXIT_FAILURE;
    }

    int min, max;
    printf("min must be != 0\ninput min: ");
    rc = fread_signed_int(&min, stdin);
    if (rc || min == 0)
    {
        printf("wrong min\n");
        return EXIT_FAILURE;
    }

    printf("max must be != 0\ninput max: ");
    rc = fread_signed_int(&max, stdin);
    if (rc || max == 0)
    {
        printf("wrong max\n");
        return EXIT_FAILURE;
    }

    if (min > max)
    {
        printf("wrong min max\n");
        return EXIT_FAILURE;
    }

    int percent;
    printf("percent must be >= 0 and <= 100\ninput percent: ");
    rc = fread_signed_int(&percent, stdin);
    if (rc || percent < 0 || percent > 100)
    {
        printf("wrong percent\n");
        return EXIT_FAILURE;
    }

    FILE *f = fopen(VECTOR_FILE, "w");

    if (f)
    {
        fgen_vector(f, n, percent / 100.0, min, max);
        fclose(f);
    }
    else
    {
        printf("open error\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int read_gen_vector(column_t *vector)
{
    FILE *f = fopen(VECTOR_FILE, "r");
    if (f)
    {
        int rc = fread_vector(vector, f);
        fclose(f);
        if (rc)
            return rc;
    }
    else
        return EXIT_FAILURE;
    
    return EXIT_SUCCESS;
}

int read_gen_pvector(pvector_t *pvector)
{
    FILE *f = fopen(VECTOR_FILE, "r");
    if (f)
    {
        int rc = fread_pvector(pvector, f);
        fclose(f);
        if (rc)
            return rc;
    }
    else
        return EXIT_FAILURE;
    
    return EXIT_SUCCESS;
}

int time_table(void)
{
    for (size_t size = 200; size <= 800; size *= 2)
    {
        printf("matrix %zux%zu\n", size, size);
        printf("     percent    normal    packed normal mem  packed mem\n");
        for (size_t percent = 10; percent <= 60; percent += 10)
        {
            /*FILE *f = fopen(MATRIX_FILE, "w");
            if (f)
            {
                gen_matrix(f, size, size, percent / 100.0, -1000, 1000);
                fclose(f);
            }
            else
            {
                printf("open error\n");
                return EXIT_FAILURE;
            }
            f = fopen(VECTOR_FILE, "w");
            if (f)
            {
                gen_vector(f, size, percent / 100.0, -1000, 1000);
                fclose(f);
            }
            else
            {
                printf("open error\n");
                return EXIT_FAILURE;
            }*/
            matrix_t mtr;
            column_t vec;
            pmatrix_t pmtr;
            pvector_t pvec;
            // int rc = read_gen_matrix(&mtr);
            // if (rc)
            //     return rc;
            // rc = read_gen_pmatrix(&pmtr);
            // if (rc)
            // {
            //     free_matrix(&mtr);
            //     return rc;
            // }
            // rc = read_gen_vector(&vec);
            // if (rc)
            // {
            //     free_matrix(&mtr);
            //     free_pmatrix(&pmtr);
            //     return rc;
            // }
            // rc = read_gen_pvector(&pvec);
            // if (rc)
            // {
            //     free_matrix(&mtr);
            //     free_pmatrix(&pmtr);
            //     free_column(vec);
            //     return rc;
            // }
            allocate_matrix(&mtr, size, size);
            allocate_column(size, &vec);
            gen_matrix(&mtr, percent / 100.0, -1000, 1000);
            gen_vector(&vec, percent / 100.0, -1000, 1000);
            read_pmatrix_from_matrix(&pmtr, mtr);
            read_pvector_from_vector(&pvec, vec);
            column_t res;
            int rc = allocate_column(mtr.rows, &res);
            if (rc)
            {
                free_matrix(&mtr);
                free_pmatrix(&pmtr);
                free_column(vec);
                free_pvector(&pvec);
                return rc;
            }
            pvector_t pres;
            rc = allocate_pvector(&pres);
            rc = change_pvcolumn_size(&pres, mtr.rows);
            if (rc)
            {
                free_matrix(&mtr);
                free_pmatrix(&pmtr);
                free_column(vec);
                free_pvector(&pvec);
                free_column(res);
                return rc;
            }
            size_t *pi = calloc(mtr.columns, sizeof(size_t));
            if (!pi)
            {
                free_matrix(&mtr);
                free_pmatrix(&pmtr);
                free_column(vec);
                free_pvector(&pvec);
                free_column(res);
                return rc;
            }
            clock_t normal = clock();
            for (size_t i = 0; i < TIME_ITERATIONS; i++)
                mlt_mtr_vec(mtr, vec, &res);
            normal = clock() - normal;
            double normal_time = ((double) normal / CLOCKS_PER_SEC) / TIME_ITERATIONS;

            clock_t packed = clock();
            for (size_t i = 0; i < TIME_ITERATIONS; i++)
                mlt_pmtr_pvec(pmtr, pvec, &pres, pi);
            packed = clock() - packed;
            double packed_time = ((double) packed / CLOCKS_PER_SEC) / TIME_ITERATIONS;
 
            size_t normal_size = sizeof(mtr) + sizeof(elem_t *) * mtr.rows + sizeof(elem_t) * mtr.rows * mtr.columns;
            size_t packed_size = sizeof(pmtr) + pmtr.columns * 2 * sizeof(elem_t) + sizeof(row_start_t) * (mtr.rows + 1);
            printf("%12zu %7lfs %7lfs %8zub %9zub\n", percent, normal_time, packed_time, normal_size, packed_size);
            free_matrix(&mtr);
            free_pmatrix(&pmtr);
            free_column(vec);
            free_pvector(&pvec);
            free_column(res);
            free_pvector(&pres);
        }
    }

    return EXIT_SUCCESS;
}

int main(void)
{
    setbuf(stdout, NULL);
    puts("This programm makes matrix vector mlt usind standart method and method for packed matrix.\n");

    matrix_t mtr;
    column_t vector;
    pmatrix_t pmtr;
    pvector_t pvec;
    int mtr_init = 0, vec_init = 0, pmtr_init = 0, pvec_init = 0;

    int choise = 10;
    int rc = EXIT_SUCCESS;
    while (choise)
    {
        printf("1 - generate and read matrix from file\n"
               "2 - generate and read vector from file\n"
               "3 - write matrix (normal view)\n"
               "4 - write vector (normal view)\n"
               "5 - write matrix (3 objects)\n"
               "6 - write vector (2 objects)\n"
               "7 - read matrix from stdin\n"
               "8 - read vector from stdin\n"
               "9 - normal matrix column mlt\n"
               "10 - packed matrix column mlt\n"
               "11 - time compare\n"
               "0 - exit\n"
               "Your choise: ");
        rc = fread_signed_int(&choise, stdin);
        if (rc)
            continue;
        if (choise == 1)
        {
            if (mtr_init)
            {
                mtr_init = 0;
                free_matrix(&mtr);
            }

            rc = create_matrix_file();
            if (rc)
                break;
            
            rc = read_gen_matrix(&mtr);
            if (rc)
                break;
            mtr_init = 1;

            if (pmtr_init)
            {
                pmtr_init = 0;
                free_pmatrix(&pmtr);
            }
            rc = read_gen_pmatrix(&pmtr);
            if (rc)
                break;
            pmtr_init = 1;
        }
        else if (choise == 2)
        {
            if (vec_init)
            {
                vec_init = 0;
                free_column(vector);
            }

            rc = create_vector_file();
            if (rc)
                break;
            
            rc = read_gen_vector(&vector);
            if (rc)
                break;
            vec_init = 1;
                
            if (pvec_init)
            {
                pvec_init = 0;
                free_pvector(&pvec);
            }

            rc = read_gen_pvector(&pvec);
            if (rc)
                break;
            pvec_init = 1;
        }        
        else if (choise == 3)
        {
            if (mtr_init)
                fwrite_matrix(mtr, stdout);
            else
                puts("matrix didn't initialized");
        }
        else if (choise == 4)
        {
            if (vec_init)
                fwrite_vector(vector, stdout);
            else
                puts("vector didn't initialized");
        }
        else if (choise == 5)
        {
            if (pmtr_init)
                fwrite_pmatrix(pmtr, stdout);
            else
                puts("matrix didn't initialized");
        }
        else if (choise == 6)
        {
            if (pvec_init)
                fwrite_pvector(pvec, stdout);
            else
                puts("vector didn't initialized");
        }                
        else if (choise == 7)
        {
            printf("input matrix sizes and after that input matrix by rows\n");
            if (mtr_init)
            {
                mtr_init = 0;
                free_matrix(&mtr);
            }

            rc = fread_matrix(&mtr, stdin);
            if (rc)
            {
                printf("wrong sizes\n");
                break;
            }
            mtr_init = 1;

            if (pmtr_init)
            {
                pmtr_init = 0;
                free_pmatrix(&pmtr);
            }
            rc = read_pmatrix_from_matrix(&pmtr, mtr);
            if (rc)
                break;
            pmtr_init = 1;
        }
        else if (choise == 8)
        {
            printf("input vector size and after that input column by rows\n");
            if (vec_init)
            {
                vec_init = 0;
                free_column(vector);
            }

            rc = fread_vector(&vector, stdin);
            if (rc)
            {
                printf("wrong sizes\n");
                break;
            }
            vec_init = 1;
                
            if (pvec_init)
            {
                pvec_init = 0;
                free_pvector(&pvec);
            }

            rc = read_pvector_from_vector(&pvec, vector);
            if (rc)
                break;
            pvec_init = 1;
        }
        else if (choise == 9)
        {
            if (!mtr_init || !vec_init)
            {
                printf("matrix or vector didn't initialized\n");
                break;
            }
            if (mtr.columns != vector.rows)
            {
                printf("wrong sizes\n");
                break;
            }
            column_t res;
            rc = allocate_column(mtr.rows, &res);
            if (rc)
                break;
            mlt_mtr_vec(mtr, vector, &res);
            fwrite_vector(res, stdout);
            free_column(res);
        }
        else if (choise == 10)
        {
            if (!pmtr_init || !pvec_init)
            {
                printf("matrix or vector didn't initialized\n");
                break;
            }
            if (mtr.columns != vector.rows)
            {
                printf("wrong sizes\n");
                break;
            }
            pvector_t res;
            rc = allocate_pvector(&res);
            if (rc)
                break;
            rc = change_pvcolumn_size(&res, mtr.rows);
            if (rc)
                break;
            size_t *pi = calloc(mtr.columns, sizeof(size_t));
            if (!pi)
            {
                free_pvector(&res);
                break;
            }
            mlt_pmtr_pvec(pmtr, pvec, &res, pi);
            fwrite_pvector(res, stdout);
            free_pvector(&res);
        }
        else if (choise == 11)
        {
            rc = time_table();
            if (rc)
                return rc;
        }
    }

    if (mtr_init)
        free_matrix(&mtr);
    
    if (vec_init)
        free_column(vector);
    
    if (pmtr_init)
        free_pmatrix(&pmtr);
        
    if (pvec_init)
        free_pvector(&pvec);

    return rc;
}