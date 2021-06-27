#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>
#include <limits.h>

#include "80_bit_compare.h"

static double test_80_bit_add(long double a, long double b, size_t iterations)
{
    long double res;
    clock_t clk = clock();
    for (size_t i = 0; i < iterations; i++)
    {
        res = a + b;
    }
    clk = clock() - clk;

    return (double)clk / CLOCKS_PER_SEC;
}

static double test_80_bit_add_asm(long double a, long double b, size_t iterations)
{
    long double res;
    clock_t clocks = clock();
    for (size_t i = 0; i < iterations; i++)
    {
        __asm__("FLD %1\n"
                "FLD %2\n"
                "FADDP\n"
                "FSTP %0\n"
                : "=m"(res)
                : "m"(a), "m"(b));
    }
    clocks = clock() - clocks;

    return (double)clocks / CLOCKS_PER_SEC;
}

static double test_80_bit_mlt(long double a, long double b, size_t iterations)
{
    long double res;
    clock_t clocks = clock();
    for (size_t i = 0; i < iterations; i++)
    {
        res = a * b;
    }
    clocks = clock() - clocks;

    return (double)clocks / CLOCKS_PER_SEC;
}

static double test_80_bit_mlt_asm(long double a, long double b, size_t iterations)
{
    long double res;
    clock_t clocks = clock();
    for (size_t i = 0; i < iterations; i++)
    {
        __asm__("FLD %1\n"
                "FLD %2\n"
                "FMULP\n"
                "FSTP %0\n"
                : "=m"(res)
                : "m"(a), "m"(b));
    }
    clocks = clock() - clocks;

    return (double)clocks / CLOCKS_PER_SEC;
}

static double test_iter_time(size_t iterations)
{
    clock_t clocks = clock();
    for (size_t i = 0; i < iterations; i++);
    clocks = clock() - clocks;

    return (double)clocks / CLOCKS_PER_SEC;
}

void print_80_bit_compares()
{
    printf("%zu bit compares.\n", sizeof(long double) * __CHAR_BIT__);

    size_t iterations = 10000000;
    long double a = 1e43, b = 1e53;

    double iter_time = test_iter_time(iterations);
    printf("iter time - %lf\n", iter_time);

    double add_time = test_80_bit_add(a, b, iterations);
    double add_time_asm = test_80_bit_add_asm(a, b, iterations);
    printf("add time - %lf\nasm add time - %lf\n", add_time - iter_time, add_time_asm - iter_time);

    double mlt_time = test_80_bit_mlt(a, b, iterations);
    double mlt_time_asm = test_80_bit_mlt_asm(a, b, iterations);
    printf("mlt time - %lf\nasm mlt time - %lf\n", mlt_time - iter_time, mlt_time_asm - iter_time);
}